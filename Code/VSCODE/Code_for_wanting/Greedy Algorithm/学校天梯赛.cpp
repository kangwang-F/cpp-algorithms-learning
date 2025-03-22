// #include<bits/stdc++.h>
// using namespace std;
// int main(){
//     int n,m;
//     scanf("%d%d",&n,&m);
//     vector<int> nums(n+1,0);
//     for(int i =0;i<n;i++){
//         scanf("%d",&nums[i+1]);
//     }
//     while(m--){
//         int l,r,k;
//         int count = 0;
//         scanf("%d%d%d",&l,&r,&k);
//         for(int i = l;i<=r;i++){
//             if(nums[i]<=k){
//                 count++;
//             }
//         }
//         printf("%d",count);
//     }
//     return 0;
// }


#include<bits/stdc++.h>
using namespace std;
int main(){
    vector<double> a(13,0);
    vector<double> b(13,0);
    vector<double> c(13,0);
    for(int i = 1;i<=12;i++){
        scanf("%lf",&a[i]);
    }
    for(int i = 1;i<=12;i++){
        scanf("%lf",&b[i]);
    }
    for(int i = 1;i<=12;i++){
        scanf("%lf",&c[i]);
    }
    vector<double> Success(13,0);
    for(int i = 1;i<=12;i++){
        //这是解决出本题的概率
        Success[i] = 1- (1-a[i])*(1-b[i])*(1-c[i]);
    }
    vector<vector<double>> dp(13,vector<double>(13,0));
    //0道题中解决出0道的概率是1
    dp[0][0] = 1;
    for(int i = 1;i<=12;i++){
        for(int j = 0;j<=i;j++){

            if(j>0)dp[i][j] = dp[i-1][j-1] * Success[i] + dp[i-1][j] * (1-Success[i]);
            else{
                dp[i][j] = dp[i-1][0]*(1-Success[i]);
            }
        }
    }
    for(int i = 0;i<=12;i++){
        printf("%lf\n",dp[12][i]);
    }
    return 0;
}


// #include<bits/stdc++.h>
// using namespace std;
// int main(){
//     int n,m;
//     scanf("%d%d",&n,&m);
//     vector<int> nums(n+1,0);
//     //int sum1 = 0;
//     int max_ = 0;
//     for(int i = 1;i<=n;i++){
//         scanf("%d",&nums[i]);
//         //sum1+=nums[i];
//         max_ = max(max_,nums[i]);
//     }
//     int result = 0;
//     int end = max_;
//     // for(int i = 1;i<=m;i++){
//     //     int sum = 0;
//     //     for(int j = 1;j<=n;j++){
//     //         sum+=(nums[j]/i);
//     //     }
//     //     if(sum>=m)result = i;
//     //     else{
//     //         break;
//     //     }
//     // }
//     int left = 1;
//     while(left<=end){
//         int mid = left+(end-left)/2;
//         int sum = 0;
//         for(int j = 1;j<=n;j++){
//             sum+=(nums[j]/mid);
//         }
//         if(sum>=m){
//             result = mid;
//             left = mid+1;
//         }
//         else{
//             end = mid - 1;
//         }
//     }
//     printf("%d\n",result);
//     return 0;
// }


#include<bits/stdc++.h>
using namespace std;
int result = 0;
vector<int> path;
int path_num = 0;
//vector<bool> usted;
void backtracking(vector<vector<int>>&nums){
    if(path.size()>(nums.size()-1))return;
    if(path.size()>1&&path.front()==path.back())return;
    if(path_num%2==0 && path.front()!=path.back()){
        result++;
    }
    for(int i = 1;i<nums.size();i++){
        if(nums[path.back()][i]==1){
            path.push_back(i);
            path_num++;
            backtracking(nums);
            path_num--;
            path.pop_back();
        }

    }
}
int main(){
    int n = 0;
    scanf("%d",n);
    vector<vector<int>> arr(n+1,vector<int>(n+1,0));
    for(int i =1;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        arr[x][y] = 1;
        //arr[y][x] = 1;
    }
    for(int i =1;i<=n;i++){
        path.push_back(i);
        backtracking(arr);
        path.pop_back();
    }
    printf("%d\n",result);
    return 0;
}