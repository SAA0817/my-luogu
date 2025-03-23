#include<cstdio>
#include<iostream>

using namespace std;

int gcd(int a, int b)
{
	if(a % b == 0) return b;
	return gcd(b, a%b);
}

char c;
int ans;

int read()
{
	int res = 0;
	c = getchar();
	while(c < '0' || c > '9') c = getchar();
	while(c >= '0' && c <= '9')
	{
		res *= 10;
		res += c - '0';
		c = getchar();
	}
	return res;
}

int main()
{
	int n;
	n = read();
	int t;
	for(int i = 1; i <= n; i++)
	{
		t = read();
		ans = gcd(ans, t);
	}
	cout << ans;
	return 0;
}
