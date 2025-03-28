#include<bits\stdc++.h>
using namespace std;
//加油站
class Solution {
    public:
        int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
            vector<int> diff(gas.size(),0);
        //先求一下全部的差和，如果总差和<0；说明无论从哪里开始都转不了一圈
    //[这里可以把这里的循环放到下面一块循环]
            for(int i = 0;i<gas.size();i++){
                diff[i] = gas[i] - cost[i];
            }
            int sum = 0;
            for_each(diff.begin(),diff.end(),[&](int num){sum+=num;});
            if(sum<0)return -1;

            sum=0;
            int result = 0;
//贪心思路：那么局部最优：当前累加rest[i]的和curSum一旦小于0，起始位置至少要是i+1，因为从i之前开始一定不行。
//全局最优：找到可以跑一圈的起始位置。
            for(int i = result;i<diff.size();i++){
                sum += diff[i];
                if(sum<0){
                    result = i+1;
                    sum = 0;
                }
            }
            if(result==diff.size())return -1;
            return result;
        }
    };
//分发糖果【得分高的人要比他做左右两边得分低的人拿到的果子要多】
//使用最少的糖果
//既要比左大，又要比右大
class Solution {
    public:     //ratings[等级，评分，收视率]
        int candy(vector<int>& ratings) {
            vector<int> arr(ratings.size(),1);
            for(int i = 1;i<arr.size();i++){
                if(ratings[i]>ratings[i-1]){
                    arr[i] = arr[i-1]+1;
                }
            }
    //在原数组的基础上进行修改【不然还得拷贝上一轮改过的东西】
            for(int i = arr.size()-2;i>=0;i--){
                if(ratings[i]>ratings[i+1]){
                    arr[i] = max(arr[i],arr[i+1] + 1);
                }
            }
            int sum = 0;
            for_each(arr.begin(),arr.end(),[&](int num){sum+=num;});
            return sum;
        }
    };
//柠檬水找零【easy】
//贪心：收到20面值时，尽可能先把10抛出去
/*所以局部最优：遇到账单20，优先消耗美元10，完成本次找零。全局最优：完成全部账单的找零。*/
class Solution {
    public:
        bool lemonadeChange(vector<int>& bills) {
            int five = 0,ten = 0;
            for(int i = 0;i<bills.size();i++){
                if(bills[i]==5)five++;
                else if(bills[i]==10){
                    if(five<1)return false;
                    else{
                        ten++;five--;
                    }
                }
                else{
                    if(ten>1&&five>1){
                        ten--;five--;
                    }
                    else if(five>3){
                        five-=3;
                    }
                    else{
                        return false;
                    }
                }
            }
            return true;
        //-2^31 到 2^31 - 1，即 -2147483648 到 2147483647
            INT_MAX;
        }
    };
//按照身高排队列
/*[类似分发糖果：身高排序一次，k排序一次]
每个 people[i] = [hi, ki] 表示第 i 个人的身高为 hi ，前面 正好 有 ki 个身高大于或等于 hi 的人

*/
class Solution {
    public:
    //[时间复杂度：O(nlogn + n^2)]
        vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
            vector<vector<int>> q;
            if(people.size()==0)return q;
            sort(people.begin(),people.end(),[](vector<int>a,vector<int>b){
                if(a[0]==b[0]){return a[1]<b[1];}
                return a[0]>b[0];
            });
            for(int i = 0;i<people.size();i++){
                q.insert(q.begin()+people[i][1],people[i]);
            }
            return q;
        }
    };
//链表实现
class Solution {
    public:
    //[时间复杂度：O(nlogn + n)]
        vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
            list<vector<int>> que;
            sort(people.begin(),people.end(),
                [](vector<int>a,vector<int>b){
                    if(a[0]==b[0]){return a[1]<b[1];}
                    return a[0]>b[0];
                });
            for(int i = 0;i<people.size();i++){
        //这里一定要这样写：链表不支持随机访问
                int pos = people[i][1];
                auto it = que.begin();
                while (pos--)
                {
                    ++it;
                }                
                // it++;
                que.insert(it,people[i]);
            }
            return vector<vector<int>>(que.begin(),que.end());
        }
    };
