﻿#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<limits>
/*回溯
*/
using namespace std;
//1.组合[给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。]
/*剪枝优化
【比如在4个元素中，组合 四个】
如果for循环选择的起始位置之后的元素个数 已经不足 我们需要的元素个数了，那么就没有必要搜索了。
    n - (k-path.size()) +1
*/
class Solution {
    vector<int> path;
    vector<vector<int>> result;
    public:
        void backtracking(int n,int k,int startindex){
            if(k==path.size()){
                result.push_back(path);
                return;
            }
            for(int i = startindex;i<=n - (k-path.size()) +1;i++){
                path.push_back(i);      //插入
                backtracking(n,k,i+1);  //递归
                path.pop_back();        //回溯
            }
        }
        vector<vector<int>> combine(int n, int k) {
            backtracking(n,k,1);
            return result;
        }
    };
//2.组合总和 【找出所有相加之和为 n 的 k 个数的组合】
// 只使用数字1到9
// 每个数字 最多使用一次
class Solution {
    public:
        vector<int> path;
        vector<vector<int>> result;
        void backtracking(int k,int n,int startindex){
            if(n==0&&k==path.size()){
                result.push_back(path);
                return;
            }
            for(int i =startindex;i<=9;i++){
                if(n-i<0){return;}
                path.push_back(i);
                backtracking(k,n-i,i+1);
                path.pop_back();
            }
        }
        vector<vector<int>> combinationSum3(int k, int n) {
            backtracking(k,n,1);
            return result;
        }
    };
//3.电话号码的字母组合
class Solution {
    public:
        vector<string> letter = {{},{},"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
        vector<string> result;
        string path;
        void backtracking(string& digits,int index){
            if(path.size()==digits.size()){
                result.push_back(path);
                return;
            }
            for(int i =0;i<letter[digits[index]-'0'].size();i++){
                // path.push_back(letter[startindex][i]);
                path+=letter[digits[index]-'0'][i];
                backtracking(digits,index+1);
                path.pop_back();
            }
        }
        vector<string> letterCombinations(string digits) {
            path.clear();
            result.clear();
            if (digits.size() == 0) {
                return result;
            }
            backtracking(digits,0);
            return result;
        }
    };
//4.组合总和
/*
    1.元素可以重复使用
    2.结果集不可以重复
*/
class Solution {
    public:
        vector<vector<int>> result;
        vector<int> path;
        void backtracking(const vector<int>&candidates,int sum,int startindex){
            if(sum==0){
                result.push_back(path);
            }
        //由于元素可以重复选择
        //这里必须提前加入终止递归的条件
        //不然占用栈内存太多
            if(sum<0)return;
            for(int i = startindex;i<candidates.size();i++){
                //下面这段代码配合排序整个候选数组使用
                if(sum-candidates[i]<0)break;
                path.push_back(candidates[i]);
                backtracking(candidates,sum-candidates[i],i);
                path.pop_back();
            }
        }
        vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
            sort(candidates.begin(),candidates.end());
            backtracking(candidates,target,0);
            return result;
        }
    };
//5.组合总和2：
//candidates【包含重复元素】 中的每个数字在每个组合中只能使用 一次
// 注意：解集不能包含重复的组合。 
// 直接复制+改一个参数：失败【有重复元素；[1,7],[1,7]会被选择两边】【需要去重】
        //往深了走：重复是可以的【树枝去重 X】||往横了走：重复就是失败的【树层去重】
class Solution {
    public:
        vector<vector<int>> result;
        vector<int> path;
        vector<bool> used;
        void backtracking(const vector<int>&candidates,int sum,int startindex){
            if(sum==0){
                result.push_back(path);
            }
        //由于元素可以重复选择
        //这里必须提前加入终止递归的条件
        //不然占用栈内存太多
            if(sum<0)return;
            for(int i = startindex;i<candidates.size();i++){
                //下面这段代码配合排序整个候选数组使用
                if(sum-candidates[i]<0)break;
            //这里对于used的赋值重点理解
                if(i!=0&&candidates[i]==candidates[i-1]&&used[i-1]==false){continue;}
                path.push_back(candidates[i]);
                used[i]=true;
                backtracking(candidates,sum-candidates[i],i+1);
                path.pop_back();
                used[i] = false;
            }
        }
        vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
            used.resize(candidates.size(),false);
            sort(candidates.begin(),candidates.end());
            backtracking(candidates,target,0);
            return result;
        }
    };
