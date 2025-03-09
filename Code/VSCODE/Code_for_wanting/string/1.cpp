#include<bits/stdc++.h>
using namespace std;
//1.反转字符串
class Solution {
    public:
        void reverseString(vector<char>& s) {
            int left = 0;int right =s.size()-1;
            while(left<(s.size()/2)){
                swap(s[left],s[right]);
                left++;right--;
            }    
        }
};
//2.反转字符串2
class Solution_ {
    public:
    //左闭右开
        void reverse_m(string& s,int begin,int end){
            for(end--;begin<=end;){
                swap(s[begin++],s[end--]);
            }
        }
        string reverseStr(string s, int k) {
            //i递增，步长为2k
            for(int i=0;i<s.size();i+=(2*k)){
                //如果i + k < = s.size() 反转
                if(i+k<=s.size()){
                    //左闭右开
                    //reverse(s.begin()+i,s.begin()+i+k);
                    reverse_m(s,i,i+k);
                }//不够k个，反转到完
                else{
                    //reverse(s.begin()+i,s.end());
                    reverse_m(s,i,s.size());
                }
            }return s;      
        }
    };
//3.替换数字[给定一个字符串 s，它包含小写字母和数字字符，请编写一个函数，
// 将字符串中的字母字符保持不变，而将每个数字字符替换为number。 
// 例如，对于输入字符串 "a1b2c3"，函数应该将其转换为 "anumberbnumbercnumber"。]
int main(){
    string s;
    cin>>s;
//法一：利用库函数 插入 删除
    // string number = "number";
    // for(int i=0;i<s.size();i++){
    //     if(s[i]>='0'&&s[i]<='9'){
    //         s.insert(i,number);i+=6;s.erase(i,1);
    //     }
    //     else{i++;}
    // }
    // int i = 0;
    // while (i < s.size()) {
    //     if (s[i] >= '0' && s[i] <= '9') {
    //         // 插入 "number"
    //         s.insert(i, number);
    //         // 跳过插入的 "number"
    //         i += number.size();
    //         // 删除原数字字符
    //         s.erase(i, 1);
    //     } else {
    //         // 非数字字符，继续检查下一个字符
    //         i++;
    //     }
    // }
//法二：快慢指针法[ 新字符串结尾 和 旧字符串结尾 ]
    int Oldindex = s.size()-1;
    int count= 0;
    for(int i=0;i<s.size();i++){
        if(s[i]>='0'&&s[i]<='9'){
            count++;
        }
    }
    s.resize(s.size()+count*5);
    int Newindex = s.size()-1;

    while(Oldindex>=0){
        if(s[Oldindex]>='0'&&s[Oldindex]<='9'){
            s[Newindex--] = 'r';
            s[Newindex--] = 'e';
            s[Newindex--] = 'b';
            s[Newindex--] = 'm';
            s[Newindex--] = 'u';
            s[Newindex--] = 'n';
        }
        else{
            s[Newindex--] = s[Oldindex];
        }Oldindex--;
    }
    cout<<s;
    return 0;
}

//4.反转字符串中的单词[先整体反转，再逐个反转]
class Solution_4 {
    public://去除字符串中的多余空格【可以用erase()，但是erase时间复杂度为o(n)+for = n^2】
    void removeExtraSpaces_erase(string& s) {
        //去除连续的空格【最多保留一个】
        for (int i = s.size() - 1; i > 0; i--) {
            if (s[i] == s[i - 1] && s[i] == ' ') {
                s.erase(s.begin() + i);
            }
        }
        // 删除字符串最后面的空格
        if (s.size() > 0 && s[s.size() - 1] == ' ') {
            s.erase(s.begin() + s.size() - 1);
        }
        // 删除字符串最前面的空格
        if (s.size() > 0 && s[0] == ' ') {
            s.erase(s.begin());
        }
    }
    //双指针法
    void removeExtraSpaces_double(string& s){
        int slow = 0;
        for(int i=0;i<s.size();i++){
            if(s[i]!=' '){
                //手动控制空格
                if(slow!=0)s[slow++]=' ';
                //复制下一个字符串
                while(i<s.size()&&s[i]!=' '){
                    s[slow++]=s[i++];
                }
            }
        }s.resize(slow);
    }
    string reverseWords(string s) {            
        reverse(s.begin(),s.end());
        int start = 0;
        for(int i = 0;i<=s.size();i++){
            //找到字符串的最后，或者【单词的结尾】
            if(i==s.size() || s[i]==' ')reverse(s.begin()+start,s.begin()+i);
            start = i+1;
        }return s;
    }
};
