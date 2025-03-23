#include<cstdio>
#include<iostream>
#define LL long long

using namespace std;

char c;
int n;
LL sum, ans;

LL read()
{
	LL res = 0;
	bool flag = 0;
	c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') 
	{
		flag = 1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		res *= 10;
		res += c - '0';
		c = getchar();
	}
	if(flag) res = -res;
	return res;
}

int main()
{
	n = read();
	ans = read(); sum = ans;
	for(int i = 2; i <= n; i++)
	{
		sum = max(sum, 0LL);
		sum += read();
		ans = max(ans, sum);
	}
	cout << ans;
	return 0;
}
