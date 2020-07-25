//很经典。给一个数组，求出最大的子序列乘积。
//来自Leetcode 152. Maximum Product Subarray
/*
Input: [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.
*/
//两种思路，一种是DP，一种是利用奇偶性质。
//首先DP，定式思维会认为只会存在一个状态量，但是这题需要两个状态量，一个是当前最小，一个是当前最大。
//因为我们的状态量既需要一个当前最大值来储存答案，又需要一个当前最小值来保证下次遇到负数时，可能乘得的正数。
//再简化一下发现当前i的值的计算仅依赖i-1，因此可以用一个常量保存。
int dynamic_programming(vector<int> &nums) {
    int ans = nums[0], max_curr = nums[0], min_curr = nums[0];
    for (int i = nums[1]; i < nums.size(); ++i) {
        if (nums[i] < 0) {
            swap(max_curr, min_curr);
        }
        max_curr = max(max_curr * nums[i], nums[i]);
        min_curr = min(min_curr * nums[i], nums[i]);
        ans = max(ans, max_curr);
    }
    return ans;
}

//第二种比较巧妙，观察可以发现会使乘积的结果浮动的是奇数的个数。
//这个因素可以通过左右各一次遍历（前后缀乘积）来消除，只需要随时保存结果，最后返回最大即可。
int 2_passes(vector<int> nums) {
    int ans = nums[0];
    int pre = 1, post = 1;
    for (int i = 0; i < nums.size(); ++i) {
        pre *= nums[i];
        post *= nums[nums.size() - 1 - i];
        ans = max(max(pre, post), ans);
        pre = pre ? pre : 1;
        post = post ? post : 1;
        //0是一种分界线
    }
    return ans;
}
