#include<bits\stdc++.h>
using namespace std;
//Greedy Algorithm 【贪心算法】
/*
    贪心算法：通过寻找局部最优解 => 全局最优解
*/
//1.分发饼干
//想清楚局部最优，想清楚全局最优，感觉局部最优是可以推出全局最优，并想不出反例，那么就试一试贪心。
class Solution {
    public:
        int findContentChildren(vector<int>& g, vector<int>& s) {
            sort(g.begin(),g.end());
            sort(s.begin(),s.end());
            int count =0;
            for(int i = s.size() - 1,j = g.size();(i>=0)&&(j>=0);){
                //每一步：先把最大的饼干给胃口最大的人吃
                if(s[i]>=g[j]){
                    count++;
                    i--;j--;
                }
                else{
                    j--;
                }
            }     
            return count;
        }
    };
//2.摆动序列【差值在正负波动】
class Solution {
    public:
        int wiggleMaxLength(vector<int>& nums) {
            //第一个元素一定放在序列里
            int count = 1;
            //少于等于一个元素直接返回
            if(nums.size()<=1)return count;
            //这个初始化，指的是在数组[0]前面放置一个等值的[-1]元素，即第二个元素的pre差值为0
            int prediff = 0;
            int curdiff = 0;
            //从第二个元素开始，一直到最后一个
            for(int i = 1;i<nums.size();i++){
                //看 本 元素 是否符合要求
                curdiff = nums[i] - nums[i-1];
                //这里去等，是为了排除有平坡的情况
                if((prediff>=0&&curdiff<0)||(prediff<=0&&curdiff>0)){
                    count++;
                    //放进里面：是为了防止单调有平坡
                    prediff = curdiff;
                }
            }
            return count;
        }
    };
//3.最大子数组和
class Solution {
    public:
        //贪心
        //局部最优：如果目前的sum<0则归零,继续往后加
        int maxSubArray(vector<int>& nums) {
            int sum = 0;
            //result来记录当前找到的最大和
            int result = INT_MIN;
            for(int i =0;i<nums.size();i++){
                if(sum<0)sum=0;
                sum += nums[i];
            //局部最优->全局最优
                result = max(sum,result);
            }
            return result;
        }
    };
//4.买入股票的最佳时机2
class Solution {
    public:
    //局部最优：找到买入的时间 -> 找到股票的峰值卖出
    //
        int maxProfit(vector<int>& prices) {
            int startindex = 0;
            int result = 0;
            int sum = 0;
            for(int i = 1;i<prices.size();i++){
                //股票上涨
                if(prices[i]>prices[i-1]){
                    //更新sum，但是并不急得往result里加
                    sum = prices[i] - prices[startindex];
                //防止到最后任然在增但是没有加入到总和中
                    if(i==prices.size()-1){
                        result+=sum;
                    }
                }
            //股票下跌就加上sum，重置sum，重置startindex
                else{
                    result += sum;
                    sum = 0;
                    startindex = i;
                }
            }
            return result;
        }
    };
//解法二：不需要看区间
//只需要，把股票上升的日子的利润加上，下降的不管
/*
此时就是把利润分解为每天为单位的维度，而不是从 0 天到第 3 天整体去考虑！
收集正利润的区间，就是股票买卖的区间，而我们只需要关注最终利润，不需要记录区间。
*/
//时间复杂度均为O(n)

class Solution{
//局部最优：收集每天的正利润，全局最优：求得最大利润。
    public: 
    int maxProfit(vector<int>& prices) {
        int result = 0;
        for(int i = 1;i<prices.size();i++){
            //收集每天的正利润
            result += max(0,prices[i]-prices[i-1]);
        }
        return result;
    }
};
//5.跳跃游戏
class Solution {
    public:
        bool canJump(vector<int>& nums) {
            int cover = 0;
            for(int i = 0;i<nums.size();i++){
                if(i>cover)return false;
            //局部最优：在当前cover中找到跨度最大下一个cover
            //全局最优：最大的cover是否到nums.zie()-1
                cover = max(cover,nums[i]+i);
                if(cover>=nums.size()-1)return true;
            }
        //这个语句应对：【0】，显然能覆盖到结尾
            return true;
        }
    };
class Solution {
    public:
        bool canJump(vector<int>& nums) {
            int cover = 0;
            if (nums.size() == 1) return true; // 只有一个元素，就是能达到
//这个循环条件很好   // 注意这里是小于等于cover
            for (int i = 0; i <= cover; i++) { 
                cover = max(i + nums[i], cover);
                if (cover >= nums.size() - 1) return true; // 说明可以覆盖到终点了
            }
            return false;
        }
    };