//6.分割回文子串[做二叉树图]
//要做分割主串
class Solution {
    public:
        vector<vector<string>> result;
        vector<string> path;
        //string s;
        //不包括end
        bool isPalindrome(string& s,int start,int end){
            end--;
            while(start<end){
                if(s[start]!=s[end]){return false;}
                start++;end--;
            }
            return true;
        }
        void backtracking(string& s,int startindex){
            if(startindex>=s.size()){
                result.push_back(path);
            }
            for(int i = startindex;i<s.size();i++){
                // 不包括end
                if(isPalindrome(s,startindex,i+1)){
                    string str = s.substr(startindex,i-startindex+1);
                    path.push_back(str);
                }
                else{
                    continue;
                }
                backtracking(s,i+1);    //继续分割
                path.pop_back();    //回溯
            }
        }
        vector<vector<string>> partition(string s) {
            backtracking(s,0);
            return result;
        }
    };
//7.复制IP地址
class Solution {
    public:
    vector<string> result;
    string path;
        void backtracking(string& s,int startindex){
            //终止条件：遍历到结尾且之加入了三个点
            if(startindex==s.size()&&path.size()==s.size()+3){
                result.push_back(path);return;
            }
            else if(path.size()>s.size()+3)return;
            //起始位置就是0的判定
            if(s[startindex]=='0'){
                string temp = path;
                string str = (path.size()==0)?"":".";
                str+='0';
                path+=str;
                backtracking(s,startindex+1);
                path=temp;
                return;
            }

            for(int i =startindex;i<s.size();i++){
                string temp = path;
                
                if(stoi(s.substr(startindex,i-startindex+1))<=255){
                    string str = (path.size()==0)?"":".";
                    str+=s.substr(startindex,i-startindex+1);
                    path+=str;
                }
                if(stoi(s.substr(startindex,i-startindex+1))>255)break;
                backtracking(s,i+1);
                path = temp;
            }
        }
        vector<string> restoreIpAddresses(string s) {
            backtracking(s,0);
            return result;
        }
    };
//8.子集问题
//  不仅收集叶子节点，而是每个节点
class Solution {
    public:
    vector<vector<int>> result;
    vector<int> path;
        void backtracking(vector<int>& nums,int startindex){
            //这里要提前插入，防止递归终止
            result.push_back(path);
            if(startindex>=nums.size()){
                return;
            }
            for(int i = startindex;i<nums.size();i++){
                path.push_back(nums[i]);
                backtracking(nums,i+1);
                path.pop_back();
            }
        }
        vector<vector<int>> subsets(vector<int>& nums) {
            backtracking(nums,0);
            return result;
        }
    };
//9.子集2【传进来的数组中包含重复元素】
//本题也可以不使用used数组来去重，因为递归的时候下一个startIndex是i+1而不是0。
// 如果要是全排列的话，每次要从0开始遍历，为了跳过已入栈的元素，需要使用used。
class Solution {
    public:
    vector<vector<int>> result;
    vector<int>path;
    vector<bool> used;
        void backtracking(vector<int>& nums,int startindex){
            result.push_back(path);
            if(startindex>=nums.size())return;
            for(int i =startindex;i<nums.size();i++){
                if(i!=0&&nums[i]==nums[i-1]&&used[i-1]==false){
                    continue;
                }
                /*
                    如果不用used数组
                    if(i>startindex&&nums[i]==nums[i-1])效果相同
                */
                path.push_back(nums[i]);
                used[i] = true;
                backtracking(nums,i+1);
                used[i] = false;
                path.pop_back();
            }
        }
        vector<vector<int>> subsetsWithDup(vector<int>& nums) {
            sort(nums.begin(),nums.end());
            used.resize(nums.size(),false);
            backtracking(nums,0);
            return result;
        }
    };
