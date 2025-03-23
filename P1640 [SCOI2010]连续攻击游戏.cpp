#include<cstdio>
#include<iostream>
#include<cstring>
#define MAXN 1000005

using namespace std;

int n, cnt;
int x, y;
char c;
bool vis[MAXN], s[MAXN];

struct Edge{
	int v;
	Edge *next;
}pool[MAXN * 2], *h[MAXN];

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

void addEdge(int x, int y)
{
	Edge *p = &pool[++cnt];
	p->v = y;
	p->next = h[x];
	h[x] = p;
}

bool dfs(int u)
{
	if(vis[u]) return false;
	vis[u] = 1;
	for(Edge *p = h[u]; p; p = p->next)
		if(!s[p->v] || dfs(s[p->v]))
		{
			s[p->v] = u;
			return true;
		}
    return false;
}

int main()
{
	n = read();
	for(int i = 1; i <= n; i++)
	{
		x = read(); y = read();
		addEdge(x, i);
		addEdge(y, i);
	}
	for(int i = 1; i <= n + 1; i++)
	{
		memset(vis, 0, sizeof(vis));
		if(!dfs(i))
		{
			cout << i - 1;
			return 0;
		}
	}
	return 0;
}