//6.跳跃问题2【以最小的步数增加最大的覆盖范围，直到覆盖范围覆盖了终点】
class Solution {
//局部最优：当前可移动距离尽可能多走，如果还没到终点，步数再加一。
//整体最优：一步尽可能多走，从而达到最少步数。
    public:
        int jump(vector<int>& nums) {
            //如果只有一个元素，需要移动 0 次
            if(nums.size()==1)return 0;
            int result = 0;
            int curcover = 0;
            int nextcover = 0;
            for(int i = 0;i<nums.size();i++){
                nextcover = max(nextcover,nums[i]+i);
                if(i==curcover){
                    curcover = nextcover;
                //范围更新，表示往前走了一次
                    result++;
                    if(curcover >= nums.size()-1){//如果到达位置
                        break;
                    }
                }
            }
            return result;
        }
    };
//解法二：比较烧脑
/*  【only走到nums.size()-2】
    1.如果移动下标等于当前覆盖最大距离下标， 需要再走一步（即 ans++），
        因为最后一步一定是可以到的终点。（题目假设总是可以到达数
    2.如果移动下标不等于当前覆盖最大距离下标，
        说明当前覆盖最远距离就可以直接达到终点了，不需要再走一步。
*/
class Solution{
    public:
    int jump(vector<int>&nums){
        int result = 0;
        int curcover = 0;
        int nextcover = 0;
        for(int i = 0;i<nums.size()-1;i++){
            nextcover = max(nextcover,i+nums[i]);
            if(i==curcover){
                curcover = nextcover;
                result++;
            }
        }return result;
    }
};
//K次取反后求最大和
/*
    贪心的思路，局部最优：让绝对值大的负数变为正数，当前数值达到最大，整体最优：整个数组和达到最大。
    局部最优可以推出全局最优。
    那么如果将负数都转变为正数了，K依然大于0，此时的问题是一个有序正整数序列，
    如何转变K次正负，让 数组和 达到最大。
    那么又是一个贪心：局部最优：只找数值最小的正整数进行反转，
    当前数值和可以达到最大（例如正整数数组{5, 3, 1}，
    反转1 得到-1 比 反转5得到的-5 大多了），全局最优：整个 数组和 达到最大。
    */
//没有处理，数组已经遍历完了，但是k仍不为0【k>nums.size()】
//而且频繁更新result，是的代码变得冗余
//【我最初的想法是，一遍过，不需要再一次循环累加nums，显然失败】
class Solution_error {
    public:
        int largestSumAfterKNegations(vector<int>& nums, int k) {
            // sort(nums.begin(),nums.end(),[](int a,int b){return a<b;});
            sort(nums.begin(),nums.end());
            int result = 0;
            for(int i = 0;i<nums.size();i++){
                if(k==0){
                    result+=nums[i];
                    continue;
                }
            //第一次贪心：遇到负数，要变正
                if(nums[i]<0){
                    nums[i]*=-1;
                    k--;
                    result+=nums[i];
                }
                else{
            //第二次贪心：遇到正的要可着绝对值小的变【k为奇数】
                    if(i==0){
                        if(k%2!=0){nums[i]*=(-1);k=0;}
                        result+=nums[i];
                    }
                    else{
                        if(k%2==0){
                            k=0;
                            result+=nums[i];
                        }
                        else{
                            if(abs(nums[i])>abs(nums[i-1])){
                                result -= (nums[i-1]*2);
                                result+= nums[i];
                            }
                            else{
                                result-=nums[i];
                            }
                            k=0;
                        }
                        
                    }
                    // if(k%2==0){
                    //     k=0;result+=nums[i];
                    // }
                    // else{
                    //     if(i==0){k=0;result-=nums[i];}
                    //     else{
                    //         if(abs(nums[i])<abs(nums[i-1])){
                    //             result-=nums[i];k=0;
                    //         }
                    //         else{
                    //             result-=nums[i-1];result-=nums[i-1];result+=nums[i];
                    //             k=0;
                    //         }
                    //     }
                    // }
                }
            }return result;
        }
    };
//正确解法【sort为绝对值排序】
class Solution {
    public:
        int largestSumAfterKNegations(vector<int>& nums, int k) {
            auto cmp = [](int a,int b){return abs(a)>abs(b);};
            sort(nums.begin(),nums.end(),cmp);//1
            for(int i = 0;i<nums.size();i++){
                if(nums[i]<0&&k>0){//第一次贪心
                    k--;
                    nums[i]*=(-1);
                }
            }
            if(k%2==0){}
            else{//第二次贪心
                nums[nums.size()-1]*=(-1);
            }
            int result = 0;
            for_each(nums.begin(),nums.end(),[&](int num){result+=num;});//4
            return result;
        }
    };
int main(){
    return 0;
}