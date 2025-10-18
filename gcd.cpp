#include<iostream>
using namespace std;
//o(log(min(a,b)))
int gcd(int a,int b){
    while(b!=0){
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int main(){
    int a = 24,b=21;
    cout<<gcd(a,b);
}