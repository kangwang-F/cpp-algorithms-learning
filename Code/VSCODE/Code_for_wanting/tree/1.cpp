#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
using namespace std;
class tree{
    public:
    class TreeNode{
        public:
            int val;
            TreeNode* left;
            TreeNode* right;
            TreeNode(int val):val(val),left(NULL),right(NULL){}
    };
    TreeNode* root;
//前序遍历
    void P_t(TreeNode* cur,vector<int>& res){
        if(!cur)return;
        res.push_back(cur->val);
        P_t(cur->left,res);
        P_t(cur->right,res);
    }
    vector<int> Pretraversal(){
        vector<int> res;
        P_t(root,res);
        return res;
    }
//中序
    void M_t(TreeNode* cur,vector<int>& res){
        if(!cur)return;
        
        M_t(cur->left,res);res.push_back(cur->val);
        M_t(cur->right,res);
    }
    vector<int> Midtraversal(){
        vector<int> res;
        M_t(root,res);
        return res;
    }
    void L_t(TreeNode* cur,vector<int>& res){
        if(!cur)return;
        
        L_t(cur->left,res);
        L_t(cur->right,res);res.push_back(cur->val);
    }
    vector<int> Lasttraversal(){
        vector<int> res;
        L_t(root,res);
        return res;
    }
//前序遍历迭代（非递归）【匹配特定顺序问题：栈的强项】
    vector<int> preorderTraversal() {
        vector<int> res;
        stack<TreeNode*> s_t;
        TreeNode* cur = root;
        while(cur!=NULL||!s_t.empty()){
            if(cur==NULL){
                cur = s_t.top()->right;
                //res.push_back(s_t.top()->val);
                s_t.pop();
            }
            else{
                s_t.push(cur);
                res.push_back(cur->val);
                cur = cur->left;
            }
        }return res;
    }
//后序遍历【前序的左右翻转，然后反转整个数组】
    vector<int> postorderTraversal() {
        vector<int> res;
        stack<TreeNode*> s_t;
        TreeNode* cur = root;
        while(cur!=NULL||!s_t.empty()){
            if(cur==NULL){
                cur = s_t.top()->left;
                //res.push_back(s_t.top()->val);
                s_t.pop();
            }
            else{
                s_t.push(cur);
                res.push_back(cur->val);
                cur = cur->right;
            }
        }
        reverse(res.begin(),res.end());
//预留空间（容量capacity），并不是反转
        //res.reserve(res.size());
//  reserve 【预留】
        return res;
    }

//中序遍历【非递归】
        
    vector<int> inorderTraversal() {
        vector<int> res;
        stack<TreeNode*> s_t;
        TreeNode* cur = root;
        while(cur!=NULL||!s_t.empty()){
            if(cur==NULL){
                res.push_back(s_t.top()->val);
                cur = s_t.top()->right;
                s_t.pop();
            }
            else{
                s_t.push(cur);
                cur = cur->left;
            }
        }
        return res;
    }
//05.层序遍历
    //下方有更好看的版本
//【这里使用队列应该，先进先出】【递归法】
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> s_T;
        TreeNode* cur = root;
        int size;
        if(cur){
            s_T.push(cur);
            size = 1;
        }
        else{
            return {};//应该是0个元素的数组
                    //而不是1个空数组的数组
        }
        vector<vector<int>> res;
        while(!s_T.empty()){
            vector<int> ress;
            for(int i =0;i<size;i++){
                cur = s_T.front();
                s_T.pop();
                ress.push_back(cur->val);
                if(cur->left)
                    s_T.push(cur->left);
                if(cur->right)
                    s_T.push(cur->right);
            }
            res.push_back(ress);
            size = s_T.size(); 
        }
        return res;
    }
//更好看的版本
    vector<vector<int>> levelOrder_better(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != NULL) que.push(root);
        vector<vector<int>> result;
        while (!que.empty()) {
            int size = que.size();
            vector<int> vec;
            // 这里一定要使用固定大小size，不要使用que.size()，因为que.size是不断变化的
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                vec.push_back(node->val);
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
            result.push_back(vec);
        }
        return result;
    }
//迭代的版本【非递归】
    void order(TreeNode* cur, vector<vector<int>>& result, int depth)
    {
        if (cur == nullptr) return;
        if (result.size() == depth) result.push_back(vector<int>());
        result[depth].push_back(cur->val);
        order(cur->left, result, depth + 1);
        order(cur->right, result, depth + 1);
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        int depth = 0;
        order(root, result, depth);
        return result;
    }
