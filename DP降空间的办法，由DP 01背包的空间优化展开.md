起因是Leetcode 416. Partition Equal Subset Sum。这是一题0/1背包问题，二维DP是最直观的解法。


但是有人优化到了一维（https://leetcode.com/problems/partition-equal-subset-sum/discuss/90592/01-knapsack-detailed-explanation）：
```Java
public boolean canPartition(int[] nums) {
    int sum = 0;
    
    for (int num : nums) {
        sum += num;
    }
    
    if ((sum & 1) == 1) {
        return false;
    }
    sum /= 2;
    
    int n = nums.length;
    boolean[] dp = new boolean[sum+1];
    Arrays.fill(dp, false);
    dp[0] = true;
    
    for (int num : nums) {
        for (int i = sum; i > 0; i--) {
            if (i >= num) {
                dp[i] = dp[i] || dp[i-num];
            }
        }
    }
    
    return dp[sum];
}
```
于是有人问如何知道什么情况可以把二维降一维，于是有了以下回答。这个回答应该被裱起来挂墙上：

```
Yes, the magic is observation from the induction rule/recurrence relation!

For this problem, the induction rule:

If not picking nums[i - 1], then dp[i][j] = dp[i-1][j]
if picking nums[i - 1], then dp[i][j] = dp[i - 1][j - nums[i - 1]]
You can see that if you point them out in the matrix, it will be like:

			  j
	. . . . . . . . . . . . 
	. . . . . . . . . . . .  
	. . ? . . ? . . . . . .  ?(left): dp[i - 1][j - nums[i], ?(right): dp[i - 1][j]
i	. . . . . # . . . . . .  # dp[i][j]
	. . . . . . . . . . . . 
	. . . . . . . . . . . . 
	. . . . . . . . . . . . 
	. . . . . . . . . . . . 
	. . . . . . . . . . . . 
Optimize to O(2*n): you can see that dp[i][j] only depends on previous row, so you can optimize the space by only using 2 rows instead of the matrix. Let's say array1 and array2. Every time you finish updating array2, array1 have no value, you can copy array2 to array1 as the previous row of the next new row.
Optimize to O(n): you can also see that, the column indices of dp[i - 1][j - nums[i] and dp[i - 1][j] are <= j. The conclusion you can get is: the elements of previous row whose column index is > j(i.e. dp[i - 1][j + 1 : n - 1]) will not affect the update of dp[i][j] since we will not touch them:
			  j
	. . . . . . . . . . . . 
	. . . . . . . . . . . .  
	. . ? . . ? x x x x x x  you will not touch x for dp[i][j]
i	. . . . . # . . . . . .  # dp[i][j]
	. . . . . . . . . . . . 
	. . . . . . . . . . . . 
	. . . . . . . . . . . . 
	. . . . . . . . . . . . 
	. . . . . . . . . . . . 
Thus if you merge array1 and array2 to a single array array, if you update array backwards, all dependencies are not touched!

    (n represents new value, i.e. updated)
	. . ? . . ? n n n n n n n
              #  
However if you update forwards, dp[j - nums[i - 1]] is updated already, you cannot use it:

    (n represents new value, i.e. updated)
	n n n n n ? . . . . . .  where another ? goes? Oops, it is overriden, we lost it :(
              #  
Conclusion:
So the rule is that observe the positions of current element and its dependencies in the matrix. Mostly if current elements depends on the elements in previous row(most frequent case)/columns, you can optimize the space.
```