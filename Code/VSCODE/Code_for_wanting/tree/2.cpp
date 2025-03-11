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
//16.左叶子之和
    int sumOfLeftLeaves(TreeNode* root) {
        if(root->left&&root->left->left==NULL&&root->right->right==NULL){
            return root->left->val;
        }
        int left = 0;
        if(root->left){
            left+=sumOfLeftLeaves(root->left);
        }
        int right =0;
        if(root->right){
            right+=sumOfLeftLeaves(root->right);
        }
        return left+right;
    }
//17.左下角的值
    //层序遍历->最底层+第一个元素
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode*> q_t;
        vector<vector<int>> vv;
        if(root)q_t.push(root);
        while(!q_t.empty()){
            int size = q_t.size();
            TreeNode* cur;
            vector<int> res;
            for(int i =0;i<size;i++){
                cur = q_t.front();
                res.push_back(cur->val);
                q_t.pop();
                if(cur->left)q_t.push(cur->left);
                if(cur->right)q_t.push(cur->right);
            }
            vv.push_back(res);
        }
        return vv[vv.size()-1][0];

        //优化后
        queue<TreeNode*>qq;
        qq.push(root);//因为节点数量>=1所以不需要判断
        TreeNode* a;
        while(!qq.empty()){
            a = qq.front();
            qq.pop();
            if(a->left)qq.push(a->left);//先右
            if(a->right)qq.push(a->right);//后左
        }//保证最后返回值是最左端的
        return a->val;
    }
    //方法三：前序遍历 + 回溯
    int result;
    int MaxDepth = INT_MIN;
    void traversal(TreeNode* cur,int depth){
        if(cur->left==NULL&&cur->right==NULL){
            if(depth>MaxDepth)
            {
                result = cur->val;
                MaxDepth = MaxDepth > depth ? MaxDepth : depth;
            }return;
        }
        if(cur->left){
            depth++;
            traversal(root->left,depth);
            depth--;
        }
        if(cur->right){
            depth++;
            traversal(root->right,depth);
            depth--;
        }
    }
    int findBottomLeftValue3(TreeNode* root) {
        traversal(root,1);
        return result;
    }
//18.路径总和 【等于目标和的 [根节点] 到 [叶节点] 路径】
    //前序+回溯
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(!root)return false;
        if(targetSum - root->val==0){
            if(root->left==NULL&&root->right==NULL)
                return true;
            return hasPathSum(root->left,targetSum-root->val)||hasPathSum(root->right,targetSum-root->val);
        }
        else if(targetSum - root->val >0){
            return hasPathSum(root->left,targetSum-root->val)||hasPathSum(root->right,targetSum-root->val);
        }
        else{
            return false;
        }
    }
//19.根据 后序和中序 构造二叉树
    //  后续数组 大小为1，叶子节点，return root
    //  后续数组最后一个元素，为节点元素
    //  寻找中序数组的对应位置
    //  切中序数组
    //  切后序数组
    //  递归处理左右区间
//难以分割的时候【打印日志->把各个区间打印出来】
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if(postorder.empty())return NULL;
        if(postorder.size()==1)return new TreeNode(postorder.back());
        int rootvalue = postorder[postorder.size()-1];
        TreeNode* root = new TreeNode(rootvalue);
        int index;
        for(int i =0;i<inorder.size();i++){
            if(inorder[i]==rootvalue){
                index = i;break;
            }
        }
        vector<int> li(inorder.begin(),inorder.begin()+index);
        vector<int> lp(postorder.begin(),postorder.begin()+index);

        vector<int> ri(inorder.begin()+index+1,inorder.end());
        vector<int> rp(postorder.begin()+index,postorder.end()-1);
        root->left = buildTree(li,lp);
        root->right = buildTree(ri,rp);
        return root;
    }
    //若果是 只知道 后序和前序=>无法推断二叉树【中左右，和左右中；左右的顺序无法确定】
    /*     1    1
        2          2
    3                   3
    
    */
//最大二叉树【给定数组中的最大值做根节点，然后递归遍历 左右 子树】
   TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if(nums.size()==0)return NULL;
        if(nums.size()==1)return new TreeNode(nums[0]);
        TreeNode* root;
        int index = 0;
        int max = -1;
        for(int i = 0;i<nums.size();i++){
            if(nums[i]>max){
                max = nums[i];index = i;
            }
        }
        vector<int> ln(nums.begin(),nums.begin()+index);
        vector<int> rn(nums.begin()+index+1,nums.end());
        root->left = constructMaximumBinaryTree(ln);
        root->right = constructMaximumBinaryTree(rn);
        return root;
   }
};
int main(){
    return 0;
}