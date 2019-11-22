#include<iostream>
using namespace std;
int main(){
    int *a;
    a = new int;
    *a=2;
    int b;
    b = *a;
    *a = 3;
    cout<<b<<endl;
    int *c;
    if (c==nullptr){cout<<'t'<<endl;}
    cout<<c<<endl;
    c = a;
    cout<<a<<' '<<c<<endl;
    delete(c);
}

