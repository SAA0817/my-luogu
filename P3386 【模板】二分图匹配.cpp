#include<cstdio>
#include<iostream>
#define LL long long
#define MAXN 1005

using namespace std;

char c;
int n1, n2, m;
int cnt, ans;
bool vis[MAXN];
int s[MAXN];
int dfn[MAXN];

struct Edge{
	int v;
	Edge *next;
}pool[MAXN * MAXN], *h[MAXN];

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

bool solve(int u, int vistime)
{
	dfn[u] = vistime;
	for(Edge *p = h[u]; p; p = p->next)
	{
		if(dfn[s[p->v]] == vistime) continue;
		if(!vis[p->v])
		{
			vis[p->v] = 1;
			s[p->v] = u;
			return true;
		}
		if(solve(s[p->v], vistime)) return true;
	}
	
	return false;
}

void dfs(int u)
{
	if(u > n1) return; 
	//cout << u << " " << ans <<endl;
	for(Edge *p = h[u]; p; p = p->next)
	{
		if(!vis[p->v])
		{
			vis[p->v] = 1;
			s[p->v] = u;
			ans++;
			dfs(u+1);
			return;
		}
	}
	//cout << "s";
	for(Edge *p = h[u]; p; p = p->next)
		if(solve(s[p->v], u))
		{
			s[p->v] = u;
			vis[p->v] = 1;
			ans++;
			dfs(u+1);
			return;
		}
	dfs(u+1);
}

int main()
{
	//freopen("testdata.in", "r", stdin);
	n1 = read(); n2 = read(); m = read();
	int x, y;
	for(int i = 1; i <= m; i++)
	{
		x = read(); y = read();
		if(y > n2) continue;
		addEdge(x, y);
	}
	dfs(1);
	cout << ans << endl;
	return 0;
}
