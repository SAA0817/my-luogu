#include<cstdio>
#include<iostream>
#define MAXN 300005
#define LL long long

using namespace std;

int n, m, q, cnt, d, ans, nf;
int len[MAXN], f[MAXN];
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

int getf(int num)
{
	if(f[num] == num) return num;
	return f[num] = getf(f[num]);
}

void init()
{
	for(int i = 1; i <= n; i++)
	{
		f[i] = i;
		len[i] = 0;
	}
}

void dfs(int u, int fa)
{
	for(Edge *p = h[u]; p; p = p->next)
	{
		if(p->v == fa) continue;
		d++;
		dfs(p->v, u);
		if(d > ans)
		{
			nf = p->v;
			ans = d;
		}
		d--;
	}
}

void add(int x, int y)
{
	x = getf(x); y = getf(y);
	if(x == y) return;
	f[x] = y;
	int lx = len[x] - (len[x] / 2), ly = len[y] - (len[y] / 2);
	len[y] = max(len[x], len[y]);
	len[y] = max(len[y], lx + ly + 1);
}

int main()
{
	n = read(); m = read(); q = read();
	int x, y, t;
	init();
	for(int i = 1; i <= m; i++)
	{
		x = read(); y = read();
		addEdge(x, y); addEdge(y, x);
		x = getf(x); y = getf(y);
		f[x] = y;
	}
	for(int i = 1; i <= n; i++)
	{
		if(len[getf(i)] != 0) continue;
		nf = 0; ans = 0; d = 0;
		dfs(i, -1);
		ans = 0; d = 0;
		dfs(nf, -1);
		len[getf(i)] = ans;
	}
	for(int i = 1; i <= q; i++)
	{
		t = read();
		if(t == 1)
		{
			x = read();
			printf("%d\n", len[getf(x)]);
		}
		if(t == 2)
		{
			x = read(); y = read();
			add(x, y);
			//cout << "t:" << getf(y) << " " << len[getf(y)] << endl;
		}
	}
	return 0;
}
