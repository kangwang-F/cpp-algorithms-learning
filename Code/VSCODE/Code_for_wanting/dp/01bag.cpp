#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false);
    cout.tie(0);cin.tie(0);
    //物品个数，背包容量
    int n,m;
    cin>>n>>m;
    vector<int> weight(n,0);
    vector<int> value(n,0);
    for(int i =0;i<n;i++){
        cin>>weight[i];
    }
    for(int i = 0;i<n;i++){
        cin>>value[i];
    }
        // 含义：对于第i个物品，背包容量为j时最大价值
//     vector<vector<int>> dp(n,vector<int>(m+1,0));
        //初始化 ：对于第0个物品进行初始化
//     for(int i = weight[0];i<=m;i++){
//         dp[0][i] = value[0];
//     }
// //******************************************************************* */
//     //第0个物品已经遍历过了，而且dp[0]不能根据dp[-1]地推
//     for(int i = 1;i<n;i++){//物品
//         for(int j = 1;j<=m;j++){//容量//【这里的for循环不能剪枝 二维的 】
//             if(j>=weight[i]){
//                 dp[i][j] = max(dp[i-1][j],dp[i-1][j-weight[i]]+value[i]);
//             }
//             else{
//                 dp[i][j] = dp[i-1][j];
//             }
//         }
//     }
//     cout<<dp[n-1][m];

    //通过压缩数组【用一维数组和代替二维的】
    //  含义：dp[j],背包容量为j时最大价值【暂时】
    vector<int> dp(m+1,0);
    //初始化
    //对于第0个物品进行初始化
    for(int i = weight[0];i<=m;i++){
        dp[i] = value[0];//能放下第0就保存它的价值 
    }
    for(int i = 1;i<n;++i){//物品
        for(int j = m;j>=weight[i];j--){//容量【倒叙】【一个物品最多使用一次】
            dp[j] = max(dp[j],dp[j-weight[i]]+value[i]);
        }
    }
    cout<<dp[m];
    return 0;
}


//03.分割等和子集
//【nums】是否能找到两个子集sum相等
/*
    回溯的组合总和：时间复杂度：2^n[超时]
*****************************************************
    背包问题，不仅可以求 背包能背的最大价值， 还可以求这个背包是否可以装满
*/
class Solution {
    public:
        bool canPartition(vector<int>& nums) {
            int sum = 0;
            for(int i :nums){
                sum+=i;
            }
            if(sum%2==1){
                return false;
            }
            else{
                //这里就是看最终能不能把dp[target] == target
                int target = sum/2;
                //dp[j]含义：容量为j时最大价值
                vector<int> dp(target+1,0);
                for(int i = nums[1];i<=target;i++){
                    dp[i] = nums[1];
                }
                for(int i = 1;i<nums.size();i++){//物品
                    for(int j = target;j>=nums[i];i--){
                        dp[j] = max(dp[j],dp[j-nums[i]]+nums[i]);
                    }
                }
                if(dp[target]==target){
                    return true;
                }
                return false;
            }
        }
    };
//最后一块石头的重量II
//两个石头可以相撞【得到的石头重量为 大 - 小】
//得到两个 和差 尽可能小的子集
class Solution {
    public:
        int lastStoneWeightII(vector<int>& stones) {
            int sum = 0;
            for(int i:stones){
                sum+=i;
            }
        //dp[sum/2] 看最多能装多少
            vector<int> dp(1501,0);
            int target = sum/2;
            //【】
            for(int i = stones[0];i<=target;i++){
                dp[i] = stones[0];
            }
            for(int i =1 ;i<stones.size();i++){//物品
                for(int j = target;j>=stones[i];j++){//倒叙容量
                    dp[j] = max(dp[j],dp[j-stones[i]]+stones[i]);
                }
            }
            //return abs(sum-dp[target]-dp[target]);
            return (sum-dp[target]-dp[target]);
        }
    };