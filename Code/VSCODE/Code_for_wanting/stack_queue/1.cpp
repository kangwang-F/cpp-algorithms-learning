#include<bits.\stdc++.h>
using namespace std;
//1.用栈实现队列
/*拓展
可以看出peek()的实现，直接复用了pop()， 要不然，对stOut判空的逻辑又要重写一遍。

再多说一些代码开发上的习惯问题，在工业级别代码开发中，最忌讳的就是 实现一个类似的函数，直接把代码粘过来改一改就完事了。

这样的项目代码会越来越乱，一定要懂得复用，功能相近的函数要抽象出来，不要大量的复制粘贴，很容易出问题！（踩过坑的人自然懂）

工作中如果发现某一个功能自己要经常用，同事们可能也会用到，自己就花点时间把这个功能抽象成一个好用的函数或者工具类，不仅自己方便，也方便了同事们。

同事们就会逐渐认可你的工作态度和工作能力，自己的口碑都是这么一点一点积累起来的！在同事圈里口碑起来了之后，你就发现自己走上了一个正循环，以后的升职加薪才少不了你！*/
class MyQueue_me {
    public:
        MyQueue_me() {
            size=0;   
        }
        
        void push(int x) {
            s_in.push(x);size++;
        }
        
        int pop() {
            stack<int> s_out;
            int num =size;
            for(int i =0;i<size;i++){
                s_out.push(s_in.top());
                s_in.pop();
            }
            int res = s_out.top();
            s_out.pop();
            size--;
            for(int i =0;i<size;i++){
                s_in.push(s_out.top());
                s_out.pop();
            }
            return res;
        }
        
        int peek() {
            int res = pop();
            stack<int> s_out;
            for(int i =0;i<size-1;i++){
                s_out.push(s_in.top());
                s_in.pop();
            }
            s_in.push(res);
            for(int i =0;i<size-1;i++){
                s_in.push(s_out.top());
                s_out.pop();
            }
            return res;
        }
        
        bool empty() {
            if(this->size)return true;
            return false;
        }
        stack<int> s_in;
        int size;
};
class Myqueue{
    public://直接定义两个栈出来，然后查数据主要看in，pop主要看out
    stack<int> s_in;
    stack<int> s_out;
    Myqueue(){}
    void push(int x){s_in.push(x);}
    int pop(){
        if(s_out.empty()){
            while(!s_in.empty()){
                s_out.push(s_in.top());
                s_in.pop();
            }
        }
        int res = s_out.top();
        s_out.pop();
    }
    int peek(){
        int res = pop();
        s_out.push(res);
        return res;
    }
    bool empty(){
        return (s_in.empty()&&s_out.empty());
    }
};
//2.用队列实现栈
//一个队列也可以，除了最后一个元素以外，其他吐出去再加入队尾
class MyStack {
    public:
        queue<int> q;
        MyStack() {
            
        }
        
        void push(int x) {
            q.push(x);
        }
        
        int pop() {
            int size = q.size();
            size--;
            while(size--){
                // front 前面 【队头】
                q.push(q.front());
                q.pop();
            }
            int res = q.front();
            q.pop();
            return res;
        }
        
        int top() {
            int res = pop();
            q.push(res);return res;
        }
        