//06.二叉树的右视图
//【广度优先搜索】【层序遍历+取每一层的最后一个值】
    vector<int> rightSideView(TreeNode* root) {
        queue<TreeNode*> q_t;
        vector<int> res;
        if(root){
            q_t.push(root);
            //res.push_back(root->val);
        }
        else{
            return {};
        }
        while(!q_t.empty()){
            int size = q_t.size();
            TreeNode* cur;
            for(int i =0;i<size;i++){
                cur = q_t.front();
                q_t.pop();
                if(cur->right!=NULL){
                    //res.push_back(cur->right->val);
                    q_t.push(cur->right);
                }
                if(cur->left){
                    //res.push_back(cur->left->val);
                    q_t.push(cur->left);
                }
                //将当前层的最后一个节点 返回到 数组中
                if(i == size-1)
                    res.push_back(cur->val);
            }
        }return res;
    }
//深度优先搜索
    vector<int> res;
    void dfs(TreeNode* root,int depth){
        if(res.size()==depth)res.push_back(root->val);
        if(root->left)dfs(root->left,depth+1);
        if(root->right)dfs(root->right,depth+1);
    }
    vector<int> rightSideView(TreeNode* root) {
        if(root)dfs(root,0);
        return res;
    }
//07.翻转二叉树
    TreeNode* invertTree(TreeNode* root) {
        //前序遍历
        if(root){swap(root->left,root->right);
            invertTree(root->left);
            invertTree(root->right);}
            
        return root;
    }
//08.对称二叉树
    bool compare(TreeNode* right,TreeNode* left){
        // if(!right&&!left){
        //     return true;
        // }
        // else if(right&&!left){
        //     return false;
        // }
        // else if(!right&&left){
        //     return false;
        // }
        // else{
        //     if(right->val!=left->val)
        //         return false;
        // }
        if(right&&left){
            if(right->val!=left->val)
                return false;
        }
        else if(!right&&!left){
            return true;
        }
        else{
            return false;
        }
        bool outside = compare(right->right,left->left);
        bool inside = compare(left->right,right->left);
        return outside&&inside;
    }
    bool isSymmetric(TreeNode* root) {
        if(!root)return true;
        return compare(root->right,root->left);
    }
//09.二叉树的最大深度【后序遍历 求 高度 代表 深度】
        //     方法二：     (充分表现出求深度 回溯的过程)
    int maxDepth(TreeNode* root) {
        if(!root)return 0;
        return 1+max(maxDepth(root->left),maxDepth(root->right));
    }
//10.二叉树的最小深度
//思路与上不同【得找到目标叶子结点 eg:2,NULL,3,NULL,6】最小深度是3
    int minDepth(TreeNode* root) {
        if(!root)return 0;
        //单独处理叶子结点【其实多余不需要单独处理，但是好理解】
        if(root->left==NULL&&root->right==NULL)
            return 1;
        else if(root->left==NULL){
            return 1+minDepth(root->right);
        }
        else if(root->right==NULL){
            return 1+minDepth(root->left);
        }
        else{
            return 1+min(minDepth(root->left),minDepth(root->right));
        }
    }
//解法二：广度优先搜索【遇到叶子节点再返回depth 】
        //非递归，迭代：：：时间非常之迅速
    int minDepth(TreeNode* root) {
        if(!root)return 0;
        int size = 0;
        int depth = 0;
        queue<TreeNode*>q_t;
        q_t.push(root);
        while(!q_t.empty()){
            TreeNode* node;
            depth++;
            size = q_t.size();
            for(int i=0;i<size;i++){
                node = q_t.front();
                q_t.pop();
                if(node->left==NULL&&node->right==nullptr){
                    return depth;
                }
                if(node->left){
                    q_t.push(node->left);
                }
                if(node->right)q_t.push(node->right);
            }
        }return depth;

    }
//11.完全二叉树的节点个数
    //解法一：当普通二叉树来看
    int countNodes(TreeNode* root) {
        if(!root)return 0;
        return 1+countNodes(root->left)+countNodes(root->right);   
    }
    //解法二：利用完全二叉树的特性
    int countNodes_trait(TreeNode* root) {
        if(!root)return 0;
        TreeNode* le = root->left;
        TreeNode* ri = root->right;
        int lnums = 0;
        int rnums = 0;
        while(ri){
            ri = ri->right;rnums++;
        }
        while(le){
            le=le->left;
            lnums++;
        }
        if(lnums==rnums){
            return (2<<lnums)-1;
        //位运算符：2<<1        =>  2^2     2<<0    =>      2
        }
        return 1+countNodes_trait(root->right)+countNodes_trait(root->left);
    }
//12.平衡二叉树【我的想法左子树高度-右子树高度 abs > 1 => false】
    //左右子树 高度差 < 1   [这里需要递归（左子树的子树也要满足上述要求....）]
//因为求深度可以从上到下去查 所以需要前序遍历（中左右），而高度只能从下到上去查，所以只能后序遍历（左右中）

