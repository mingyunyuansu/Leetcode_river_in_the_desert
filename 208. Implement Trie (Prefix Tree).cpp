//终于见到了大名鼎鼎的前缀树。
//看了一下简洁也就写出来了，似乎并没有多难，不知道为什么学校不教
//就是不知道什么场景会用上，而且构建一科前缀树本身代码量就蛮大的了

class Trie {
private:
    struct trie_node {
        trie_node* children[26];
        bool is_end;
        
        trie_node() {
            is_end = false;
            for (int i = 0; i < 26; ++i) {
                children[i] = NULL;
            }
        }
    };
    
    trie_node* root;
    
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new trie_node();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        trie_node* p = root;
        for (int i = 0; i < word.size(); ++i) {
            if (!p->children[word[i] - 'a']) {
                p->children[word[i] - 'a'] = new trie_node();
            }
            p = p->children[word[i] - 'a'];
        }
        p->is_end = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        trie_node* p = root;
        for (int i = 0; i < word.size(); ++i) {
            if (p->children[word[i] - 'a'] == NULL) return false;
            p = p->children[word[i] - 'a'];
        }
        return p->is_end;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        trie_node* p = root;
        for (int i = 0; i < prefix.size(); i++) {
            int index = prefix[i] - 'a';
            if (!p->children[index]) return false;
            p = p->children[index];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */