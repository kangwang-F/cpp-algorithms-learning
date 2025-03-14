#include<iostream>
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
        vector<string> letterCombinations(string digits) {
            
        }
    };

int main(){
    return 0;
}