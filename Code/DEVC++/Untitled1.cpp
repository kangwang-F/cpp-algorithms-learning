#include<iostream>

using namespace std;
int main() {
    //cout << (3 ^ 5) << endl;
    int nums = 0;
    for (int i = 1; i < 2025; i++) {
        cout << (i ^ 2024) << endl;
        if ((i ^ 2024) < 2024) { nums++; }
    }
    cout << nums << endl;
    return 0;
}
