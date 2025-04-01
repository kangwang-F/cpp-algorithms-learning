#include<bits/stdc++.h>
using namespace std;
//回文字串[连续]
class Solution {
    public:
        int countSubstrings(string s) {
            vector<vector<bool>> dp(s.size(),vector<bool>(s.size(),false));
    //dp[i][j]:[i-j]是否是回文字串 
            int result = 0;
            for(int i = s.size() - 1;i>=0;i--){
                for(int j = i;j<s.size();j++){
                    // 相等
                    if(s[i]==s[j]){
                        if(j-i<=1){
                            dp[i][j] = true;
                            result++;
                        }   //这里看的是左下角
                        else if((dp[i+1][j-1]==true)){
                            dp[i][j] = true;    //递推公式
                            result++;   
                        }
                    }
                } 
            }
            return result;
        }
    };
//最长回文子序列[非必要连续]
class Solution {
    public:
        int longestPalindromeSubseq(string s) {
            vector<vector<int>> dp(s.size(),vector<int>(s.size(),0));
    //dp[i][j]:[i~j]中最长回文子序列的长度
            for(int i = 0;i<s.size();i++)dp[i][i] = 1;
            for(int i = s.size()-1;i>=0;i--){
                for(int j = i+1;j<s.size();j++){
                    if(s[i]==s[j]){
                        dp[i][j] = dp[i+1][j-1] + 2;//多两个字符
                    }
                    else{ // 不等说明不能同时加入 i和j,那么可以试试去掉i或者j的最大值 
                        dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
                    }
                }
            }
            return dp[0][s.size()-1];
        }
    };
int main(){
    return 0;
}