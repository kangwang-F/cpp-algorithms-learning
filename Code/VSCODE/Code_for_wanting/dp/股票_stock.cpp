/*买卖股票的最佳时机问题
    nums: 
*/
#include<bits/stdc++.h>
using namespace std;
//1.只能买卖一次
/*
    dp[i][0]持有
    dp[i][1]不持有
*/
class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            vector<vector<int>> dp(prices.size(),vector<int>(2,0));
            dp[0][0] = -prices[0];
            dp[0][1] = 0;
            for(int i = 1;i<prices.size();i++){
                //这里只能买一次            所以买入时初始值为0
                dp[i][0] = max(dp[i-1][0],-prices[i]);
                dp[i][1] = max(dp[i-1][1],dp[i-1][0]+prices[i]);
            }
            return dp[prices.size()][1];
        }
    };
//2.可以反复买卖
class Solution{
    //局部最优：收集每天的正利润，全局最优：求得最大利润。
        public: 
        int maxProfit(vector<int>& prices) {
        //贪心
            // int result = 0;
            // for(int i = 1;i<prices.size();i++){
            //     //收集每天的正利润
            //     result += max(0,prices[i]-prices[i-1]);
            // }
            // return result;
            vector<vector<int>> dp(prices.size(),vector<int>(2,0));
            dp[0][0] = -prices[0];
            dp[0][1] = 0;
            for(int i = 1;i<prices.size();i++){
                dp[i][0] = max(dp[i-1][0],dp[i-1][1]-prices[i]);
            //// 注意这里是和121. 买卖股票的最佳时机唯一不同的地方。
                dp[i][1] = max(dp[i-1][1],dp[i-1][0]+prices[i]);
            }
            return dp[prices.size()-1][1];
        }
    };
//3.只能完成两笔交易
/*
    dp[0] 不操作    //不必要
    dp[1] 第一次持股
    dp[2] 第一次不持股
    dp[3] 第二次持股
    dp[4] 第二次不持股
*/
class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            vector<vector<int>> dp(prices.size(),vector<int>(2*2+1,0));
            dp[0][0] = 0;
            dp[0][1] = -prices[0];
            dp[0][2] = 0;
            dp[0][3] = -prices[0];
            dp[0][4] = 0;
            for(int i = 1;i<prices.size();i++){
                dp[i][0] = dp[i-1][0];//不操作
                dp[i][1] = max(dp[i-1][1],dp[i-1][0]-prices[i]);//第一次持股
                dp[i][2] = max(dp[i-1][2],dp[i-1][1]+prices[i]);//第一次不持股
                dp[i][3] = max(dp[i-1][3],dp[i-1][2]-prices[i]);
                dp[i][4] = max(dp[i-1][4],dp[i-1][3]+prices[i]);
            }
            return dp[prices.size()-1][4];
        }
    };
//4.可以买卖k次
/*
    仅需对以上代码下表进行改动
*/
class Solution {
    public:
        int maxProfit(int k, vector<int>& prices) {
            vector<vector<int>> dp(prices.size(),vector<int>(2*k+1,0));
            for(int i = 1;i<2*k;i+=2){
                dp[0][i] = -prices[i];
            }
            // dp[0][0] = 0;
            // dp[0][1] = -prices[0];
            // dp[0][2] = 0;
            // dp[0][3] = -prices[0];
            // dp[0][4] = 0;
            for(int i = 1;i<prices.size();i++){
                for(int j = 1;i<2*k;i+=2){
                    dp[i][0] = dp[i-1][0];//不操作
                    dp[i][j] = max(dp[i-1][j],dp[i-1][j-1]-prices[i]);//第一次持股
                    dp[i][j+1] = max(dp[i-1][j+1],dp[i-1][j]+prices[i]);//第一次不持股
                    // dp[i][3] = max(dp[i-1][3],dp[i-1][2]-prices[i]);
                    // dp[i][4] = max(dp[i-1][4],dp[i-1][3]+prices[i]);
                }               
            }
            return dp[prices.size()-1][2*k];
        }
    };
//5.含冷冻期
/*
    0 持股 
    1 卖出
    2 持续卖出(下一天按可以买入)
    3 冷冻期
*/
class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            vector<vector<int>> dp(prices.size(),vector<int>(4,0));
            dp[0][0] = -prices[0];
            dp[0][1] = dp[0][2] = dp[0][3] = 0;
            for(int i = 1;i<prices.size();i++){
                dp[i][0] = max(dp[i-1][0],max(dp[i-1][2]-prices[i],dp[i-1][3]-prices[i]));
        //把所有卖出利润最大值往后覆盖
                dp[i][1] = max(dp[i-1][1],dp[i-1][0] + prices[i]);//卖出
                dp[i][2] = max(dp[i-1][2],dp[i-1][3]);//持续卖出
                dp[i][3] = dp[i-1][1];
            }
            return dp[prices.size()-1][1];
        }
    };
//老师写法
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
                dp[i][1] = max(dp[i - 1][1], dp[i - 1][3]);//持续买入
                dp[i][2] = dp[i - 1][0] + prices[i];//卖出
                dp[i][3] = dp[i - 1][2];
            }
            return max(dp[n - 1][3], max(dp[n - 1][1], dp[n - 1][2]));
        }
    };
//6.含手续费
class Solution {
    public:
        int maxProfit(vector<int>& prices, int fee) {
            vector<vector<int>> dp(prices.size(),vector<int>(2,0));
            dp[0][0] = -prices[0]-fee;
            dp[0][1] = 0;
            for(int i = 1;i<prices.size();i++){
                dp[i][0] = max(dp[i-1][0],dp[i-1][1]-prices[i]-fee);
                dp[i][1] = max(dp[i-1][1],dp[i-1][0]+prices[i]);
            }      
            return dp[prices.size()-1][1];
        }
    };