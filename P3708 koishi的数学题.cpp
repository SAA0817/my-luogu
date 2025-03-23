#include<cstdio>
#include<iostream>
#define MAXN 1000005

using namespace std;

int sum[MAXN];
int n, ans;

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	    for(int j = i; j <= n; j += i)
	        sum[j] += i;
	for(int i = 1; i <= n; i++)
	{
		ans += n;
		ans -= sum[i];
		printf("%d ", ans);
	}
	return 0;
}
