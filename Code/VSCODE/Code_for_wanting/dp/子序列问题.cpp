#include<bits/stdc++.h>
using namespace std;
//最长递增子序列
class Solution {
    public:
        int lengthOfLIS(vector<int>& nums) {
            if(nums.size()<=1)return nums.size();
        //初始化 [单个数字本身就算一个子序列]
            vector<int> dp(nums.size(),1);
        //dp[i] 表示考虑上i的最长递增子序列的长度 
            int result = 0;
            for(int i = 1;i<nums.size();i++){
                for(int j = 0;j<i;j++){
                    if(nums[i]>nums[j]){
                        dp[i] = max(dp[i],dp[j]+1);
                    }
                }
                result = max(result,dp[i]);
            }
            return result;
        }
    };
//最长 连续 递增子序列
class Solution {
    public:
        int findLengthOfLCIS(vector<int>& nums) {
            if(nums.size()<=1)return nums.size();
            vector<int> dp(nums.size(),1);
            int result = 0;
            for(int i = 1;i<nums.size();i++){
                if(nums[i]>nums[i-1]){
                    dp[i] = dp[i-1]+1;
                }
                result = max(result,dp[i]);
            }
            return result;
        }
    };
//最长重复子数组【连续子序列】
class Solution {
    public:
        int findLength(vector<int>& nums1, vector<int>& nums2) {
            vector<vector<int>> dp(nums1.size()+1,vector<int>(nums2.size()+1,0));
//dp[i][j]表示nums1[i-1]为结尾的数字，和nums2[j-1]为结尾的数字的最长重复子序列
            //初始化
                //dp[0][i] = 0
            
                //dp[i][0] = 0
            //遍历顺序
            int result = 0;
            for(int i = 1;i<=nums1.size();i++){
                for(int j = 1;j<=nums2.size();j++){
                    if(nums1[i-1]==nums2[j-1]){
                        dp[i][j] = 1+dp[i-1][j-1];//递推公式
                    }
            //要求连续
                //不等直接从0开始
                    // else{
                    //     dp[i][j] = dp[i-1][j-1];
                    // }
                    result = max(result,dp[i][j]);
                }
                
            }
            return result;
        }
    };
//最长公共子序列
class Solution {
    public:
        int longestCommonSubsequence(string text1, string text2) {
            vector<vector<int>> dp(text1.size()+1,vector<int>(text2.size()+1,0));
//dp[i][j]:text1[i-1]为结尾，text[j-1]为结尾的最长公共子序列长度
            for(int i = 1;i<=text1.size();i++){
                for(int j =1;j<=text2.size();j++){
                    if(text1[i-1]==text2[j-1]){
                        dp[i][j] = dp[i-1][j-1]+1;
                    }
                    else{//不要求连续
                        dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
                    }
                }
            }
            return dp[text1.size()][text2.size()];
        }
    };
//不相交的线 == 最长公共子序列问题
class Solution {
    public:
        int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
            vector<vector<int>> dp(nums1.size()+1,vector<int>(nums2.size()+1,0));
            for(int i = 1;i<nums1.size();i++){
                for(int j = 1;j<nums2.size();j++){
                    if(nums1[i-1]==nums2[j-1]){
                        dp[i][j] = dp[i-1][j-1]+1;
                    }
                    else{
                        dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
                    }
                }
            }
            return dp[nums1.size()][nums2.size()];
        }
    };
//最大连续子序和
class Solution {
    public:
        //贪心
        //局部最优：如果目前的sum<0则归零,继续往后加
        int maxSubArray(vector<int>& nums) {
            // int sum = 0;
            // int result = INT_MIN;
            // for(int i =0;i<nums.size();i++){
            //     if(sum<0)sum=0;
            //     sum += nums[i];
            //     result = max(sum,result);
            // }
            // return result;
            
            vector<int> dp(nums.size(),0);
    //dp[i]:到nums[i]的最大字序和
        //包括下标i之前的最大连续子序列和为dp[i]
            dp[0] = nums[0];
    //初始化：nums:[-1]  sum = -1【子序列最起码有一个元素】
            int result = dp[0];
            for(int i =1;i<nums.size();i++){
                dp[i] = max(dp[i-1]+nums[i],nums[i]);
                result = max(result,dp[i]);
            }
            return result;
        }
    };
