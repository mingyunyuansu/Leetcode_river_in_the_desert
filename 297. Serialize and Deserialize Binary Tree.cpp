/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
//比较啰嗦的一题
//我采用的是BSF，即一层一层地打印，和leetcode官方的树表示方法一致。
//细节很多，但是最重要的是有：
//遍历当前层，打印（输出到data）下一层，只要有NULL，就打印null；
//遍历当前层，依次恢复子层
//最后的剪枝可以消除大量的末尾NULL

class Codec {
public:

    string serialize(TreeNode* root) {
    if (!root) return "[]";
    deque<TreeNode*> q1, q2;
    q1.push_back(root);
    string ans = to_string(root->val);
    while (!q1.empty()) {
        //string curr_level;
        while (!q1.empty()) {
            TreeNode* tmp = q1.front();
            q1.pop_front();
            if (tmp->left) {
                q2.push_back(tmp->left);
                ans += ',' + to_string(tmp->left->val);
            }
            else ans += ",null";
            if (tmp->right) {
                q2.push_back(tmp->right);
                ans += ',' + to_string(tmp->right->val);
            }
            else ans += ",null";
        }
        q1.swap(q2);
    }
    //消掉末尾无意义的"null"
    while (ans.size() >= 4 && ans.substr(ans.size() - 4, 4) == "null") {
        ans.pop_back();
        ans.pop_back();
        ans.pop_back();
        ans.pop_back();
        ans.pop_back();
    }
    return '[' + ans + ']';
}
TreeNode* deserialize(string data) {
    if (data == "[]") return NULL;
    int curr_cnt = 0, end_cnt = 0, pos = 1;
    string one;
    while (data[pos] != ',' && data[pos] != ']') {
        one += data[pos++];
    }
    pos++;
    TreeNode* root = new TreeNode(stoi(one));
    TreeNode* p = root;
    deque<TreeNode*> q1, q2;
    q1.push_back(root);
    while (pos < data.size() && q1.size()) {
        while (q1.size()) {
            TreeNode* tmp = q1.front();
            q1.pop_front();
            string le, ri;
            while (pos < data.size() && data[pos] != ',' && data[pos] != ']') {
                le += data[pos++];
            }
            pos++;
            if (le != "null" && le.size()) {
                tmp->left = new TreeNode(stoi(le));
                q2.push_back(tmp->left);
            }
            while (pos < data.size() && data[pos] != ',' && data[pos] != ']') {
                ri += data[pos++];
            }
            pos++;
            if (ri != "null" && ri.size()) {
                tmp->right = new TreeNode(stoi(ri));
                q2.push_back(tmp->right);
            }
        }
        q1.swap(q2);
    }
    return root;
}
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));