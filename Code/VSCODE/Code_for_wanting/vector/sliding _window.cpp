#include<bits\stdc++.h>
#include<vector>
using namespace std;
//暴力解法  数组较大时直接内存超限【找一个nums.size*num.size的数组来存储各个符合要求子数组的最小长度】
class Solution {
    public:
        int minSubArrayLen(int target, vector<int>& nums) {
            //vector<vector<int>> arr(nums.size(),vector<int>(nums.size(),nums.size()+1));
            //arr.resize(10000);
            int lenght = INT_MAX;
//直接设置一个length  ,找到符合长度时直接更新长度         
            for(int i = 0;i<nums.size();i++){
                int sum = 0;
                for(int j = i ;j<nums.size();j++){
                    sum+=nums[j];
                    //lenght++;
                    if(sum>=target){
                        //arr[i][j] = lenght;break;
                        lenght = min(lenght,j-i+1);break;
                    }
                }
            }
            return (lenght==INT_MAX?0:lenght);
           // for(vector<vector<int>>::const_iterator it = arr.begin();it<=arr.end();it++){}    
            // auto min_it = std::min_element(arr[0].begin(), arr[0].end());
            // for (size_t i = 1; i < arr.size(); ++i) {
            //     auto current_min_it = std::min_element(arr[i].begin(), arr[i].end());
            //     if (*current_min_it < *min_it) {
            //         min_it = current_min_it;
            //     }
            // }                            
            //min_element(arr.begin(),(*arr.end()).end());
            
            //return ((*min_it == nums.size()+1)?0:(*min_it));
        }
    };
//滑动窗口的方法
//与双指针类似，一个for干两个for的工作
//【总和符合后，start右移
//         否则，end右移【问题就在这里】  】
//  自己写的，问题主要出在：end更新后 length = end - start【end】

class Solution_DW{
    public:
        int minSubArrayLen(int target,vector<int>& nums){
            int start = 0,end = 0;
            int sum =0;int length = INT_MAX;
            for(;end<nums.size();){
                if(sum>=target){
                    length = min(length,end-start+1);
                    sum-=nums[start];
                    start++;                   
                }
                else{
                    sum+=nums[end];
                    end++;
                }
            }
            while (sum >= target) {
                length = std::min(length, end - start);
                sum -= nums[start];
                start++;
            }
            return ((length==INT_MAX)?0:length);
        }
};
class Solution_DW_a{
//卡哥写法【循环内容指的是以end为末尾的子序列；所以每次end是之后才更新的】
    public:
    int minSubArrayLen(int target,vector<int>&nums){
        int lenght = INT_MAX;
        int sum=0;int start = 0;
        for(int end = 0;end<nums.size();end++){
            sum+=nums[end];
            while(sum>=target){
                lenght = min(lenght,end-start+1);
                sum-=nums[start];
                start++;
            }
        }return ((lenght==INT_MAX)?0:lenght);
    }
};
int main(){
    //int target = 4;vector<int> nums = {1,4,4};
    int target = 7;vector<int> nums = {2,3,1,2,4,3};
    //Solution s;
    Solution_DW_a s;
    cout<< s.minSubArrayLen(target,nums);

    return 0;
}