//此时大家应该明白了既然要求比较高度，必然是要后序遍历。
class Solution {
    public://前序遍历【求深度】
        int result;
        void getDepth(TreeNode* node, int depth) {
            result = depth > result ? depth : result; // 中
    
            if (node->left == NULL && node->right == NULL) return ;
    
            if (node->left) { // 左
                depth++;    // 深度+1
                getDepth(node->left, depth);
                depth--;    // 回溯，深度-1
            }
            if (node->right) { // 右
                depth++;    // 深度+1
                getDepth(node->right, depth);
                depth--;    // 回溯，深度-1
            }
            return ;
        }
        int maxDepth(TreeNode* root) {
            result = 0;
            if (root == NULL) return result;
            getDepth(root, 1);
            return result;
        }
    };
    // int Height(TreeNode*root){
    //     if(!root)return 0;
    //     return 1+max(Height(root->left),Height(root->right));
    // }
    // bool isBalanced(TreeNode* root) {
    //     if(!root)return true;
    //     return !(abs(Height(root->left)-Height(root->right)) > 1);
    // }
//后序遍历 
    int GetHeight(TreeNode* root){
        if(!root) return 0;
        int LH = GetHeight(root->left);
        if(LH==-1)return -1;
        int RH = GetHeight(root->right);
        if(RH==-1)return -1;
        int res = abs(LH-RH);
        return (res>1)?-1:1+max(LH,RH);
    }
    bool isBalanced(TreeNode* root) {
        if(!root)return true;
        return !(GetHeight(root)==-1);
    }
//13.返回二叉树所有路径[从上向下遍历：前序遍历]
    //遍历完一条路径后需要                  回溯

//那有同学可能想，为什么不去定义一个 string& path 这样的函数参数呢，然后也可能在递归函数中展现回溯的过程，
// 但关键在于，path += to_string(cur->val); 每次是加上一个数字，这个数字如果是个位数，那好说，就调用一次path.pop_back()，但如果是 十位数，百位数，千位数呢？
//  百位数就要调用三次path.pop_back()，才能实现对应的回溯操作，这样代码实现就太冗余了。
    void traversal(TreeNode* cur,vector<string>& res,vector<int>& path){
        path.push_back(cur->val);
        if(cur->left==NULL&&cur->right==NULL){
            string spath;
           for(int i =0;i<path.size()-1;i++){
            spath += to_string(path[i]);
            spath += "->";
           } 
           spath += to_string(path[path.size()-1]);
           path.pop_back(); //回溯
           res.push_back(spath);
        }
        
        if(cur->left){    
            traversal(cur->left,res,path);
            path.pop_back();//回溯
        }
        
        if(cur->right){
            traversal(cur->right,res,path);
            path.pop_back();//回溯 
        }
    }
//以下是精简版本
    void traversal_brief(TreeNode* cur,string path,vector<string>&res){
        path += to_string(cur->val);
        if(cur->left&&cur->right){
            res.push_back(path);
        }
        if(cur->left){
            traversal_brief(cur->left,path+"->",res);//隐含回溯【值传递】
        }
        if(cur->right){
            traversal_brief(cur->right,path+"->",res);//隐含回溯【值传递】
        }
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> res;
        vector<int>path;
        if(!root)return {};
        traversal(root,res,path);
        return res;      
    }
//14.相同的树【对标 对称二叉树】
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p==NULL&&q!=NULL)return false;
        if(p!=NULL&&q==NULL)return false;
        if(p==NULL&&q==NULL)return true;
        if(p->val!=q->val)return false;
        bool left = isSameTree(p->left,q->left);
        bool right = isSameTree(p->right,q->right);
        return left&&right;
    }
//15.另一个 树的子树
    //我的想法：while循环找目标的根节点->在调用issame函数
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(root==NULL)return false;
        bool mid = false;
        if(root->val==subRoot->val)mid = isSameTree(root,subRoot);
        bool left = isSubtree(root->left,subRoot);
        bool right = isSubtree(root->right,subRoot);
        return mid||left||right;
    }
};
//N叉树的最大深度
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
class Solution {
    public:
//这里是深度优先搜索
//用层序遍历【广度优先亦可】
    int maxDepth(Node* root) {
        if(!root)return 0;
        int max = 0;     
        for(auto i:root->children){
            int a = maxDepth(i);
            max = (a>max)?a:max;
        }
        return max+1;
    }
        
};
int main(){
    tree t;
    t.root = new tree::TreeNode(5);
    t.root->left = new tree::TreeNode(4);
    t.root->left->left = new tree::TreeNode(1);
    t.root->left->right = new tree::TreeNode(2);
    t.root->right = new tree::TreeNode(6);
    t.root->right->left = new tree::TreeNode(7);
    t.root->right->right = new tree::TreeNode(8);
//先
    vector<int> res = t.Pretraversal();
    for(auto i: res){cout<<i<<" ";}
    res.clear();

    printf("\n");
    res = t.Midtraversal();
    for(auto i: res){cout<<i<<" ";}
    res.clear();
    
    printf("\n");
    res = t.Lasttraversal();
    for(auto i: res){cout<<i<<" ";}
    return 0;
}