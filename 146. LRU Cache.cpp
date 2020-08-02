//题目不难，但是提供了很好的角度来看LRU cache究竟是怎么实现的。
//list（链表）管理使用的频率，因为插入删除速度快
//map就是cache，但是同时还要多记录一个链表的位置（迭代器信息），以便更新。
class LRUCache {
public:
    LRUCache(int capacity) {
        _cap = capacity;
        _size = 0;
    }

    int get(int key) {
        auto it = cache.find(key);
        if (it == cache.end()) {
            return -1;
        }
        else {
            int val = it->second.second;
            touch(it);
            return val;
        }
    }

    void put(int key, int value) {
        auto it = cache.find(key);
        if (it != cache.end()) touch(it);
        else {
            if (_cap == _size) {
                int dele_key = freq.back();
                freq.pop_back();
                cache.erase(dele_key);
                _size--;
            }
            freq.push_front(key);
            _size++;
        }
        cache[key] = {freq.begin(), value};
    }
private:
    int _cap;
    int _size;
    typedef list<int>::iterator LI;
    typedef pair<list<int>::iterator, int> P;
    list<int> freq; //keys, pos
    unordered_map<int, P> cache; //<key, <pos, val>>

    void touch(unordered_map<int, P>::iterator it) {
        freq.erase(it->second.first);
        freq.push_front(it->first);
        it->second.first = freq.begin();
    }
};