//用最少数量的箭引爆气球
class Solution {
    public:
        int findMinArrowShots(vector<vector<int>>& points) {
        //时间复杂度O(nlogn)
            if(points.size()==0)return 0;
            int result = 1;
    /*
    这里我用lambda函数超时了，首先vector<int>值传递，复制问题
    问题：每次比较时，Lambda 会复制两个 vector<int> 对象（每个包含两个 int 元素）。
    后果：排序时间复杂度从 O(n log n) 上升为 O(n log n * k)，其中 k 是复制每个 vector 的成本。
        当 n 极大时（如 1e5 数据），频繁复制会导致超时。
    */
            sort(points.begin(),points.end(),
                [](const vector<int>&a,const vector<int>&b)->bool{
                    return a[0]<b[0];
                });
            for(int i = 1;i<points.size();++i){
                if(points[i][0]<=points[i-1][1]){//重叠了
                    points[i][1] = min(points[i][1],points[i-1][1]);
                }
                else{//不重叠得加一
                    result++;
                }
            }
            return result;
        }
    };
//无重叠区间
/*
时间复杂度：O(nlog n) ，有一个快排
空间复杂度：O(n)，有一个快排，最差情况(倒序)时，需要n次递归调用。因此确实需要O(n)的栈空间
*/
class Solution {
    public:
    //左边界排序：失败【相当于首先删除重叠部分最左边的区间】
    //但是可以记录重叠区间的个数
        int eraseOverlapIntervals(vector<vector<int>>& intervals) {
            if(intervals.size()<=1)return 0;
            int result = 0;
            sort(intervals.begin(),intervals.end(),
                [](const vector<int>&a,const vector<int>&b)->bool{
                    //if(a[0]==b[0]){return a[1]>b[1];}
                    return a[0]<b[0];
                });
            for(int i = 1;i<intervals.size();++i){
                if(intervals[i][0]<intervals[i-1][1]){//重叠了得加
                    result++;intervals[i][1] = min(intervals[i][1],intervals[i-1][1]);
                }
                else{
                    
                }
            }
            return result;
            //其实就是对于气球那个题
            {return intervals.size() - result;}
        }
    };
//右边界排序
class Solution {
    public:
        // 按照区间右边界排序
        static bool cmp (const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        }
        int eraseOverlapIntervals(vector<vector<int>>& intervals) {
            if (intervals.size() == 0) return 0;
            sort(intervals.begin(), intervals.end(), cmp);
            int count = 1; // 记录非交叉区间的个数
            int end = intervals[0][1]; // 记录区间分割点
            for (int i = 1; i < intervals.size(); i++) {
                if (end <= intervals[i][0]) {//非交叉区间
                    end = intervals[i][1];
                    count++;
                }
            }
            return intervals.size() - count;
        }
    };
//划分字母区间
/*
    一旦找到一个a，就得找到string中最后一个a
*/
class Solution {
    public:
        vector<int> partitionLabels(string s) {
            vector<int> result;
            vector<int> ha(26,0);
            for(int i = 0;i<s.size();++i){
                ha[s[i]-'a'] = i;
            }//对应字符的最长位置记录完毕
            int end = ha[s[0]-'a'];
            int begin = 0;
            for(int i = 0;i<s.size();i++){
                end = max(end,ha[s[i]-'a']);
                if(i==end){
                    result.push_back(end-begin+1);
                    begin = i+1;
                }
                else{
                    end = max(end,ha[s[i]-'a']);
                }
            }
            return result;
        }
    };
//合并区间
class Solution {
    public:
        vector<vector<int>> merge(vector<vector<int>>& intervals) {
            vector<vector<int>> result;
            sort(intervals.begin(),intervals.end(),[](const vector<int>&a,const vector<int>&b){
                return a[0]<b[0];
            });
            result.push_back(intervals[0]);
            for(int i = 1;i<intervals.size();i++){
                if(result.back()[1]>=intervals[i][0]){
                    //贪心，局部的区间尽可能覆盖最长
                    result.back()[1] = max(result.back()[1],intervals[i][1]);
                }
                else{
                    result.push_back(intervals[i]);
                }
            }
            return result;
        }
    };

int main(){
    return 0;
}