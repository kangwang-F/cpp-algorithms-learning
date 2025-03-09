#include<bits/stdc++.h>
using namespace std;

//5.  ******小白噩梦**********两数之和【实质：看看是否遍历过target-nums[i],并且记忆对应元素的下标】
//暴力
class Solution_double_for{
    public:
        vector<int> twoSum(vector<int>& nums,int target){
            for(int i =0;i<nums.size();i++){
                for(int j = i + 1;j<nums.size();j++){
                    if(nums[i]+nums[j]==target){
                        return {i,j};
                    }
                }
            }return {};
        }
};
class Solution_map {
    public:
        vector<int> twoSum(vector<int>& nums, int target) {
            multimap<int,int> hash_table;
            vector<int> res;
            for(int i =0;i<nums.size();i++){
                hash_table.insert(make_pair(nums[i],i));
            }
            for(int i =0;i<nums.size();i++){
                multimap<int,int>::iterator it = hash_table.find(target-nums[i]);
                if(it!=hash_table.end()&&it->second!=i){
                    res.push_back(i);res.push_back(it->second);break;
                }
            }return res;
        }
};
//1.用unordered_map<>   首先要存下数字(key) 和 其对应的下标(value)      
//2.因为key不需要有序；；；；；；这种情况下最好用unordered_map<>    查询_增删效率都最高
class Solution_best{
    public:
        vector<int> twoSum(vector<int>& nums,int target){
            unordered_map<int,int> mp;
            int sz = nums.size();
            for(int i=0;i<sz;i++){
                unordered_map<int,int>::iterator it = mp.find(target-nums[i]);
                if(it!=mp.end()){
                    return{i,it->second};
                }
                mp[nums[i]] = i;
            }return{};
        }
};
//6.进阶四数之和  我逐渐写的：最后结果是 mp1[]*mp2[]  【由于我的两个mp，所以时间会多一些】
//  carl写的一个mp，然后哈希搜索，count++； 141ms->116ms    的运行时间的下降
class Solution_me {
    public:
    int twoSum(vector<int>& nums1,vector<int>& nums2,int target){int count = 0;
        unordered_map<int,int> mp;
        for(auto i:nums2){
            mp[i]++;
        }
        int sz = nums1.size();
        for(int i=0;i<sz;i++){
            int sub = target-nums1[i];
            if(mp.find(sub)!=mp.end())count+=mp[sub];        //这里出现了问题，只能返回一个迭代器，不能返回nums2中符合要求的个数
        }return count;
    }
        int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
            int count = 0;
            // for(int i =0;i<nums1.size();i++){            //四层循环，超时了
            //     for(int j=0;j<nums2.size();j++){
            //         for(int k = 0;k<nums3.size();k++){
            //             for(int q = 0;q<nums4.size();q++){
            //                 if(nums1[i]+nums2[j]+nums3[k]+nums4[q]==0){
            //                     count++;
            //                 }
            //             }
            //         }
            //     }
            // }
            unordered_map<int,int> mp1;
            for(int i =0;i<nums1.size();i++){            //两层循环 + 一个哈希map仍然超时
                for(int j=0;j<nums2.size();j++){
                    mp1[nums1[i]+nums2[j]]+=1;
                    // int a = twoSum(nums3,nums4,0-nums1[i]-nums2[j]);
                    // if(a)count+=a;
                }
            }
            unordered_map<int,int> mp2;

            for(int i=0;i<nums3.size();i++){
                for(int j = 0;j<nums4.size();j++){
                    mp2[nums3[i]+nums4[j]]+=1;
                }
            }
            for(auto i: mp1){
                if(mp2.find(i.first)!=mp2.end())count+=(i.second*mp2[i.first]);
            }
            return count;
        }    
};
class Solution {
    public:
        int fourSumCount(std::vector<int>& nums1, std::vector<int>& nums2, std::vector<int>& nums3, std::vector<int>& nums4) {
            std::unordered_map<int, int> umap; // key: nums1[i] + nums2[j] 的数值，value: nums1[i] + nums2[j] 数值出现的次数
            // 遍历 nums1 和 nums2 数组，统计两个数组元素之和，和出现的次数，放到 map 中
            for (int a : nums1) {
                for (int b : nums2) {
                    umap[a + b]++;
                }
            }
            int count = 0; // 统计 nums1[i] + nums2[j] + nums3[k] + nums4[l] = 0 出现的次数
            // 再遍历 nums3 和 nums4 数组，找到如果 0 - (nums3[k] + nums4[l]) 在 map 中出现过的话，就把 map 中 key 对应的 value 也就是出现次数统计出来。
            for (int c : nums3) {
                for (int d : nums4) {
                    if (umap.find(0 - (c + d)) != umap.end()) {
                        count += umap[0 - (c + d)];
                    }
                }
            }
            return count;
        }
};

