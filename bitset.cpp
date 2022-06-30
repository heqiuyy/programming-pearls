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
    if( a[i>>SHIFT] ==(1<<(i &MASK)))
     return 1;
     else
     return 0;
}

int main(){
    int i = 35;
    cout<<sizeof(a)<<endl;
    cout<<sizeof(a)/sizeof(*a)<<endl;
    set(i);
    if(test(i))
        cout<<"ok"<<endl;
    if(test(55))
        cout<<"ok"<<endl;
    else
          cout<<"no ok"<<endl;
    return 0;
}




