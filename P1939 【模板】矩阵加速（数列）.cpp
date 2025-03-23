#include<cstdio>
#include<iostream>
#define LL long long
#define MAXN 4
const LL mod = 1000000007;

using namespace std;

int n;
LL c[MAXN][MAXN];
LL ans[MAXN];

void multiply_c()
{
    LL t[MAXN][MAXN];
    for(int i = 1; i <= 3; i++)
        for(int j = 1; j <= 3; j++)
            t[i][j] = 0;
    for(int i = 1; i <= 3; i++)
        for(int j = 1; j <= 3; j++)
            for(int k = 1; k <= 3; k++)
                t[i][j] = (t[i][j] % mod) + (((c[i][k] % mod) * (c[k][j]) % mod) % mod);
    for(int i = 1; i <= 3; i++)
        for(int j = 1; j <= 3; j++)
            c[i][j] = t[i][j];
}

void multiply_ans()
{
	LL t[MAXN];
	for(int i = 1; i <= 3; i++)
	    t[i] = 0;
    for(int i = 1; i <= 3; i++)
        for(int j = 1; j <= 3; j++)
            t[i] = (t[i] + (ans[j] * c[i][j]) % mod) % mod;
    for(int i = 1; i <= 3; i++)
        ans[i] = t[i];
}

void init()
{
    for(int i = 1; i <= 3; i++)
        for(int j = 1; j <= 3; j++)
        {
        	c[i][j] = 0;
        	ans[i] = 0;
        }
    c[1][1] = 1; c[1][3] = 1;
    c[2][1] = 1; c[3][2] = 1;
    ans[1] = 1;
    ans[2] = 1;
    ans[3] = 1;
}

LL pow(int n)
{
    if(n <= 3) return 1;
    n -= 3;
    while(n)
    {
        if(n % 2 == 1)
            multiply_ans();
        multiply_c();
        n = n >> 1;
        //cout << ans[1][1] << endl;
    }
    return ans[1];
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        init();
        printf("%lld\n", pow(n));
    }
    return 0;
}
