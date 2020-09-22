#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

//详细解释请看
int non_manacher_naive(const string &s) {
    int ans = 0, odd = 0, even = 0;
    for (int i = 0; i < s.length(); ++i) {
        int k = 1;
        while(i - k >= 0 && i + k < s.length() && s[i + k] == s[i - k]) {
            ++k;
        }
        odd = max(odd, k);
    }
    for (int i = 0; i < s.length(); ++i) {
        int k = 0;
        while (i - k >= 0 && i + k + 1 < s.length() && s[i - k] == s[i + k + 1]) {
            ++k;
        }
        even = max(even, k);
    }
    return max(odd * 2 - 1, 2 * even);
}

int odd_max_palindrome_length_manacher(const string &s) {
    //奇数情况
    int l = 0, r = -1;
    int max_half = 0;
    vector<int> d1(s.size());
    for (int i = 0; i < s.size(); ++i) {
        int k = i > r ? 1 : min(d1[l + (r - i)], r - i);//k是个数
        while (i - k >= 0 && i + k < s.size() && s[i - k] == s[i + k])
        ++k;
        d1[i] = k--;//长度和坐标加减要错1，下面更新时要用
        if (i + k > r) {
            //超过了当前大串的范围，更新
            l = i - k;
            r = i + k;
        }
        max_half = max(max_half, d1[i]);
    }
    return 2 * max_half - 1;
}

int even_max_palindrome_length_manacher(const string &s) {
    vector<int> d2(s.size());
    int l = 0, r = -1, max_half = 0;
    for (int i = 0; i < s.length(); ++i) {
        int k = i > r ? 0 : min(r - i + 1, d2[l + r - i + 1]);
        while (i - k - 1 >= 0 && i + k < s.size() && s[i - k - 1] == s[i + k])
        ++k;
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
        max_half = max(max_half, d2[i]);
    }
    return 2 * max_half;
}

int Manacher(const string &s) {
    string s1 = "#";
    for (char c: s) {
        s1.push_back(c);
        s1.push_back('#');
    }
    //预处理完毕
    int n = s1.size();
    int len_ans = 0;
    vector<int> d1(s1.size());
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = i > r ? 1 : min(r - i, d1[l + r - i]);
        while (i - k >= 0 && i + k < n && s1[i - k] == s1[i + k]) {
            ++k;
        }
        d1[i] = k--;
        if (i + k > r) {
            r = i + k;
            l = i - k;
        }
    len_ans = max(len_ans, d1[i]);
    }
    return len_ans - 1;
}

void benchmark() {
    string s(5e4, 'A');
    clock_t start = clock();
    cout << "Manacher's result: " << Manacher(s) << endl;
    clock_t stop1 = clock();
    cout << "Central expansion's result: " << non_manacher_naive(s) << endl;
    clock_t stop2 = clock();
    cout << "Manacher's duration:" << (double)(stop1 - start) / CLOCKS_PER_SEC << "\n" << "Central expansion's duration:" << (double)(stop2 - start) / CLOCKS_PER_SEC << endl;
}

int main() {
    
    string s = "ABABAB";
    string s1 = "aba";
    cout << odd_max_palindrome_length_manacher(s) << endl;
    cout << even_max_palindrome_length_manacher(s1) << endl;
    cout << Manacher(s) << endl;
    cout << Manacher(s1) <<  endl;
    cout << non_manacher_naive(s) << endl;
    cout << non_manacher_naive(s1) << endl;
    
   //benchmark();
    return 0;
}