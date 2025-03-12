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
    //TreeNode* root;
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
            traversal(cur->left,depth);
            depth--;
        }
        if(cur->right){
            depth++;
            traversal(cur->right,depth);
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
//20.最大二叉树【给定数组中的最大值做根节点，然后递归遍历 左右 子树】
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
//21.合并二叉树【同一相对位置：加；不统一：留】
   //[前序遍历]
   TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if(root1==NULL)return root2;
        if(root2==NULL)return root1;
        root1->val+=root2->val;
        root1->left = mergeTrees(root1->left,root2->left);
        root1->right = mergeTrees(root1->right,root2->right);
        return root1;
   }
/*
   二叉搜索树环节：
        中序遍历 形成的数组：递增
*/
//22.二叉搜索树中的搜索
   TreeNode* searchBST(TreeNode* root, int val) {
        if(root==NULL||root->val==val)return root;
        if(val>root->val)return searchBST(root->right,val);
        else return searchBST(root->left,val);
   }
//23.验证二叉搜索树
   //【不是单纯的判断root>left&&left<right】
                //而是大于左子树的所有值
                //而是小于右子树的所有值
    //方法一：中序遍历 -> 数组，相邻两个递增
    //法二：中序遍历 -> 设置 max ，遍历时要逐渐更新max，如果比max小就出问题了[这里初始化为Long——MIN，因为树的节点的最小是INT——MIN]          
    //方法三：快慢指针，pre永远指cur遍历过的结点的上一个遍历的节点 

    //法二：
    long max = LONG_MIN;
    bool isValidBST(TreeNode* root) {
        if(root==NULL)return true;
        bool leftis = isValidBST(root->left);
        if(root->val>max){
            max = root->val;
        }
        else return false;
        bool rightis = isValidBST(root->right);
        return leftis&&rightis;
    }
    //法三：
    TreeNode* pre = NULL;
    bool isValidBST(TreeNode* root) {
        if(root==NULL)return true;
        bool leftis = isValidBST(root->left);
    //这里加以判断：如果pre是NULL，直接赋值
        if(pre==NULL||root->val>pre->val){
            pre = root;        
        }
        else return false;
    
        bool rightis = isValidBST(root->right);
        return leftis&&rightis;
    }
//24.最小绝对差
    //解法基本同上
    TreeNode* pre2 = NULL;
    int result2 = INT_MAX;
    int getMinimumDifference(TreeNode* root) {
        if(root==NULL)return result2;
        int leftmin = getMinimumDifference(root->left);
        if(pre2!=NULL)
            result2 = min(result2,root->val-pre2->val);
        pre2 ==root;
        int rightmin = getMinimumDifference(root->right);
        return result2;
    }
//25.二叉搜索树众数
    //法一：哈希map -> max
    //法二：利用二叉搜索树特性  -> 中序遍历
                                //【同上】
    int maxcount = 0;
    int count = 0;
    TreeNode* pre = NULL;
    vector<int> res;
    void traversal(TreeNode* cur){
        if(cur==NULL)return ;
        traversal(cur->left);
        if(pre!=NULL){
            if(pre->val == cur->val){
                count++;
                if(count>maxcount){
                    res.clear();
                    res.push_back(cur->val);
                    maxcount = count;
                }
                else if(count==maxcount)res.push_back(cur->val);
            }
            else{
                count = 1;//这里有可能  解集合中的元素的频率都是1   【所以可以把这大端代码放到外面 【见下】】
                if(count>maxcount){
                    res.clear();
                    res.push_back(cur->val);
                    maxcount = count;
                }
                else if(count==maxcount)res.push_back(cur->val);
            }
        }   
        else{
            count = 1;
            maxcount = 1;
            res.push_back(cur->val);
        }
        
        pre = cur;
        traversal(cur->right);

    }
//优化
    void traversal_2(TreeNode* cur){
        if(cur==NULL)return ;
        traversal_2(cur->left);
        if(pre!=NULL){
            if(pre->val == cur->val){
                count++;
            }
            else{
                count = 1;//这里有可能  解集合中的元素的频率都是1   【所以可以把这大端代码放到外面 【见下】】
            }
        }   
        else{
            count = 1;
            maxcount = 1;
            //因为下面统一处理 众数，这里需要注释掉
            //res.push_back(cur->val);
        }
        if(count>maxcount){
            res.clear();
            res.push_back(cur->val);
            maxcount = count;
        }
        else if(count==maxcount)res.push_back(cur->val);
        pre = cur;
        traversal_2(cur->right);
    }
    vector<int> findMode(TreeNode* root) {
        traversal(root);
        return res;
    }
//26.二叉树的公共祖先[ 从下向上查找 ]
    //先分析第一种情况：目标节点在同一层
    //后序遍历  [类似求深度]