//判断子序列
class Solution {
    public:
                //s = "abc", t = "ahbgdc"  判s是不是t的子序列
                    //遇到不同可以考虑删除t[j-1]
        bool isSubsequence(string s, string t) {
            vector<vector<int>> dp(s.size()+1,vector<int>(t.size()+1,0));
//dp[i][j]:text1[i-1]为结尾，text[j-1]为结尾的最长公共子序列长度
        for(int i = 1;i<=s.size();i++){
            for(int j =1;j<=t.size();j++){
                if(s[i-1]==t[j-1]){
                    dp[i][j] = dp[i-1][j-1]+1;
                }
                else{//不要求连续
            //不同之处：本题这里只需考虑删除t[j-1]【因为s是被查找的】
                    //dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
                    dp[i][j] = dp[i][j-1];
                }
            }
        }
        return dp[s.size()][t.size()]==s.size();
        }
    };
//不同子序列
class Solution {
    public:
//s = "babgbag", t = "bag"
        int numDistinct(string s, string t) {
            vector<vector<int>> dp(s.size()+1,vector<int>(t.size()+1,0));
        //dp[i][j]: s[i-1]为结尾中有t[j-1]为结尾的子序列个数
            //初始化
                //dp[i][0] = 1
                //dp[0][i] = 0
                //dp[0][0] = 1  0个数组中仍然有一个0的子序列
            for(int i =0;i<=s.size();i++){
                dp[i][0] = 1;
            }
            for(int i = 1;i<=t.size();i++){
                dp[0][i] = 0;
            }
            for(int i = 1;i<=s.size();i++){
                for(int j = 1;j<=t.size();j++){
                    if(s[i-1]==t[j-1]){
            //既然要表示s[i-1]中有多少个t[j-1]
                //那么不仅要累加 本个字母匹配的bag，还有之前出现过的g匹配到的bag
                        dp[i][j] = dp[i-1][j-1]+dp[i-1][j];
                    }
            //如果不匹配：dp[i][j] = dp[i-1][j]: s[i-2]为结尾有多少个t[i-1]为结尾的子序列【方便之后累加】
        //即：babg 和 bag 的g配对成功后 应该累加[b][a]即bab中有多少个ba子序列 == ba 中 有多少个 ba
                                                                    //【由于最后的b匹配失败】
                    else{
                        dp[i][j] = dp[i-1][j];
                    }
                }
            }
            return dp[s.size()][t.size()];
        }
    };
//两个字符串的删除操作
class Solution {
    public:     //最长公共子序列
        int minDistance(string word1, string word2) {
            vector<vector<int>> dp(word1.size(),vector<int>(word2.size(),0));
            //钧初始化为0
            for(int i = 1;i<=word1.size();i++){
                for(int j =1;j<word2.size();j++){
                    if(word1[i-1]==word2[j-1]){
                        dp[i][j] = dp[i-1][j-1] + 1;
                    }
                    else{
                        dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
                    }
                }
            }
            return word1.size()-dp[word1.size()][word2.size()]+word2.size()-dp[word1.size()][word2.size()];
        }
    };
//编辑距离
class Solution {
    public:                 //word1 -> word2
        int minDistance(string word1, string word2) {
            vector<vector<int>> dp(word1.size()+1,vector<int>(word2.size()+1,0));
            //初始化
                //dp[0][i] = i
                //dp[i][0] = i;
            for(int i = 0;i<=word1.size();i++){
                dp[i][0] = i;
            }
            for(int i = 0;i<=word2.size();i++){
                dp[0][i] = i;
            }
            for(int i = 1;i<=word1.size();i++){
                for(int j =1;j<=word2.size();j++){
                    if(word1[i-1]==word2[j-1]){//相等，编辑次数不需要加
                        dp[i][j] = dp[i-1][j-1];
                    }
                    else{//不相等
                        dp[i][j] = min(
                            dp[i-1][j] + 1,//删除
                            min(dp[i][j-1] + 1,//增加【相当于减少一个匹配的元素】
                                dp[i-1][j-1] +1 //替换
                            )
                        );
                    }
                }
            }
            return dp[word1.size()][word2.size()];
        }
    };
int main(){
    return 0;
}