#include<cstdio>
#include<iostream>
#define mod 1000000007
#define LL long long
#define MAXN 1000005

using namespace std;

int n, m;
LL sum, ans, q, cnt;
LL f[MAXN];
char c;

LL pow(LL a, LL b)
{
    LL res = 1;
    for(; b; b = b >> 1, a = (a*a)%mod)
        if(b & 1)
            res = (res*a) % mod;
    return res;
}

int read()
{
	int res = 0;
	c = getchar();
	while(c < '0' || c > '9') c = getchar();
	while(c  >= '0' && c <= '9')
	{
		res *= 10;
		res += c - '0';
		c = getchar();
	}
	return res;
}

int main()
{
	f[0] = 1;
	n = read(); m = read();
	for(int i = 1; i <= MAXN; i++)
	    f[i] = (f[i-1] * i) % mod;
	for(int i = 1; i <= m; i++)
	    sum = (sum + read()) % mod;
	if(sum > n)
	{
		cout << 0;
		return 0;
	}
	n -= sum;
	ans = (f[n-m] * f[m-1]) % mod;
	ans = (f[n-1] * pow(ans, mod-2)) % mod;
    cout << ans;
	return 0;
}