//7.赎金信
// 暴力---值得注意的是：他用到的s.length();然后删掉ransom中与magazine[i]相等的第一个字符；最后判断ransom是否为空
class Solution_baoli {
    public:
        bool canConstruct(string ransomNote, string magazine) {
        //add
            if (ransomNote.size() > magazine.size()) {
                return false;
            }
            for (int i = 0; i < magazine.length(); i++) {
                for (int j = 0; j < ransomNote.length(); j++) {
                    // 在ransomNote中找到和magazine相同的字符
                    if (magazine[i] == ransomNote[j]) {
                        ransomNote.erase(ransomNote.begin() + j); // ransomNote删除这个字符
                        break;
                    }
                }
            }
            // 如果ransomNote为空，则说明magazine的字符可以组成ransomNote
            if (ransomNote.length() == 0) {
                return true;
            }
            return false;
        }
    };
class Solution_hash {
    public:
        bool canConstruct(string ransomNote, string magazine) {
        //add
            if (ransomNote.size() > magazine.size()) {
                return false;
            }
            int hash_table1[26];
            for(int i=0;i<magazine.size();i++){
                hash_table1[magazine[i]-'a']+=1;
            }
            int hash_table2[26];
            for(int i=0;i<ransomNote.size();i++){
                hash_table2[ransomNote[i]-'a']+=1;
            }
            for(int i=0;i<26;i++){
                if(hash_table2[i]>hash_table1[i])return false;
            }return true;
        }
};
//8.三数之和        
//  暴力：数据量特别大
class Solution_baoli {
    public:
        vector<vector<int>> threeSum(vector<int>& nums) {
            vector<vector<int>> res;
            for(int i=0;i<nums.size();i++){
                for(int j=i+1;j<nums.size();j++){
                    for(int k=j+1;k<nums.size();k++){
                        if(nums[i]+nums[j]+nums[k]==0)res.push_back({nums[i],nums[j],nums[k]});
                    }
                }
            }
            for(int i =0;i<res.size();i++){
                sort(res[i].begin(),res[i].end());
            }
            set<vector<int>> res_s(res.begin(),res.end());
            return vector<vector<int>>(res_s.begin(),res_s.end());
        }
};
//  哈希法因为要去重复：失败了
class Solution_error {
    public:
        vector<vector<int>> threeSum(vector<int>& nums) {
            vector<vector<int>> res;
            set<int> s(nums.begin(),nums.end());
            s.erase(nums[0]);
            s.erase(nums[1]);
            for(int i=0;i<nums.size();i++){
                for(int j=i+1;j<nums.size();j++){                    
                    if(s.find(-nums[i]-nums[j])!=s.end())res.push_back({nums[i],nums[j],-nums[i]-nums[j]});
                    
                }s.erase(nums[i+2]);
            }
            return res;
            // for(int i =0;i<res.size();i++){
            //     sort(res[i].begin(),res[i].end());
            // }
            // set<vector<int>> res_s(res.begin(),res.end());
            // return vector<vector<int>>(res_s.begin(),res_s.end());
        }
};
//  哈希正确写法    【要做排序】
class Solution {
    public:
        vector<vector<int>> threeSum(vector<int>& nums) {
            vector<vector<int>> result;
            sort(nums.begin(), nums.end());
            // 找出a + b + c = 0
            // a = nums[i], b = nums[left], c = nums[right]
            for (int i = 0; i < nums.size(); i++) {
                // 排序之后如果第一个元素已经大于零，那么无论如何组合都不可能凑成三元组，直接返回结果就可以了
                if (nums[i] > 0) {
                    return result;
                }
                // 错误去重a方法，将会漏掉-1,-1,2 这种情况
                /*
                if (nums[i] == nums[i + 1]) {
                    continue;
                }
                */
                // 正确去重a方法
                if (i > 0 && nums[i] == nums[i - 1]) {
                    continue;
                }
                int left = i + 1;
                int right = nums.size() - 1;
                while (right > left) {
                    // 去重复逻辑如果放在这里，0，0，0 的情况，可能直接导致 right<=left 了，从而漏掉了 0,0,0 这种三元组
                    /*
                    while (right > left && nums[right] == nums[right - 1]) right--;
                    while (right > left && nums[left] == nums[left + 1]) left++;
                    */
                    if (nums[i] + nums[left] + nums[right] > 0) right--;
                    else if (nums[i] + nums[left] + nums[right] < 0) left++;
                    else {
                        result.push_back(vector<int>{nums[i], nums[left], nums[right]});
                        // 去重逻辑应该放在找到一个三元组之后，对b 和 c去重
                        while (right > left && nums[right] == nums[right - 1]) right--;
                        while (right > left && nums[left] == nums[left + 1]) left++;
    
                        // 找到答案时，双指针同时收缩
                        right--;
                        left++;
                    }
                }
            }
            return result;
        }
};
//  【一定要排序】双指针+去重
class Solution {
    public:
        vector<vector<int>> threeSum(vector<int>& nums) {
            vector<vector<int>> res;
            sort(nums.begin(),nums.end());
            for(int i =0;i<nums.size();i++){
                if (nums[i] > 0) {
                    return res;
                }
                int left = i+1;
                int right = nums.size()-1;
                while(left<right){
                    int sum = nums[i]+nums[left]+nums[right];
                    if(sum>0)right--;
                    else if(sum<0)left++;
                    else{
                        res.push_back({nums[i],nums[left],nums[right]});
                        while(left<right&&nums[left]==nums[left+1])left++;
                        while(left<right&&nums[right]==nums[right-1])right--;
                        left++;right--;
                    }
                }
            }return res;
        }
};
//最快的版本 【先更新值，再进行去重】
class Solution_best {
    public:
        vector<vector<int>> threeSum(vector<int>& nums) {
            vector<vector<int>> vv;
            sort(nums.begin(), nums.end());
            for (int i = 0;i < nums.size() - 2&&nums[i]<=0;)
            {
                int left = i + 1, right = nums.size() - 1;
                int target = -nums[i];
                while (left < right)
                {
                    if (nums[left] + nums[right] > target) right--;
                    else if (nums[left] + nums[right] < target)left++;
                    else
                    {
                        vv.push_back({ nums[i],nums[left],nums[right] });
                        right--;
                        left++;
                        //去重实在符合条件的情况下去重的
                        while (left < right && nums[left] == nums[left - 1]) left++;
                        while (left < right && nums[right] == nums[right + 1]) right--;
                    }
                   
                }
                i++;
                while (i<nums.size()&&nums[i] == nums[i - 1]) i++;
            }
            return vv;
        }
    };
