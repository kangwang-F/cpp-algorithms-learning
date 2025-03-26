#include<bits/stdc++.h>
using namespace std;
class Solution {
    public:
        int numTrees(int n) {
            vector<int> dp(n+1,0);
            dp[0] = dp[1] = 1;
            for(int i = 2;i<=n;i++){
                for(int j = 0;j<i;j++){
                    dp[i] += dp[j] * dp[i-j-1];
                }
            }
            for_each(dp.begin(),dp.end(),[](int num){cout<<num<<" ";});
            return dp[n];
            
        }
    };
int main(){
    Solution s;
    s.numTrees(10);
    return 0;
}