/*哈希表常用的数据结构
    数组：范围可控，
        不适合数组：数据量大，数据比较分布：1，2，100000000
    set
    map
*/
#include<bits/stdc++.h>

using namespace std;
//1.异位字符串    s -> t  【t这个单词是由s字母排列组合得到的】
class Solution {
    public:
        bool isAnagram(string s, string t) {
            //两个哈希表    一个哈希表亦可
            vector<int> hash_table(26,0);
            vector<int> hash_tableA(26,0);
            vector<int> hash_tableB(26,0);
            // if(s.size()>t.size()){
            //     swap(s,t);
            // }
            for(int i = 0;i<s.size();i++){
                hash_tableA[s[i]-'a'] += 1;
                hash_table[s[i]-'a'] ++;

            }
            for(int j =0;j<t.size();j++){
                // if(hash_table[t[j]-97]!=1){
                //     return false;
                // }
                hash_tableB[t[j]-'a'] += 1;
                hash_table[t[j]-'a'] --;

            }
            for(int i =0;i<26;i++){
                if(hash_tableA[i]!=hash_tableB[i]){
                    return false;
                }

                if(hash_table[i]!=0)return false;
            }
            return true;
        }
    };
//2.查找公用的字符    【不仅返回公用的，而且是包括重复的，eg：boll,coll,eoll  返回 o l l】
class Solution_error {
    public:
        vector<string> commonChars(vector<string>& words) {
            vector<vector<int>> hash_table(words.size(),vector<int>(26,0));
            for(int i = 0;i<words.size();i++){
                for(int j = 0;j<words[i].size();j++){
                    hash_table[i][words[i][j]-'a']++;
                }
            }
            vector<int> arr;
            for(int i = 0;i<26;i++){
                bool temp = 1;
                for(int j=0;j<words.size();j++){
                    if(hash_table[j][i]==0){
                        temp = 0;break;
                    }
                }
                if(temp==1){
                    arr.push_back(i);
                }
            }vector<string> res;
            for(int i=0;i<arr.size();i++){
                //char c = new char(arr[i]+'a');
                // char* pc = (char*)new char(arr[i]+'a');  //这里，new char（）是指分配多大的空间，而不是赋值
                // string s = pc;
                string s(1,arr[i]+'a');
                //string s1((char)(arr[i]+'a'))
                res.push_back(s);
            }return res;
        }
};
//修正：hash[i] = min(hash[i],hashotherarr[i])
class Solution_h {
    public:
        vector<string> commonChars(vector<string>& words) {
            vector<vector<int>> hash_table(words.size(),vector<int>(26,0));
            for(int i = 0;i<words.size();i++){
                for(int j = 0;j<words[i].size();j++){
                    hash_table[i][words[i][j]-'a']++;
                }
            }
            int arr[26];
            memset(arr,0,26*sizeof(int));
            for(int i = 0;i<26;i++){
                arr[i] = hash_table[0][i];  //赋初值
                for(int j = 0;j<words.size();j++){
                    arr[i] = min(arr[i],hash_table[j][i]);
                    if(arr[i]==0){
                        break;
                    }
                }
            }
            vector<string> res;
            for(int i=0;i<26;i++){
                for(int i =0;i<arr[i];i++){
                    string s(1,i+'a');
                    res.push_back(s);
                }
            }return res;
        }
    };
//标准
    class Solution_std {
        public:
            vector<string> commonChars(vector<string>& A) {
                vector<string> result;
                if (A.size() == 0) return result;
                int hash[26] = {0}; // 用来统计所有字符串里字符出现的最小频率
                for (int i = 0; i < A[0].size(); i++) { // 用第一个字符串给hash初始化
                    hash[A[0][i] - 'a']++;
                }
        
                int hashOtherStr[26] = {0}; // 统计除第一个字符串外字符的出现频率
                for (int i = 1; i < A.size(); i++) {
                    memset(hashOtherStr, 0, 26 * sizeof(int));
                    for (int j = 0; j < A[i].size(); j++) {
                        hashOtherStr[A[i][j] - 'a']++;
                    }
                    // 更新hash，保证hash里统计26个字符在所有字符串里出现的最小次数
                    for (int k = 0; k < 26; k++) {
                        hash[k] = min(hash[k], hashOtherStr[k]);
                    }
                }
                // 将hash统计的字符次数，转成输出形式
                for (int i = 0; i < 26; i++) {
                    while (hash[i] != 0) { // 注意这里是while，多个重复的字符
                        string s(1, i + 'a'); // char -> string
                        result.push_back(s);
                        hash[i]--;
                    }
                }
        
                return result;
            }
        };
//3.求交集——我用hashtable(数组)   由于本题：数据范围从1亿改到1000，所以之前用set较合适，现在用数组也可以
class Solution_me {
    public:
        vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
            // vector<vector<int>> hash_table(2,vector<int>(10001,0));
            // for(int i=0;i<nums1.size();i++){
            //     hash_table[0][nums1[i]]++;
            // }
            // for(int i=0;i<nums2.size();i++){
            //     hash_table[1][nums2[i]]++;
            // }
            // vector<int> res;
            // for(int i=0;i<=1000;i++){
            //     if(hash_table[0][i]>0&&hash_table[1][i]>0)res.push_back(i);
            // }return res;
//代码随想录
            unordered_set<int> result_set; // 存放结果，之所以用set是为了给结果集去重
            int hash[1005] = {0}; // 默认数值为0
            for (int num : nums1) { // nums1中出现的字母在hash数组中做记录
                hash[num] = 1;
            }
            for (int num : nums2) { // nums2中出现话，result记录
                if (hash[num] == 1) {
                    result_set.insert(num);
                }
            }
            return vector<int>(result_set.begin(), result_set.end());
        }
    };
    
//最快——用set（因为结果不允许重复）
class Solution_s {
    public:
        vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
            unordered_set<int> set(nums1.begin(),nums1.end());//把nums1的数据存入
            unordered_set<int> result;
            for(int b:nums2)//枚举nums2的数据，观察是否在nums1中
            {
                if(set.find(b)!=set.end())
                    result.insert(b);
            }
            return vector<int> (result.begin(),result.end()); 
        }
};
//4.   【【【【【【【【【【【【【【【【【【【【【【【【快乐数】【判断是否无限循环，只需要判断新加入的数字是不是在原set中】
class Solution_isH{
    public:
        int bitSquareSum(int n){
            int sum =0;
            while(n){
                sum+=(n%10)*(n%10);
                n/=10;
            }return sum;
        }
        bool ishappy(int n){
            set<int> seen;
            seen.insert(n);
            while(n!=1){
                n = bitSquareSum(n);
                if(seen.insert(n).second==false)return false;
            }return true;
        }
};

int main(){
    return 0;
}