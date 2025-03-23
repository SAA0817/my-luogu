#include<cstdio>
#include<iostream>
#define MAXN 16005
#define INF 2147483647

using namespace std;

int cnt, n, dp[MAXN];
int ans = -INF;
char c;

struct Edge{
	int v;
	Edge *next;
}pool[MAXN*2], *h[MAXN];

void addEdge(int x, int y)
{
	Edge *p = &pool[++cnt];
	p->v = y;
	p->next = h[x];
	h[x] = p;
} 

int read()
{
	bool flag = 0;
	int res = 0;
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

void dfs(int u, int fa)
{
	for(Edge *p = h[u]; p; p = p->next)
	{
		if(p->v == fa) return;
		dfs(p->v, u);
		if(dp[p->v] > 0) dp[u] += dp[p->v];
	}
}

int main()
{
	n = read();
	for(int i = 1; i <= n; i++)
		dp[i] = read();
	int x, y;
	for(int i = 1; i < n; i++)
	{
		x = read(); y = read();
		addEdge(x, y); addEdge(y, x);
	}
	dfs(1, -1);
	for(int i = 1; i <= n; i++)
	    ans = max(ans, dp[i]);
	printf("%d", ans);
	return 0;
}
