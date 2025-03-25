#include<iostream>
#include<bits/stdc++.h>
using namespace std;
/*动态规划[Dynamic[动态的] Programming[规划，编程，设计]]
    动态规划中每一个状态一定是由上一个状态推导出来的，
    这一点就区分于贪心，贪心没有状态推导，而是从局部直接选最优的，

    斐波那契数列     
    背包问题
    打家劫舍
    股票问题
    子序列问题
    
    五部曲：
        dp下标定义
        递推公式
        初始化
        遍历顺序
        打印dp数组[检查]
*/
//1. 斐波那契数
class Solution {
    public:
        int fib(int n) {
            if(n==0)return 0;

            // vector<int> dp(n+1,0);
            // dp[1] = 1;//初始化【dp[0]题目要求为0】
            // for(int i = 2;i<n+1;i++){
            //     dp[i] = dp[i-1]+dp[i-2];//递归公式
            // }
            //return dp[n];

            //滚动数组
            int num1 = 0,num2 = 1;
            for(int i = 2;i<n+1;++i){
                int temp = num1 + num2;
                num1 = num2;
                num2 = temp;
            }
            return num2;
        }
    };
//2.爬楼梯
/*
    到第五层的方式：到第三层的方法数[跨两部] + 到底四层的方法数[跨一步]
*/
class Solution {
    public:
        int climbStairs(int n) {
            if(n==1)return 1;
            vector<int> dp(n+1,1);
            //dp[1] = 1;
            for(int i = 2;i<n+1;i++){
                dp[i] = dp[i-1]+dp[i-2];
            }      
            return dp[n];
        }
    };
//3.使用最小花费爬楼梯
/*一旦你支付此费用，即可选择向上爬一个或者两个台阶。
你可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯。*/
class Solution {
    public:
        int minCostClimbingStairs(vector<int>& cost) {
            //目标要上到顶层，即    dp[cost.size()]
            vector<int> dp(cost.size()+1,0);
    //可以直接从底层上到0或者1;所以dp[0]/dp[1]最小花费是0
            // dp[0] = 0;   
            // dp[1] = 0;
            for(int i = 2;i<cost.size()+1;i++){
                dp[i] = min(dp[i-1]+cost[i-1],dp[i-2]+cost[i-2]);
            }
            return dp[cost.size()];
        }
    };
//4.不同路径
/*
    机器人只能向下或者向右走
    在 m*n 的表格中【start在左上角，end在右下角】
*/

//以下是深度优先搜索的写法【超时了】
//此时问题就可以转化为求二叉树叶子节点的个数，代码如下：【时间复杂度在后面】
class Solution {
private:
    int dfs(int i, int j, int m, int n) {
        if (i > m || j > n) return 0; // 越界了
        if (i == m && j == n) return 1; // 找到一种方法，相当于找到了叶子节点
        return dfs(i + 1, j, m, n) + dfs(i, j + 1, m, n);
    }
public:
    int uniquePaths(int m, int n) {
        return dfs(1, 1, m, n);
    }
};
// 大家如果提交了代码就会发现超时了！
// 来分析一下时间复杂度，这个深搜的算法，其实就是要遍历整个二叉树。
// 这棵树的深度其实就是m+n-1（深度按从1开始计算）。
// 那二叉树的节点个数就是 2^(m + n - 1) - 1。
//可以理解深搜的算法就是遍历了整个满二叉树（其实没有遍历整个满二叉树，只是近似而已）
// 所以上面深搜代码的时间复杂度为O(2^(m + n - 1) - 1)，可以看出，这是指数级别的时间复杂度，是非常大的。
class Solution {
    public:
        int uniquePaths(int m, int n) {
            vector<vector<int>> dp(m,vector<int>(n,1));
            //初始化：第一行第一列的dp都是1【只有一种方法】
            for(int i = 1;i<m;++i){
                for(int j = 1;j<n;j++){
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
                }
            }
            return dp[m-1][n-1];
        }
    };
//方法三：数论
/*在这m + n - 2 步中，一定有 m - 1 步是要向下走的，不用管什么时候向下走。
那么有几种走法呢？ 可以转化为，给你m + n - 2个不同的数，随便取m - 1个数，有几种取法。
即求
    C^m-1
      m+n-2
*/
class Solution {
    public:
        int uniquePaths(int m, int n) {
            int numerator = 1, denominator = 1;
            int count = m - 1;
            int t = m + n - 2;
            while (count--) numerator *= (t--); // 计算分子，此时分子就会溢出
            for (int i = 1; i <= m - 1; i++) denominator *= i; // 计算分母
            return numerator / denominator;
        }
    };
//需要在计算分子的时候，不断除以分母，代码如下：
    
class Solution {
public:
    int uniquePaths(int m, int n) {
        long long numerator = 1; // 分子
        int denominator = m - 1; // 分母
        int count = m - 1;
        int t = m + n - 2;
        while (count--) {
            numerator *= (t--);//分子【n+m-2 ~~ n-1 】
                                        //尝试对分子进行约分【使分子尽可能小】
                                        //因为分子的乘法使奇数偶数交替
                                        //所以denominator总有被约完的时候
            while (denominator != 0 && numerator % denominator == 0) {
                numerator /= denominator;//分母【(m-1)!】
                denominator--;
            }
        }
        return numerator;
    }
};
//5.不同路径2【路径中存在障碍】
class Solution {
    public:
        int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
            //                                      【这个数组中，有障碍标记为1】
            int m = obstacleGrid.size();
            int n = obstacleGrid[0].size();
            if(obstacleGrid[0][0] == 1)return 0;
            vector<vector<int>> dp(m,vector<int>(n,1));
//代码随想录里的初始化注意代码里for循环的终止条件，【先全赋值为0】
    //一旦遇到obstacleGrid[i][0] == 1的情况就停止dp[i][0]的赋值1的操作，dp[0][j]同理
            //初始化dp[0][i] = 0 / 1
            /*
            vector<vector<int>> dp(m, vector<int>(n, 0));
            for (int i = 0; i < m && obstacleGrid[i][0] == 0; i++) dp[i][0] = 1;
            for (int j = 0; j < n && obstacleGrid[0][j] == 0; j++) dp[0][j] = 1;
    //这里还是老师写得好
            */ 
            for(int i = 1;i<n;i++){
                if(obstacleGrid[0][i]==1){
                    for(int j = i;j<n;j++){
                        dp[0][j] = 0;
                    }
                    break;
                }
            }
            //初始化 dp[i][0] = 0/1
            for(int i = 1;i<m;i++){
                if(obstacleGrid[i][0]==1){
                    for(int j = i;j<m;++j){
                        dp[j][0] = 0;
                    }
                    break;
                }
            }
            for(int i = 1;i<m;++i){
                for(int j = 1;j<n;j++){
                    if(obstacleGrid[i][j]==1){
                        dp[i][j] = 0;
                    }
                    else{//递推公式
                        dp[i][j] = dp[i-1][j]+dp[i][j-1];
                    }
                }
            }
            return dp[m-1][n-1];
        }
    };
int main(){
    #define MAXNUM 50
    vector<int> dp(MAXNUM,0);
    dp[0] = 1;dp[1] = 1;
    for(int i = 2;i<MAXNUM;i++){
        dp[i] = dp[i-1]+dp[i-2];
    }
    for_each(dp.begin(),dp.end(),[](int num){cout<<num<<endl;});
    std::cout<<"sss"<<std::endl;
    return 0;
}