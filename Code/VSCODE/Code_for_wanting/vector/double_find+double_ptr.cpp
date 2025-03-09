// #include<bits/c++.h>
#include<bits/stdc++.h>
using namespace std;
class Solution {
    public:
        int search(vector<int>& nums, int target) {
            int left = 0;int right = nums.size()-1;
            while(left<=right){
                int mid = (left+right)/2;
                if(nums[mid]>target){
                    left = mid+1;
                }
                else if(nums[mid]==target){
                    right = mid-1;
                }
                else{
                    return mid;
                }

            }return -1;
        }
    };

//暴力算法【移除元素】
class Solution_2 {
    public:
        int removeElement(vector<int>& nums, int val) {
            int k = nums.size();int n = 0;
            for(int i = 0;i<k-n;i++){
                if(val==nums[i]){
                //if(val==nums[i]){
                    for(int j =i;j<k-1;j++){
                        nums[j] = nums[j+1];
                    }  
                    if(i!=k-1-n){
                        i--;
                    }                                     
                    n++;             
                }
            }return k-n;     
        }
};
//双指针算法
//  利用一个for循环做两个for循环的工作
class Solution_3 {
    public:
        int removeElement(vector<int>& nums, int val) {
            int slow = 0;int k = nums.size();
            for(int fast = 0;fast<k;fast++){
                if(nums[fast]!=val){
                    nums[slow++] = nums[fast];
                }  
            }return slow;

        }
};
//有序数组的平方
class Solution_sqr {
    public:
        vector<int> sortedSquares(vector<int>& nums) {
            int k = nums.size();
            int arr[1000] = {0};int index = 0;
            vector<int> res;
            res.resize(k);
            int j = 0;
            for(int i =0;(j<k&&i<k);i++){
                int sqr = (nums[i]*nums[i]);
                if(nums[i]<0){
                    arr[index++] = sqr;
                }
                else{
                    if(index>0){
                        if(arr[index-1]>=sqr){
                        res[j++] = sqr;
                        }
                        else{
                            res[j++] = arr[--index];i--;continue;
                        }
                    }else{
                        res[j++]=sqr;

                    }
                }
            }
            if(index>0){
                for(;index>0;){
                    res[j++] = arr[--index];
                }
            }
            return res;
        }
};
int compare(const void* a,const void* b){
    return (*(int*)a - *(int*)b);
}
//卡bug一样用快排也同样解决了本体的所有样例
class Solution_sqr_quick_sort {
    public:
        vector<int> sortedSquares(vector<int>& nums) {
            int index = 0;
            for(auto i : nums){
                nums[index++] = i*i;
            }
            int k = index;
            //sort(nums.begin(),nums.end());
            qsort(nums.data(),nums.size(),sizeof(int),compare);
            return nums;
        }
};
//双指针解法：首先不能固化思维，认为res数组只从0开始从小到大来填写，也可以从末尾从大到小来更新
// 由于给出的数组是有序的，那么从两边向中间平方值是在逐渐变大的
//由此想到了双指针解法
class Solution_sqr_double_ptr{
    public:
    vector<int> sortedSquares(vector<int>& nums){
        int k = nums.size();
        int index = k-1;
        vector<int> res(nums.size(),0);
        for(int i=0,j=k-1;i<=j;){
            if(pow(nums[i],2)>pow(nums[j],2)){
                res[index--] = pow(nums[i++],2);
            }
            else{
                res[index--] = pow(nums[j--],2);

            }
        }return res;
    }
};
int main(){
    //vector<int> nums= {3,2,2,3};
    vector<int> nums= {0,1,2,2,3,0,4,2};
    Solution_3 s2;
    cout<<s2.removeElement(nums,2)<<endl;
    for(auto i :nums){
        cout<<i<<" "<<endl;
    }
    cout<<endl;
//平方数组
    vector<int> nums_ = {-4,-1,0,3,10};
    // Solution_sqr s_s;
    // vector<int> res = s_s.sortedSquares(nums_);

    // Solution_sqr_quick_sort s_s_qs;
    // vector<int> res = s_s_qs.sortedSquares(nums_);

    Solution_sqr_double_ptr s_s_dp;
    vector<int> res = s_s_dp.sortedSquares(nums_);
    for(auto i :res){
        cout<<i<<" "<<endl;
    }
    return 0;
}