//10.递增子序列<这里集合中至少得两个元素>【有重复元素】
//【这里不允许排序 -- 子序列的顺序要符合原来数组中的顺序】
#include<set>
#include<unordered_set>
class Solution {
    public:
    vector<int> path;
    vector<vector<int>> result;
        void backtracking(vector<int>& nums,int startindex){
            //万万不可放到for里面
            if(path.size()>1){
                result.push_back(path);
            }
            if(startindex==nums.size()){return;}
            unordered_set<int> uset;
            for(int i =startindex;i<nums.size();i++){
                // if(i==0||nums[i]>path.back()){
                //     if(uset.find(nums[i])==uset.end()){
                //         uset.insert(nums[i]);
                //         path.push_back(nums[i]);
                //         backtracking(nums,i+1);
                //         path.pop_back();
                //     }
                // }
                //          这里如果使用vector<int>.back()一定确保vector有 元素
                if((!path.empty()&&nums[i]<path.back())
                    || uset.find(nums[i])!=uset.end()){
                        continue;
                    }
                uset.insert(nums[i]);
                path.push_back(nums[i]);
                backtracking(nums,i+1);
                path.pop_back();
            }
        }
        vector<vector<int>> findSubsequences(vector<int>& nums) {
            backtracking(nums,0);
            return result;
        }
    };
//11.全排列
class Solution {
    public:
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> uset;
        void backtracking(vector<int>& nums){
            if(path.size()==nums.size()){
                result.push_back(path);
                return;
            }
            for(int i = 0;i<nums.size();i++){
                if(uset[i]==true)continue;
                uset[i] = true;
                path.push_back(nums[i]);
                backtracking(nums);
                path.pop_back();
                uset[i] = false;
            }
        }
        vector<vector<int>> permute(vector<int>& nums) {
            uset.resize(nums.size(),false);
            backtracking(nums);
            return result;
        }
    };
//12.全排列2
//给定一个可包含重复数字的序列，要返回所有不重复的全排列。
class Solution {
    public:
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> uset;
        void backtracking(vector<int>& nums){
            if(path.size()==nums.size()){
                result.push_back(path);
                return;
            }
            for(int i = 0;i<nums.size();i++){
                if(uset[i]==true)continue;
                /*这里uset[i-1]==true表示树枝去重；==false表示树层去重【因为全排列【不收集<个数的】】
                对于排列问题，树层上去重和树枝上去重，都是可以的，但是树层上去重效率更高！*/
                if(i!=0&&nums[i]==nums[i-1]&&uset[i-1]==false)continue;
                uset[i] = true;
                path.push_back(nums[i]);
                backtracking(nums);
                path.pop_back();
                uset[i] = false;
            }
        }
        vector<vector<int>> permuteUnique(vector<int>& nums) {
            uset.resize(nums.size(),false);
            sort(nums.begin(),nums.end());
            backtracking(nums);
            return result;
        }
    };
//13. 重新安排行程[去的地方从小到大排序]
                //这里可以用map[map会对key进行默认排序]
// HARD 隔天再写
//难还难在容器的选择和使用上。
#include<map>
#include<unordered_map>
class Solution {
    public:
        vector<string> result;
        //出发地 map(目标地，航班次数)
        unordered_map<string,map<string,int>> tragets;
        bool backtracking(int ticketNum){
            if(result.size()==ticketNum+1){
                return true;
            }
    //加上引用之后，就必须在 string 前面加上 const，因为map中的key 是不可修改了，这就是语法规定了。
    //for(pair<const string,int>& traget: tragets[result[result.size()-1]])
            for(auto& traget : tragets[result[result.size()-1]]){
                if(traget.second>0){
                    //记录到达机场没有飞过
                    traget.second--;
                    result.push_back(traget.first);
                    if(backtracking(ticketNum))return true;
                    traget.second++;
                    result.pop_back();
                }
                
            }
            return false;
        }
        vector<string> findItinerary(vector<vector<string>>& tickets) {
            for(auto i : tickets){
                tragets[i[0]][i[1]]++;
            }
            result.push_back("JFK");
            backtracking(tickets.size());
            return result;    
        }
    };
