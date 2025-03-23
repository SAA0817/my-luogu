#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#define LL long long
#define MAXN 10005
#define MAXM 100005

using namespace std;

int n, m;
char c;
int cnt, time, top, r[MAXN];
int low[MAXN], dfn[MAXN], stk[MAXN], f[MAXN];
bool vis[MAXN];

struct Edge{
	int from;
	int v;
	Edge *next;
}pool[MAXM], *h[MAXN], pool2[MAXN], *h2[MAXN];

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
	p->from = x;
	p->v = y;
	p->next = h[x];
	h[x] = p;
}

void addEdge2(int x, int y)
{
	Edge *p = &pool2[++cnt];
	p->from = x;
	p->v = y;
	p->next = h2[x];
	h2[x] = p;
}

void rebuild()
{
	int x, y;
	cnt = 0;
	for(int i = 1; i <= m; i++)
	{
		x = pool[i]->from;
		y = pool[i]->v;
		addEdge2(x, y);
		r[y]++;
	}
}

void tarjan(int num)
{
	dfn[num] = ++time; low[num] = dfn[num];
	stk[++top] = num; vis[num] = 1;
	for(Edge *p = h[num]; p; p = p->next)
	{
		if(!dfn[p->v])
		{
			tarjan(p->v);
			low[num] = min(low[num], low[p->v]);
		}
		else if(vis[p->v]) low[num] = min(low[num], low[p->v]);
	}
	
	if(dfn[i] == low[i])
	{
		stk[++top] = 0;
		while(stk[top] != num)
		{
			top--;
			int t = stack[top];
			vis[t] = 0;
			f[p->v] = num;
			v[num] += v[p->v];
		}
	}
}

void topo()
{
	queue<int> q;
	for(int i = 1; i <= n; i++)
	    if(!r[i])
	        q.push(i);
	while(!q.empty())
	{
		  
	}
}

int main()
{
	int x, y;
	n = read();
	m = read();
	for(int i = 1; i <= n; i++)
	    v[i] = read();
	for(int i = 1; i <= m; i++)
	{
		x = read(); y = read();
		addEdge(x, y);
	}
	for(int i = 1; i <= n; i++)
	    if(!dfn[i])
	        tarjan(i);
	rebuild();
	
	return 0;
}
