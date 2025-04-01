#include<bits/stdc++.h>
using namespace std;
//打家劫舍1：邻家不能偷
class Solution {
    public:
        int rob(vector<int>& nums) {
            if(nums.size()==1) return nums[0];
            vector<int> dp(nums.size());
            dp[0] = nums[0];
            dp[1] = max(nums[0],nums[1]);
        //定义：dp[j]:遍历到第j个物品【考虑了j】可以拿到的最大价值
            for(int i = 2;i<nums.size();i++){
                    //偷                      不偷
                dp[i] = max(nums[i]+dp[i-2],dp[i-1]);
            }
            return dp[nums.size()-1];
        }
    };
//打家劫舍2：成环了
/*
    1,2,3,4
        1 4不能同时偷
            分析：1> 只考虑 中间
                 2> 不考虑 左边
                 3> 不考虑 右边
                2和3分别可以包括1
                    所以结果取2，3的max
*/
class Solution {
    private:
        int rob1(const vector<int>& nums){
            if(nums.size()==0)return 0;
            if(nums.size()==1)return nums[0];
            vector<int> dp(nums.size(),0);
            dp[0] = nums[0];
            dp[1] = max(nums[0],nums[1]);
            for(int i = 2;i<nums.size();i++){
                dp[i] = max(dp[i-1],dp[i-2]+nums[i]);
            }
            return dp[nums.size()-1];
        }
    public:
        int rob(vector<int>& nums) {
            if(nums.size()==1)return nums[0];
            int left = rob1(vector<int>(nums.begin(),nums.end()-1));
            int right = rob1(vector<int>(nums.begin()+1,nums.end()));
            return max(left,right);
        }
    };
//打家劫舍3:树状住户
/*相邻不偷
    对于每一个节点 返回 dp[0] 没偷 dp[1] 偷
*/ 
class Solution {
    private:
     struct TreeNode {
             int val;
             TreeNode *left;
             TreeNode *right;
             TreeNode() : val(0), left(nullptr), right(nullptr) {}
             TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
             TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
         };
    public:// 后序遍历
         vector<int> traversal(TreeNode* root){
            if(root==NULL)return {0,0};
            vector<int> leftdp = traversal(root->left);//左
            vector<int> rightdp = traversal(root->right);//右
            vector<int> dp(2,0);
            //偷
            dp[1] = leftdp[0]+rightdp[0] + root->val;
            //不偷
            dp[0] = max(leftdp[0],leftdp[1]) + max(rightdp[0],rightdp[1]);
            return dp;
         }
        int rob(TreeNode* root) {
            if(root==NULL) return 0;
            vector<int> result = traversal(root);
            return max(result[0],result[1]);
        }
    };

int main(){

    return 0;
}