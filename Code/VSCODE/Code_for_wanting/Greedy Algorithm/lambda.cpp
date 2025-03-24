#include<bits/stdc++.h>
/*  //匿名函数
    lambda函数【来自c++11】
[capture list](parameters[参数列表])->return type{function body}
[=]值捕获
    4. mutable 关键字
    默认 Lambda 的 operator() 是 const 的，使用 mutable 允许修改按值捕获的变量：
[&]引用捕获
*/
using namespace std;
int main(){
    vector<int> v_i = {5,6,8,4,2,1};
//匿名函数，不能有名字
    auto compare = [](int a,int b){
        return a>b;
    };
    sort(v_i.begin(),v_i.end(),compare);

    for_each(v_i.begin(),v_i.end(),
        [](int num){cout<<num<<" ";});//这里就是一个lambda函数
    
    int fuck = 10;
    auto multiply = [fuck](int x) mutable{fuck+=10;return fuck*x;};
    printf("fuck  = %d",fuck);
    printf("%d",multiply(10));
    
    int sum = 0;
    auto accumulate = [&](int num){sum+=num;};
    for_each(v_i.begin(),v_i.end(),accumulate);
    printf("sum = %d",sum);
    return 0;
}