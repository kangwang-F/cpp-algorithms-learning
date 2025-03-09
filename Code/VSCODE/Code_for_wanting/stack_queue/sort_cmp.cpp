#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
class cmp{
    public:
    bool operator()(const int v1,const int v2){
        return v1>v2;
    }
};
bool cmp_(int v1,int v2){
    return v1>v2;
}
int main(){
    vector<int> v = {5,4,9};
// 默认是升序，改成降序：cmp里的v1>v2
    sort(v.begin(),v.end(),cmp_);
    for(auto i:v){
        cout<<i<<endl;
    }
    return 0;
}