//14.N皇后
//求出所有解法【返回值为void【整棵树】】
class Solution {
    public:
    vector<vector<string>> result;
    vector<string> path;
        bool isvaild(int row,int col){
        //因为我们对行进行了回溯，所以不用检查 行和本身 合法    
            if(path[row][col]=='Q')return false;
        
            // for(int i = 0;i<path.size();i++){
            //     if(col==i)continue;
            //     if(path[row][i]=='Q')return false;
            // }

            //检查列
            for(int i = 0;i<path.size();i++){
                if(row==i)continue;
                if(path[i][col]=='Q')return false;
            }

            // int minNUM = min(row,col);
            // int maxNUM = max(row,col);
            // for(int i = 0;i<=minNUM;i++){
            //     if(path[row-i][col-i]=='Q')return false;
            // }
            // for(int i = 0;i<=(path.size()-maxNUM-1);i++){
            //     if(path[row+i][col+i]=='Q')return false;
            // }
            //因为是从上往下填的
            //所以只用检查之前被填的地方的Q
             // 检查 45度角是否有皇后
            for (int i = row - 1, j = col - 1; i >=0 && j >= 0; i--, j--) {
                if (path[i][j] == 'Q') {
                    return false;
                }
            }
            // 检查 135度角是否有皇后
            for(int i = row - 1, j = col + 1; i >= 0 && j < path.size(); i--, j++) {
                if (path[i][j] == 'Q') {
                    return false;
                }
            }
            return true;
        }
        void backtracking(int QNums,int Q,int row){
            if(Q==0){
                result.push_back(path);
                return;
            }
            //这里只需要在本列中找位置插入
            /*【row是传进来的，保证一横只有一个Q】
            //即下面的for循环是在 新的一行 中搜索
            for (int col = 0; col < n; col++) {
                if (isValid(row, col, chessboard, n)) { // 验证合法就可以放
                    chessboard[row][col] = 'Q'; // 放置皇后
                    backtracking(n, row + 1, chessboard);
                    chessboard[row][col] = '.'; // 回溯，撤销皇后
            }
    }*/
            for(int i = row;i <QNums;i++){
                for(int j = 0;j<QNums;j++){
                    if(path[i][j]=='.'&&isvaild(i,j)){
                        path[i][j] = 'Q';
                        backtracking(QNums,Q-1,i+1);
                        path[i][j] = '.';
                    }
                }
            }
        }
        vector<vector<string>> solveNQueens(int n) {
            path.resize(n);
            for(int i = 0;i<n;i++){
                for(int j = 0;j<n;j++)path[i] +="."; 
            }
            backtracking(n,n,0);
            return result;
        }
    };
// 上面的回溯算法：递归函数中【for*1 仅仅遍历列】
//15.数独
class Solution {
    public:
        bool isvaild(vector<vector<char>>& board,int row,int col,int num){
            for(int i = 0;i<board.size();i++){
                if(board[i][col]==num+'0')return false;
            }
            for(int i = 0;i<board.size();i++){
                if(board[row][i] ==num+'0')return false;
            }
            
            for(int i = (row/3)*3;i<((row/3)*3+3);i++){
                for(int j = (col/3)*3;j<((col/3)*3+3);j++){
                    if(board[i][j]==num+'0')return false;
                }
            }
            return true;
        }
        bool backtracking(vector<vector<char>>& board,int row,int coll){
            if(row==9)return true;

            for(int col = coll;col < 9;col++){
                if(board[row][col]!='.'){
                    if(col == 8){
                        if(backtracking(board,row+1,0))return true;
                    }
                    continue;
                }
                for(int i = 1;i<=9;i++){
                    if(isvaild(board,row,col,i)){
                        board[row][col] = i+'0';
                        if(col==8){
                            if(backtracking(board,row+1,0))return true;
                        }
                        else{
                            if(backtracking(board,row,col+1))return true;
                        }
                        
                        board[row][col] = '.';
                    }
                }
                return false;
            }
    //对于我的代码来说没必要
    //  遍历完没有返回false，说明找到了合适棋盘位置了
            return true;
            
        }
        //要求：结果唯一 + 在原来的数组中操作
        void solveSudoku(vector<vector<char>>& board) {
            backtracking(board,0,0);
            return;
        }
    };
int main(){
    return 0;
}