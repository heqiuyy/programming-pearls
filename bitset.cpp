#include<cstdio>
#include<algorithm>
#include<iostream>
#include<functional>
using namespace std;
#define BITSPERWORD 32
#define SHIFT 5
#define MASK 0x1F
#define N 10000000
int a[1+N/BITSPERWORD];
void set(int i)
{
    a[i>>SHIFT] |= (1<<(i &MASK));
}
void clr(int i )
{
    a[i>>SHIFT] &= ~(1<<(i &MASK));
}
int test(int i )
{
}

int main(){
    int i = 35;
    cout<<sizeof(a)<<endl;
    cout<<sizeof(a)/sizeof(*a)<<endl;
    //设置i，也就是置相应位置位1
    set(i);
    //测试是否置1了
    if(test(i))
        cout<<"ok"<<endl;
    return 0;
}