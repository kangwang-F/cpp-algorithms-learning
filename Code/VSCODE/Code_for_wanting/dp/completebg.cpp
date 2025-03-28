#include<bits/stdc++.h>
using namespace std;
/*
    完全背包：物品可以重复取
        一维dp的正序遍历
    【纯完全背包的题目】for物品和for容量 可以颠倒
*/
#define endl "\n"
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    //物品个数 背包容量
    int n=0,v=0;
    cin>>n>>v;
    int temp = n;
    vector<int> weight(n,0);
    vector<int> value(n,0);
    for(int i = 0;i<n;i++){
        cin>>weight[i]>>value[i];
    }
    //以下为一维dp
    // vector<int> dp(v+1,0);
    // //初始化
    
    // for(int i = 0;i<n;i++){
    //     for(int j = weight[i];j<=v;j++){
    //         dp[j] = max(dp[j],dp[j-weight[i]]+value[i]);
    //     }
    // }
    //cout<<dp[v]<<endl;
    vector<vector<int>> dp(n,vector<int>(v+1,0));
    for(int i = weight[0];i<=v;i++){//容量
        //dp[0][i] = value[0] * i/weight[0];
        //统一写法
        dp[0][i] = dp[0][i-weight[0]] + value[0];
    }//初始化 第一行
    for(int i = 1;i<n;i++){     //物品
        for(int j = 1;j<=v;j++){    //容量[正序]
            // //第一行进行初始化
            // if(i==0){dp[0][j] = value[0]*j/weight[0];}
            // else dp[i][j] = max(dp[i-1][j],max(dp[i-1][j-weight[i]]+value[i],dp[i][j-weight[i]]+value[i]));
    //*********************************************** */
            //这里容量<weight[j]也要赋值
            if(j<weight[i])dp[i][j] = dp[i-1][j];
            else {//这里不需要再对do[i-1][j-weight[i]]+value[i]取最大值，上面有用的dp已经保存到dp[i][0~weight[i]-1]
                // dp[i][j] = max(dp[i-1][j],max(dp[i-1][j-weight[i]]+value[i],dp[i][j-weight[i]]+value[i]));
                dp[i][j] = max(dp[i-1][j],dp[i][j-weight[i]]+value[i]);
            }
        }
    }
    cout<<dp[n-1][v]<<endl;
    return 0;
}

//开始做题
//零钱兑换2
/*
    多次选择+组合 问题[1,2] [2,1]X
面向用例编程：
    amount = 4681
    但是coins全是奇数 -> return 0;
vector<long long> 还是溢出
vector<__int128> 还是溢出【编译器不兼容】
用 unsigned long long uint64_t
*/
#define ull unsigned long long
class Solution {
    public:
        int change(int amount, vector<int>& coins) {
            vector<uint64_t> dp(amount+1,0);
            dp[0] = 1;
        //先物品后容量  ->  组合
            for(int i = 0;i<coins.size();i++){//物品
                for(int j = coins[i];j<=amount;j++){//容量
                    dp[j] += dp[j-coins[i]];
                    //防止int越界
                    if(dp[j]>INT_MAX - dp[j-coins[i]]){
                        dp[j] += dp[j-coins[i]];
                    }    
                }
            }
            return dp[amount];
        }
    };
//组合总和4
//返回组合的个数
/*
    【物品的重量和价值一样】dp[i]装满i的方法
所有可能的组合为:( 1，1，1，1)( 1,1，2)( 1，2，1)( 1，3)(2，1，1)(2，2)( 3，1)
请注意，顺序不同的序列被视作不同的组合。
*/
class Solution {
    public:
        int combinationSum4(vector<int>& nums, int target) {
            vector<int> dp(target+1,0);
            dp[0] = 1;
            for(int i = 1;i<=target;i++){//背包【正序】
                for(int j = 0;j<nums.size();j++){//物品
                    if(i>=nums[j]){
                        if(dp[i]<INT_MAX-dp[i-nums[j]])
                            dp[i] += dp[i-nums[j]];    
                    }
                    
                }    
            }
            return dp[target];
        }
    };
