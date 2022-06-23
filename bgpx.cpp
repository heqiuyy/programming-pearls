#include<cstdio>
#include<algorithm>
#include<iostream>
#include<functional>
using namespace std;

int main()
{

	int a[]={1,1,4,2,1,9,2,1,999,445,22,33,11,22,66,99,55,33,22};
	sort(a,a+(sizeof(a)/sizeof(*a)),greater<int>());

	for(int i=0;i<(sizeof(a)/sizeof(*a));i++)
	{
		cout<<a[i]<<" ";

	}
return 0;

}