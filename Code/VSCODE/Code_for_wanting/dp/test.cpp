#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  //一共n阶，一次最多爬m
  int n = 0, m = 0;
  cin >> n >> m;
  vector<int> dp(n + 1, 0);
  dp[0] = 1;
  for (int i = 1; i <= n; i++) {   //背包[正序]
    for (int j = 1; j <= m; j++) { //一次爬1 ~ m
        if(i>=j){
            // if(dp[i]<+INT_MAX - dp[i-j]){
            //     dp[i] += dp[i - j];
            // }
            dp[i] += dp[i - j];
        }
    }
  }
  for_each(dp.begin(),dp.end(),[](int num){cout<<num<<" ";});
  cout << dp[n];
  return 0;
}