//四数之和【对于mid控制起来比较复杂】【其实只用再来一个for循环】
//【注意减枝和去重】
class Solution_error {
    public:
        vector<vector<int>> fourSum(vector<int>& nums, int target) {
            sort(nums.begin(),nums.end());
            vector<vector<int>> res;
            for(int i=0;i<nums.size();i++){
                int left = i+1;
                int right = nums.size()-1;
                int mid = (left+right)/2;
                while(left<mid&&right>mid){
                    int sum = nums[i]+nums[left]+nums[right]+nums[mid]-target;
                    if(sum>0){right--;mid--;
                            while(mid>left&&nums[mid]==nums[mid+1])mid--;
                        }
                    else if(sum<0){left++;mid++;
                            while(mid<right&&nums[mid]==nums[mid-1])mid++;
                        }
                    else{
                        res.push_back({nums[i],nums[left],nums[mid],nums[right]});
                        left++;
                        right--;
                        while(left<mid&&nums[left]==nums[left-1])left++;
                        while(right>mid&&nums[right]==nums[right+1])right--;
                    }
                    i++;
                    while(i<nums.size()&&nums[i]==nums[i-1])i++;
                }
            }return res;
        }
};
class Solution{
    public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        sort(nums.begin(),nums.end());
        for(int k=0;k<nums.size();k++){
            //第一次减枝[这里的减枝]
    //很关键，有一组测试数据：10 000 0000, 10 000 0000, 10 000 0000. 10 000 0000. target =0
                //如果加到一起，int越界【这里并不是减枝条件没写好，就是会溢出，得用long】
        // nums[k]>target   &&  target>=0
            if(nums[k]>target&&target>=0)continue;
            //第一次去重
            if(k>0&&nums[k]==nums[k-1])continue;
            for(int i=k+1;i<nums.size();i++){
                //第二次减枝
                if(nums[k]+nums[i]>target&&target>0)continue;
                //第二次去重
                if(i>k+1&&nums[i]==nums[i-1])continue;
                //开始配对+第三四次去重
                int left = i+1;int right = nums.size()-1;
                while(left<right){
                //会溢出
                    //int sum = nums[i]+nums[k]+nums[left]+nums[right]-target;
                    if((long) nums[k] + nums[i] + nums[left] + nums[right]  > target)right--;
                    else if((long) nums[k] + nums[i] + nums[left] + nums[right]  < target)left++;
                    else{
                        res.push_back({nums[i],nums[k],nums[left],nums[right]});
                        //第三次去重
                        left++;right--;
                        while(left<right&&nums[left]==nums[left-1])left++;
                        while(left<right&&nums[right]==nums[right+1])right--;
                    }
                }
            }
        }return res;
    }
};