        bool empty() {
            return q.empty();
        }
};
//有效的括号
class Solution {
    public:
        bool isValid(string s) {
            //if(s.size()==0)return true;
            if(s.size()%2==1)return false;
            string s_left = "{[(";
            stack<char> st_c;
            for(int i =0;i<s.size();i++){
                if(s_left.find(s[i])!=-1){
                    st_c.push(s[i]);
                }
                else{
                    if((st_c.top()=='{'&&s[i]=='}')||(st_c.top()=='('&&s[i]==')')
                            ||(st_c.top()=='['&&s[i]==']')){
                        st_c.pop();
                    }
                    else{
                        return false;
                    }
                }
            }
            if(st_c.empty()){
                return true;
            }
            else{
                return false;
            }
        }
};
class Solution_ {
    public:
        bool isValid(string s) {
            if (s.size() % 2 != 0) return false; // 如果s的长度为奇数，一定不符合要求
            stack<char> st;
            for (int i = 0; i < s.size(); i++) {
                if (s[i] == '(') st.push(')');
                else if (s[i] == '{') st.push('}');
                else if (s[i] == '[') st.push(']');
                // 第三种情况：遍历字符串匹配的过程中，栈已经为空了，没有匹配的字符了，说明右括号没有找到对应的左括号 return false
                // 第二种情况：遍历字符串匹配的过程中，发现栈里没有我们要匹配的字符。所以return false
                else if (st.empty() || st.top() != s[i]) return false;
                else st.pop(); // st.top() 与 s[i]相等，栈弹出元素
            }
            // 第一种情况：此时我们已经遍历完了字符串，但是栈不为空，说明有相应的左括号没有右括号来匹配，所以return false，否则就return true
            return st.empty();
        }
};
//5.删除重复项
class Solution {
    public:
        string removeDuplicates(string s) {
            stack<char> s_c;
            int i = 0;
            int slow = -1;
            while(i<s.size()){
                // if(s_c.empty()){
                //     s_c.push(s[i]);
                //     slow++;
                //     i++;
                // }
                // else{
                //     if(s_c.top()==s[i]){
                //         s_c.pop();
                //         slow--;
                //         i++;

                //     }
                //     else{
                //         s_c.push(s[i]);
                //         slow++;
                //         s[slow] = s[i];
                //         i++;
                //     }
                // }
                if(s_c.empty()||s_c.top()!=s[i]){
                    s_c.push(s[i]);
                    slow++;
                    s[slow]=s[i];
                    i++;
                }
                else{
                    s_c.pop();
                    slow--;
                    i++;
                }
            }return string(s.begin(),s.begin()+slow+1);            
        }
};
//直接用字符串做栈
class Solution {
    public:
        string removeDuplicates(string s) {
            string res;
            for(char c:s){
                if(res.empty()||res.back()!=c){
                    res.push_back(c);
                }
                else{
                    res.pop_back();
                }
            }
            return res;
        }
};
//6.逆波兰表达式求值
class Solution {
    public:
        int evalRPN(vector<string>& tokens) {
            stack<int> s_i;
            for(string i : tokens){
                if(i=="+"||i=="-"||i=="*"||i=="/"){
                    int a = s_i.top();
                    s_i.pop();
                    int num;
                    int b = s_i.top();
                    s_i.pop();
                    if(i=="+")num = a+b;
                    else if(i=="-")num = b-a;
                    else if(i=="*")num = a*b;
                    else num = b/a;
                    s_i.push(num);
                }
                else{
                    s_i.push(stoi(i));
                }
            }return s_i.top();
        }
};
//滑动窗口最大值
class Solution {
    public:
        //小顶堆
        class Queue{
                public:
                deque<int> dq;
                Queue(){}
                void pop(int x){
                    if(dq.front()==x){
                        dq.pop_front();
                    }
                }
                void push(int x){
                    while(!dq.empty()&&dq.back()<x){
                        dq.pop_back();
                    }
                    dq.push_back(x);
                }
                int front(){
                    return dq.front();
                }
            };
            vector<int> maxSlidingWindow(vector<int>& nums, int k) {
                vector<int> res;
                //暴力：超时了
                /*for(int i =0;i<=nums.size()-k;i++){
                    res.push_back(*(max(nums.begin()+i,nums.begin()+i+k)));   
                }return res;*/
                //单调队列【小顶堆（每次pop吐出来最小的元素） 自己实现】
                Queue q;
                //先处理前k个元素
                for(int i =0;i<k;i++)
                    q.push(nums[i]);
                res.push_back(q.front());
                for(int i =k;i<nums.size();i++){
                    //后续处理时，先pop前一个最前面的
                    q.pop(nums[i-k]);
                    //再加入新的
                    q.push(nums[i]);
                    res.push_back(q.front());
                }return res;
            }
    };
//前k个高频元素
class Solution {
    public:
        class Mycmp{
            public:
            bool operator()(const pair<int,int>& lp,const pair<int,int>& rp){
                return lp.second > rp.second;
            }
        };
        vector<int> topKFrequent(vector<int>& nums, int k) {
            unordered_map<int,int> u_m;
            for(int i = 0;i<nums.size();i++){
                u_m[nums[i]]++;
            }
            //这里可以用qsort;但是对整个数组都进行了排序，时间复杂度是O(nlogn)
            priority_queue<pair<int,int>,vector<pair<int,int>>,Mycmp> p_q;
                                            //这里这个cmp比较类里面的()一定要是public的
            for(auto a:u_m){
            //这里先向优先队列压入东西，再看是否要吐出最小的【用最后一个元素帮助理解】
                p_q.push(a);

                if(p_q.size()>k){
                    p_q.pop();
                }
            }
            vector<int> res;
            for(int i = 0;i<k;i++){
                res.push_back(p_q.top().first);
                p_q.pop();
            }
        }
};

//最快的方法
class Solution {
    public:
    //原理是用map【小顶堆】然后map<频数，频数对应 数字数组(可能多个数字出现的频率都等于他)>
        vector<int> topKFrequent(vector<int>& nums, int k) {
            map<int,vector<int>> mp;
            unordered_map<int,int> count;
            for(auto x:nums){
                count[x]++;
            }
            for(auto m:count){
                mp[m.second].push_back(m.first);
            }
    
            auto p=--mp.end();
            vector<int> res;
            for(int i=0;i<k;){
                for(auto x: p->second){
                    res.push_back(x);
                    i++;
                    if(i>k-1) break;
                }
                --p;
            }
            return res;
        }
};
    int main(){
    stack<int> s;

    return 0;
}