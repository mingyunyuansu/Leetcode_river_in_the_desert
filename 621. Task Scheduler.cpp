/*
You are given a char array representing tasks CPU need to do. It contains capital letters A to Z where each letter represents a different task. Tasks could be done without the original order of the array. Each task is done in one unit of time. For each unit of time, the CPU could complete either one task or just be idle.

However, there is a non-negative integer n that represents the cooldown period between two same tasks (the same letter in the array), that is that there must be at least n units of time between any two same tasks.

You need to return the least number of units of times that the CPU will take to finish all the given tasks.

 

Example 1:

Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: 
A -> B -> idle -> A -> B -> idle -> A -> B
There is at least 2 units of time between any two same tasks.
Example 2:

Input: tasks = ["A","A","A","B","B","B"], n = 0
Output: 6
Explanation: On this case any permutation of size 6 would work since n = 0.
["A","A","A","B","B","B"]
["A","B","A","B","A","B"]
["B","B","B","A","A","A"]
...
And so on.
Example 3:

Input: tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
Output: 16
Explanation: 
One possible solution is
A -> B -> C -> A -> D -> E -> A -> F -> G -> A -> idle -> idle -> A -> idle -> idle -> A
 

Constraints:

The number of tasks is in the range [1, 10000].
The integer n is in the range [0, 100].
*/
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        //神仙题目
        int max = 0;
        vector<int> table(26);
        for (int i = 0; i < tasks.size(); ++i) {
            table[tasks[i] - 'A']++;
            max = table[tasks[i] - 'A'] > max ? table[tasks[i] - 'A'] : max;
        }
        int cnt_dup_max = 0;
        for (int i = 0; i < table.size(); ++i) {
            if (table[i] == max) cnt_dup_max++;
        }
        int ans = (max - 1) * (n + 1) + cnt_dup_max;
        return tasks.size() > ans ? tasks.size() : ans;
    }
};

//基本思想是插空。可以想见，给定一个任务串，如果出现不得不idle的情况，那么必然是因为
//不同任务的数量过少，而相同任务的数量过多。
//这种情况下，最小运行时间是由重复数最大的那个任务决定的（因为他们每一次运行期间必须间隔n）。
//设一个任务为E，他是出现频率最大的，频率设为M。
//那么首先插入M-1个E，每个之间间隔n，运行时间至少为(M-1) * (n + 1)，即M-1个任务与M-1次间隔。（+1因为自身消耗时间）
//这时如果频率为M的任务只有一个，那么结尾加上最后一次运行E就是结果了。否则有几个重复，就得加几。
//其他频率比较小的元素，则刚好可以插入M个E形成的M-1组空中，如E..E..E，那么频率为M-1的A插入后得EA.EA.E，以此类推。
//结果需要加一次判断，因为如果一个序列重复数较少，那么不同的任务已经足够填满空隙了，此时答案就是任务长度，即无idle。
//可以说上面最大重复数方法形成的框架就是一个临界点，如果可填充物比这个还宽，就不需要idle。