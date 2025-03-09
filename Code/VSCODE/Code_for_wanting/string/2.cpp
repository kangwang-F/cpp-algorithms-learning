/*字符串的右旋转操作是把字符串尾部的若干个字符转移到字符串的前面。
给定一个字符串 s 和一个正整数 k，
请编写一个函数，将字符串中的后面 k 个字符移到字符串的前面，实现字符串的右旋转操作。 
例如，对于输入字符串 "abcdefg" 和整数 2，函数应该将其转换为 "fgabcde"。*/
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
//#include<bits/stdc++.h>
using namespace std;
int main(){
    int k = 0;
    string s;
    cin>>k>>s;
    reverse(s.begin(),s.end());
    reverse(s.begin(),s.begin()+k);
    reverse(s.begin()+k,s.end());
    cout<<s<<endl;
    return 0;
}


//6.字符串匹配【返回第一个匹配项的下标】

//暴力
class Solution {
    public:
        int strStr(string haystack, string needle) {
            for(int i =0;i<haystack.size();i++){
                int j =0;bool index = 1;
                                //条件取 并         ‘aaa’   'aaaa'
                for(int start = i;(start<haystack.size()&&j<needle.size());j++){
                    if(haystack[start++]!=needle[j]){index=0;break;}
                }

                if(index&&j==needle.size())return i;
            }return -1;
        }
};
//KMP算法   【先求前缀和】
class Solution {
    public://匹配失败回到nextval[j]
        void GetNextval(string s,vector<int>& nextval){
            nextval.resize(s.size(),0);
            nextval[0] = 0;
            int i = 1,k=0;
            while(i<s.size()){
                if(k==0||s[i]==s[k]){//s[i]后缀的单个字符，s[k]前缀的单个字符
                    i++;
                    k++;
                    if(s[i]!=s[k])//若当前字符与前缀字符不相同，
                        nextval[i] = k;
                    else//相同
                        nextval[i] = nextval[k];
                }
                else{
                    k = nextval[k]; //若字符不相同，回溯k
                }
            }   
        }//匹配失败回到next[j]
        void GetNext(string s,vector<int>& next){
            next.resize(s.size(),0);
            next[0] = 0;
            int i =0;
            for(int j=1;j<s.size();j++){
                while(i>0&&s[j]!=s[i]){
                    i = next[i-1];
                }
                if(s[i]==s[j])i++;
                next[j] = i;
            }      
        }
        int strStr(string haystack, string needle) {
            vector<int> next;
            GetNextval(needle,next);
            int j =0;
            for(int i = 0;i<haystack.size();i++){
                while(j>0&&needle[j]!=haystack[i]){
                    j =next[j-1];
                }
                if(needle[j]==haystack[i])j++;
                if(j==needle.size())return (i-needle.size()+1);
            }return -1;
        }
};
//7.重复子字符串
//法一：s+s 【数学推理法】
class Solution {
    public:
        bool repeatedSubstringPattern(string s) {
            string temp = s+s;
            temp.erase(temp.begin());
            temp.erase(temp.end()-1);
            if(temp.find(s)!=string::npos)return true;
            return false;            
        }
};
//KMP算法
class Solution {
    public:
    void GetNext(string s,vector<int>& next){
        next.resize(s.size(),0);
        next[0] = 0;
        int i =0;
        for(int j=1;j<s.size();j++){
            while(i>0&&s[j]!=s[i]){
                i = next[i-1];
            }
            if(s[i]==s[j])i++;
            next[j] = i;
        }      
    }
        bool repeatedSubstringPattern(string s) {
            vector<int> next(s.size());
            GetNext(s,next);
        //最长的相等前后缀 一定要到底
            if(next[s.size()-1]!=0&&
                    s.size()%(s.size()-next[s.size()-1])==0){
                return true;
            }return false;
        }
    };