//爬楼梯【进阶】
/*
1. 内存布局与数据未被覆盖
数组在内存中是连续存储的，arr[-1] 实际上访问的是数组起始地址之前的内存位置。
如果该位置恰好有其他已分配且有数据的内存，
并且该内存的数据对程序后续执行没有造成严重影响，那么程序可能不会立即崩溃报错。
*/
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
//一共n阶，一次最多爬m
    int n=0,m=0;
    cin>>n>>m;
    vector<int> dp(n+1,0);
    dp[0] = 1;
    for(int i = 1;i<=n;i++){//背包
        for(int j = 1;j<=m;j++){//一次爬1 ~ m
            //这里一定在容量够的时候进行运算
            if(i>=j)
                dp[i] += dp[i-j]; 
        }    
    }
    cout<<dp[n];
    return 0;
}

//零钱兑换
//计算并返回可以凑成总金额所需的 最少的硬币个数 。
//如果没有任何一种硬币组合能组成总金额，返回 -1
class Solution {
    public:
        #define MAXAMOUNT 10001
        //amount 最多为 10000 【所以用的硬币最多为10001】
        int coinChange(vector<int>& coins, int amount) {
        //dp[j]：凑足总额为j所需钱币的最少个数为dp[j]
            vector<int> dp(amount+1,MAXAMOUNT);
            //初始化
            dp[0] = 0;//组成0 需要0个钞票
            for(int i = 0;i<coins.size();i++){//物品
                    //你先得能放下coins[i]
                for(int j = coins[i];j<=amount;j++){//容量【正序】
                // 1 2 5    11 
                    dp[j] = min(dp[j],dp[j-coins[i]]+1);
                }
            }
            return dp[amount]==MAXAMOUNT ? -1 : dp[amount];
        }
    };
//完全平方数
/*
    对于一个数n：把他拆成完全平方数的和，用的最少的个数
*/
class Solution {
    public:
        int numSquares(int n) {
            int index = sqrt(n);
            vector<int> nums(index+1,0);
            for(int i = 1;i<=index;i++){
                nums[i] = i*i;
            }      
            vector<int> dp(n+1,1000);
            dp[0] = 0;
            for(int i = 1;i<=index;i++){//物品【第一个物品】
                for(int j = nums[i];j<=n;j++){//容量【正序】
                    dp[j] = min(dp[j],dp[j-nums[i]]+1);
                }
            }
            return dp[n];
        }
    };
//解法二：不需要index
class Solution {
    public:
        int numSquares(int n) {
            vector<int> dp(n + 1, INT_MAX);
            dp[0] = 0;
                //从1开始枚举，直到 i^2 > n
            for (int i = 1; i * i <= n; i++) { // 遍历物品
                for (int j = i * i; j <= n; j++) { // 遍历背包
                    dp[j] = min(dp[j - i * i] + 1, dp[j]);
                }
            }
            return dp[n];
        }
    };
//单词分割
/*
    s是否可以由wordDict里的元素组成
            [Dict为物品，能否填满dp[s.size()]]
        dp[i] 字符串长度为 i 是否可以由元素组成
    dp[i] = dp[i-j] && Dict.find(s[j~i]);
【完全背包】
*/
class Solution {
    public:
        bool wordBreak(string s, vector<string>& wordDict) {
            // unordered
            set<string> s_s(wordDict.begin(),wordDict.end());
            vector<bool> dp(s.size()+1,false);
            dp[0] = true;
            //要求顺序【先背包 后物品】
            for(int i = 1;i<=s.size();i++){//背包
                for(int j = 0;j<i;j++){    //物品[j~i子串]
                    // string word = s.substr(j, i - j); //substr(起始位置，截取的个数)
                    // dp[i] = (dp[j] && (s_s.find(s.substr(j,i-j))!=s_s.end()));
            //上面那种写发，dp[i] 即使在某个字串处被赋值为true
                    //之后会被后面的字串返回值覆盖
                    if(dp[j] && (s_s.find(s.substr(j,i-j))!=s_s.end())){
                        dp[i] = true;
                        break;
                    }
                }
            }
            return dp[s.size()];
        }
    };