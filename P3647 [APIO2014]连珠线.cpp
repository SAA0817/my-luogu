#include<cstdio>
#include<iostream>
#define MAXN 200005

using namespace std;

int dp[MAXN][2];
int root, r[MAXN];
int cnt, n;
struct Edge{
	int v;
	int len;
	Edge *next;
}pool[MAXN * 2], *h[MAXN];

void addEdge(int x, int y, int len)
{
	Edge *p = &pool[++cnt];
	p->v = y;
	p->len = len;
	p->next = h[x];
	h[x] = p;
}

int read()
{
	bool flag = 0;
	int res = 0;
	char c = getchar();
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
		if(dp[p->v][1]) dp[u][0] += dp[p->v][1] + p->len; //不做中点 
		dp[u][1] = max(dp[u][1], dp[p->v][0] + p->len); //做中点 
		if(p->v == fa) continue;
		dfs(p->v, u);
	}
}

int main()
{
	n = read();
	int x, y, len;
	for(int i = 1; i < n; i++)
	{
		x = read(); y = read(); len = read();
		r[x]++; r[y]++;
		addEdge(x, y, len);
		addEdge(y, x, len);
	}
	for(int i = 1; i <= n; i++)
	    if(r[i] == 1)
	    {
	    	root = i;
	    	break;
		}
	dfs(root, -1);
	cout << max(dp[root][0], dp[root][1]);
	return 0;
}
