#include<bits\stdc++.h>
using namespace std;
#include<vector>
int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    vector<vector<int>> arr(a,vector<int>(b,0));
    // for(auto i:arr){
    //     for(auto j:(i)){
    //         scanf("%d",&j);
    //     }
    // }//生成的仅仅是arr中每个元素的副本
   /* for(int i = 0;i<a;i++){
        for(int j  =0;j<b;j++){
            scanf("%d",&(arr[i][j]));
        }
    }*///这个是正常的
//解决办法：for(auto& i : arr)
    for(auto& i :arr){
        for(auto& j :i){
            scanf("%d",&j);
        }
    }
    for(auto i:arr){
        for(auto j:(i)){
            printf("%d ",j);
        }printf("\n");
    }
    return 0;
}