//在递归函数有返回值的情况下：如果要搜索一条边，递归函数返回值不为空的时候，立刻返回，如果搜索整个树，
//直接用一个变量left、right接住返回值，这个left、right后序还有逻辑处理的需要，
//也就是后序遍历中处理中间节点的逻辑（也是回溯）。
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // if(root==NULL)return NULL;
        // if(root==p||root==q)return root; //可以精进
        if(root==NULL||root==p||root==q)return root;
        TreeNode* left = lowestCommonAncestor(root->left,p,q);
        TreeNode* right = lowestCommonAncestor(root->right,p,q);

        if(left==NULL&&right!=NULL)return right;
        if(left!=NULL&&right==NULL)return left;
        if(left&&right)return root;
        return NULL;
    }
//27.二叉搜索树的最近公共祖先
    //因为本身有序，简单很多；同时大于目标，向左遍历。。。
    //递归
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root==NULL)return NULL;
        if(root->val>p->val&&root->val>q->val){
            return lowestCommonAncestor(root->left,p,q);
        }
        if(root->val<p->val&&root->val<p->val){
            return lowestCommonAncestor(root->right,p,q);
        }
        return root;
    }
    //迭代
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* cur = root;
        while(cur!=NULL){
            if(cur->val>p->val&&cur->val>q->val){
                cur = cur->left;
            }
            else if(cur->val<p->val&&cur->val<q->val){
                cur = cur->right;
            }
            else{break;}
        }return root;
    }
//28.二叉搜索树的插入
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root==NULL)return new TreeNode(val);
        if(root->val>val){
            root->right = insertIntoBST(root->right,val);
        }
        else{
            root->left = insertIntoBST(root->left,val);
        }
        return root;
    }
//29.二叉搜索树的删除
    /*多种情况
        没找到；没孩子；有一个孩子；有两个孩子
*/
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root==NULL)return NULL;
        if(root->val!=key){
            if(key>root->val){
                root->right = deleteNode(root->right,key);
            }
            else{root->left = deleteNode(root->left,key);}
            return root;
        }
        else{
            if(root->left==NULL&&root->right==NULL){delete root;return NULL;}
            else if(root->left==NULL&&root->right!=NULL){
                TreeNode* cur = root->right;
                delete root;
                return cur;
            }
            else if(root->left!=NULL&&root->right==NULL){
                TreeNode* cur = root->left;
                delete root;
                return cur;
            }
            else{
                TreeNode* cur = root->left;
                while(cur->right){
                    cur = cur->right;
                }
                cur->right = root->right;
                cur = root->left;
                delete root;
                return cur;
            }
        }
    }
//30.对于普通二叉树【非搜索二叉树】
    //操作两次
        //与右边的左下角交换
        //置为NULL(删除)
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return root;
        if (root->val == key) {
            if (root->right == nullptr) { // 这里第二次操作目标值：最终删除的作用
                return root->left;
            }
            TreeNode *cur = root->right;
            while (cur->left) {
                cur = cur->left;
            }
            swap(root->val, cur->val); // 这里第一次操作目标值：交换目标值其右子树最左面节点。
        }
        root->left = deleteNode(root->left, key);
        root->right = deleteNode(root->right, key);
        return root;
    }
//31.修建二叉搜索树
    //实质上删除一定范围内的节点
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if(root==NULL){
            return NULL;
        }
        if(root->val<low){
            TreeNode* right =trimBST(root->right,low,high);
            return right;
        }
        if(root->val>high){
            TreeNode* left = trimBST(root->left,low,high);
            return left;
        }
        root->left = trimBST(root->left,low,high);
        root->right = trimBST(root->right,low,high);
        return root;
    }
//32.将有序数组转为二叉搜索+平衡树
    //这里要求平衡树，一定是从中间往两边
    TreeNode* traversal(vector<int>& nums,int left,int right){
        if(left<=right){
            // int mid= (left+right)/2;        
        //这样，在数字很大时不会溢出
            int mid = left + (right - left)/2;
            TreeNode* root = new TreeNode(nums[mid]);
            root->left = traversal(nums,left,mid-1);
            root->right = traversal(nums,mid+1,right);
            return root;
        }
        return NULL;
        
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        TreeNode* root = traversal(nums,0,nums.size()-1);
        return root;
    }
//33.二叉搜索树->累加树
    //联想昨天所学：per -> cur所遍历的节点前面的
    //右 中 左
//结点个数>=0;节点值有正有负
    int result = 0;
    TreeNode* convertBST(TreeNode* root) {
        if(root==NULL)return root;
        //right
        root->right = convertBST(root->right);
        //中
        root->val+=result;
        result = root->val;
        //left
        root->left = convertBST(root->left);
        
        return root;
    }
};
int main(){
    return 0;
}