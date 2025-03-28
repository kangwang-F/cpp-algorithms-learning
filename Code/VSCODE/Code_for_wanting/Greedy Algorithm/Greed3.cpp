#include<bits/stdc++.h>
using namespace std;
//单调递增的数字【小于等于n的最大的单调递增】
//暴力
class Solution {
    private:
        // 判断一个数字的各位上是否是递增
        bool checkNum(int num) {
            int max = 10;
            while (num) {
                int t = num % 10;
                if (max >= t) max = t;
                else return false;
                num = num / 10;
            }
            return true;
        }
    public:
        int monotoneIncreasingDigits(int N) {
            for (int i = N; i > 0; i--) { // 从大到小遍历
                if (checkNum(i)) return i;
            }
            return 0;
        }
    };
/*
    思路：
        例如：98，一旦出现strNum[i - 1] > strNum[i]的情况（非单调递增），首先想让strNum[i - 1]--，
            然后strNum[i]给为9，这样这个整数就是89，即小于98的最大的单调递增整数。
        要用从后向前遍历：前面的可以用到后面的结果
            332 模拟
                前->后 332->332->329 x
                后->前 332 -> 329-> 229
*/
class Solution {
    public:
        int monotoneIncreasingDigits(int n) {
            string nums = to_string(n);
        //这里并不是最优的
    //eg：312-> 312->292 X [299]   一旦修改高位【低位应该全部赋值为9】
            int flag = nums.size();
            for(int i = nums.size()-1;i>0;i--){
                if(nums[i]<nums[i-1]){
                    // nums[i] = '9';
                    flag = i;
                    nums[i-1]--;
                }
            }
            for(int i = flag;i<nums.size();i++){
                nums[i] = '9';
            }
            return stoi(nums);
        }
    };
//监控二叉树
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
/*
    递归遍历【左右中】
        局部最优【0.没被覆盖1.有监控2.被覆盖】
            1.叶子结点的父节点 得有 监控【叶子节点的NULL结点应该返回【2.被覆盖】->2】
            2.被覆盖的结点的父节点的父节点需要监控
            3.放监控的父节点被覆盖
            4.根节点例外
*/
class Solution {
    public: struct TreeNode {
            int val;
            TreeNode *left;
            TreeNode *right;
            TreeNode() : val(0), left(nullptr), right(nullptr) {}
            TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
            TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
        };
    public:
        int result;
        int traversal(TreeNode* p){
            if(p==NULL){return 2;}//1叶子结点的NULL结点
            int l = traversal(p->left);
            int r = traversal(p->right);
            if(l==0||r==0){//1
                result++;
                return 1;
            }
            if(l==1||r==1){
                return 2;
            }
            return 0;
        }
        int minCameraCover(TreeNode* root) {
            result = 0;
            if(traversal(root) == 0){
                result++;//4
            }
            return result;
        }
    };