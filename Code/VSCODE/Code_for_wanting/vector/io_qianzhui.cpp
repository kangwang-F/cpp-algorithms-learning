#include<bits\stdc++.h>
using namespace std;
// C++ 代码 面对大量数据 读取 输出操作，最好用scanf 和 printf，耗时会小很多：
//以下是暴力解法
int main_(){
    int num = 0;
    //cin>>num;
    scanf("%d",&num);
    vector<int> nums(num,0);
    for(int i =0;i<num;i++){
        cin>>nums[i];
    }
    int a,b;
//算法比赛中用来看书否输入到文件尾
//【解释：scanf函数会返回成功赋值数据的个数，like：a，b=>2;若读到文件结尾返回EOF(-1)】
//这个时候，用 ~ 按位取反；只有-1（补码：11111111....*32）会变成 0 即终止循环
    while(~scanf("%d %d",&a,&b)){
        int sum = 0;
        for(int i = a;i<=b;i++){
            sum+=nums[i];
        }//cout<<sum<<endl;
        printf("%d\n",sum);
    }
    return 0;
}
//前缀和解法
int main__(){
    int num = 0;
    //cin>>num;
    scanf("%d",&num);
    //vector<int> nums(num,0);
    vector<int> p(num,0);
    int presum = 0;
    int inp;
    for(int i=0;i<num;i++){
        scanf("%d",&inp);
        presum+=inp;
        p[i] = presum;
    }
    int a=0;int b = 0;
    while(~scanf("%d %d",&a,&b)){
        if(a==0)printf("%d\n",p[b]);
        else{printf("%d\n",p[b]-p[a-1]);}
    }
    return 0;
}
//投资商问题【大型前缀和/double前缀和】
int main_1(){
    int a,b;
    scanf("%d%d",&a,&b);
    //vector<vector<int>> arr(a,vector<int>(b,0));
    vector<int> row(a,0);
    vector<int> col(b,0);
    int sum  = 0;
    for(int i = 0;i<a;i++){
        for(int j = 0;j<b;j++){
            int temp = 0;
            scanf("%d",&temp);
            sum+=temp;
            row[i]+=temp;
            col[j]+=temp;
        }
    }
//还是上一题？
    int res = INT_MAX;
    // int sum = 0;
    // for(int i = 0;i<a-1;i++){
    //     sum+=row[i];
    // }
    int rowcut = 0;
    for(int i =0;i<a-1;i++){
        rowcut+=row[i];
        int sub = sum - rowcut - rowcut;
        res = min(res,abs(sub));
    }
    int colcut = 0;
    for(int i =0;i<b-1;i++){
        colcut+=col[i];
        int sub = sum - colcut-colcut;
        res = min(res,abs(sub));
    }
    printf("%d\n",res);
    return 0;
}


class Solution_luoxuan {
    public:
        vector<vector<int>> generateMatrix(int n) {
            // if(n==1)return {{1}};
            // else{
            //     vector<vector<int>> arr(n,vector<int>(n,0));
            // }
            vector<vector<int>> arr(n,vector<int>(n,0));
            int startx = 0,starty = 0;
            int offset = 1;//终止位置初始为1
            int loop = n/2;
            int count = 1;
            int i,j;
            while(loop--){
                for(j = starty;j<(n-offset);j++){
                    arr[startx][j] = count++;
                }
                for(i = startx;i<(n-offset);i++){
                    arr[i][j] = count++;
                }
                for(;j>=offset;j--){
                    arr[i][j] = count++;
                }
                for(;i>=offset;i--){
                    arr[i][j] = count++;
                }
                startx++;starty++;offset++;

            }
            if(n%2==1){
                arr[n/2][n/2] = count;
            }return arr;
    }
};

int main(){
    Solution_luoxuan s_l;
    vector<vector<int>> arr = s_l.generateMatrix(4);
    for(auto i :arr){
        for(auto j:i){
            printf("%d ",j);
        }
        printf("\n");
    }
    return 0;
}