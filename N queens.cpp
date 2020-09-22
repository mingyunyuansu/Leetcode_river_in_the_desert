//经典老番N皇后问题
//其实我觉得蛮难的，虽然大一时就接触到了，但是直到现在我都是要想想才能做出来
//或许是当年的舍友都太猛了，他们似乎讨论的都很轻松，让我有种其实八皇后蛮简单的错觉

//总之这是一个效率还不错的一维数组回溯解法
//算是模板了，可以背一下
#include <vector>
#include <iostream>
using namespace std;

//已知每个皇后必须在不同行，因为可以直接用一个一位数组，a[i]表示第i行的皇后所在的列数
//其实就类似全排列。但是在得出一整个全排结果前就判断每一步是否合法，然后视情况直接回溯，可以剪掉不少无用的时间复杂度
bool check(vector<int> &v, int curr_row, int n) {
//依次查看当该行之前（已经放了皇后的行）是否有列与当前行皇后所在列有冲突
//斜线的合法性判断比较讨巧，只要两个横坐标的差与两个纵坐标的差不相等即可
    for (int i = 0; i < curr_row; ++i) {
        if (v[curr_row] == v[i] || abs(curr_row - i) == abs(v[curr_row] - v[i])) 
            return false;
        }
    return true;
}

void recur(vector<int> &v, int curr_row, int n, int &cnt) {
    if (curr_row == n) {
        cnt++;
        return;
    }
    //对于当前行，依次试所有列
    for (int i = 0; i < n; ++i) {
        v[curr_row] = i;
        if (check(v, curr_row, n)) {
            //合法则下一行
            recur(v, curr_row + 1, n, cnt);
        }
        //这里没有进入下一层其实就相当于回溯了
        //因为要重新填充这一行的列数
    }
}

int main() {
    const int n = 8;
    vector<int> v(n, -1);
    int cnt = 0;
    recur(v, 0, n, cnt);
    cout << cnt << endl;
    return 0;
}