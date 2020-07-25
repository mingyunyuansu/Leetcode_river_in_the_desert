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

void merge(vector<int> &v, vector<int> &ans, int l, int r, int mid) {
    vector<int> tmp(r - l);
    int i = l, j = mid, curr = 0;
    while (i < mid || j < r) {
        if (i < mid && j < r) {
            if (v[i] < v[j]) {
                tmp[curr++] = v[i++];
            }
            else tmp[curr++] = v[j++];
        }
        else if (i < mid) tmp[curr++] = v[i++];
        else if (j < r) tmp[curr++] = v[j++];
    }
    copy(tmp.begin(), tmp.end(), v.begin() + l);
    print_arr(v);
}

int main() {
    vector<int> v{1,4,6,3,8,4,66,3, 12,5,7,9};
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