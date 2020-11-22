//Merge sort 是一个我不太熟的排序，虽然要写应该可以，但是终归没有快排那么熟练。
//在leetcode上碰到一个sort linked list的题，似乎这种bottom to top 的merge sort是最优解。
//并且我感觉非递归的merge sort控制好像蛮有意思，正好练一练手。
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print_arr(vector<int> &arr) {
    for (auto x: arr) {
        cout << x << " ";
    }
    cout << endl;
}

void merge(vector<int> &v, vector<int> &ans, int start, int end, int mid) {
    int l = start, r = mid, curr = start;
    while (l < v.size() && r < v.size() && l < mid && r < end) {
        ans[curr++] = v[l] < v[r] ? v[l++] : v[r++];
    }
    while (l < v.size() && l < mid) {
        ans[curr++] = v[l++];
    }
    while (r < v.size() && r < end) {
        ans[curr++] = v[r++];
    }
    copy(ans.begin() + start, ans.begin() + end, v.begin() + start);
    print_arr(v);
}

int main() {
    vector<int> v{-4,0,7,4,9,-5,-1,0,-7,-1};
    int sz = 1;
    vector<int> ans(v.size());
    for (; sz < v.size(); sz <<= 1) {
        for (int lo = 0; lo < v.size(); lo += 2 * sz) {
            merge(v, ans, lo, min(lo + 2*sz, (int)v.size()), lo + sz);
        }
    }
    print_arr(v);
    return 0;
}