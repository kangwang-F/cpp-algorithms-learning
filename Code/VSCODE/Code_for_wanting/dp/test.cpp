#include <bits/stdc++.h>
using namespace std;
// int main() {
//   ios::sync_with_stdio(false);
//   cin.tie(0);
//   cout.tie(0);
//   //一共n阶，一次最多爬m
//   int n = 0, m = 0;
//   cin >> n >> m;
//   vector<int> dp(n + 1, 0);
//   dp[0] = 1;
//   for (int i = 1; i <= n; i++) {   //背包[正序]
//     for (int j = 1; j <= m; j++) { //一次爬1 ~ m
//         if(i>=j){
//             // if(dp[i]<+INT_MAX - dp[i-j]){
//             //     dp[i] += dp[i - j];
//             // }
//             dp[i] += dp[i - j];
//         }
//     }
//   }
//   for_each(dp.begin(),dp.end(),[](int num){cout<<num<<" ";});
//   cout << dp[n];
//   return 0;
//}
class Solution_me {
  public:
      int maxProfit(vector<int>& prices) {
          vector<vector<int>> dp(prices.size(),vector<int>(4,0));
          dp[0][0] = -prices[0];
          dp[0][1] = dp[0][2] = dp[0][3] = 0;
          for(int i = 1;i<prices.size();i++){
              dp[i][0] = max(dp[i-1][0],max(dp[i-1][2]-prices[i],dp[i-1][3]-prices[i]));
              dp[i][1] = max(dp[i-1][1],dp[i-1][0] + prices[i]);//卖出
              dp[i][2] = max(dp[i-1][2],dp[i-1][3]);//持续卖出
              dp[i][3] = dp[i-1][1];
          }
          for(int i = 0;i<prices.size();i++){
            for(int j = 0;j<4;j++){
              cout<<dp[i][j]<<" ";
            }cout<<endl;
          }
          return dp[prices.size()-1][1];
      }
  };
  class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            int n = prices.size();
            if (n == 0) return 0;
            vector<vector<int>> dp(n, vector<int>(4, 0));
            dp[0][0] -= prices[0]; // 持股票
            for (int i = 1; i < n; i++) {
                //持股
                dp[i][0] = max(dp[i - 1][0], max(dp[i - 1][3] - prices[i], dp[i - 1][1] - prices[i]));
                dp[i][1] = max(dp[i - 1][1], dp[i - 1][3]);//持续买出
                dp[i][2] = dp[i - 1][0] + prices[i];//卖出
                dp[i][3] = dp[i - 1][2];
            }
            for(int i = 0;i<prices.size();i++){
              for(int j = 0;j<4;j++){
                cout<<dp[i][j]<<" ";
              }cout<<endl;
            }
            return max(dp[n - 1][3], max(dp[n - 1][1], dp[n - 1][2]));
        }
    };
int main(){
  vector<int> prices = {1,2,3,0,2};
  Solution_me s_m;
  s_m.maxProfit(prices);

  Solution s;
  s.maxProfit(prices);
  return 0;
}