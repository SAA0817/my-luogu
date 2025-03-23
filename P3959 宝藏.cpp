#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<ctime>
#include<cmath>
#define LL long long 
#define mod 105
#define MAXN 15
#define MAXM MAXN * MAXN
#define INF 1e9 + 7

using namespace std;

const double eps = 1e-10, Dlt = 0.97;
char c;
int n, m, cnt;
int ans, tot, res, cnt2;
int map[MAXN][MAXN];
int f[MAXN];
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

struct Edge{
	int v;
	int w;
	Edge *next;
}pool[MAXM<<1], *h[MAXN];

struct Edge2{
	int x;
	int y;
	int w;
}E[MAXM];

void addEdge(int x, int y, int w)
{
	Edge *p = &pool[++cnt];
	p->v = y;
	p->w = w;
	p->next = h[x];
	h[x] = p;
	//cout << x << " " << y << " " << w << endl;
}

bool cmp(Edge2 a, Edge2 b)
{
	return a.w < b.w;
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
		h[i] = NULL;
	}
	cnt = 0;
	cnt2 = 0;
	res = INF;
}

int dfs(int u, int fa, int d)
{
	int r = 0;
	for(Edge *p = h[u]; p; p = p->next)
	{
		if(p->v == fa) continue;
		r += (p->w) * d;
		r += dfs(p->v, u, d+1);
	}
	return r;
}

int solve()
{
	int x, y;
	init();
	for(int i = 1; i <= tot; i++)
	{
		//ÖØ½¨Ê÷
		x = E[i].x; y = E[i].y;   
		if(getf(x) == getf(y)) continue;
		f[getf(y)] = f[x];
		addEdge(x, y, E[i].w);
		addEdge(y, x, E[i].w);
		cnt2++;
	}
	if(cnt2 != n-1) return INF;
	//dfs
	for(int i = 1; i <= n; i++)
	    res = min(dfs(i, -1, 1), res);
	return res;
}

void sp(Edge2 x, Edge2 y)
{
	Edge2 t = x;
	x = y;
	y = t;
}

int main()
{
	srand(19260817);
	n = read(); m = read();
	if(n == 1)
	{
		cout << 0;
		return 0;
	}
	int x, y, w;
	for(int i = 1; i <= n; i++)
	    for(int j = 1; j <= n; j++)
	        map[i][j] = INF;
	for(int i = 1; i <= m; i++)
	{
		x = read(); y = read(); w = read();
		map[x][y] = min(map[x][y], w);
		map[y][x] = min(map[y][x], w);
	}
	tot = 0;
	for(int i = 1; i <= n; i++)
	    for(int j = 1; j <= n; j++)
	    	if(map[i][j] != INF)
	    	{
	    		//cout << "tot:" << i << " " << j << endl;
	    		E[++tot].x = i;
	    		E[tot].y = j;
	    		E[tot].w = map[i][j];
			}
	sort(E + 1, E + tot + 1, cmp);
	//cout << endl;
	//system("pause");
	ans = solve();
	//cout << ans << endl;
	
	int time = 200;
	while(time--)
	{
		int now = INF;
		for(double T = 100000; T > eps; T *= Dlt) 
		{
			cout << T << endl;
            int x = (rand() % tot) + 1;
			int y = (rand() % tot) + 1;
            sp(E[x], E[y]);
            int nxt = solve();
            if(nxt < ans)
			{
			    ans = nxt;
			    //cout << x << " " << y << endl;
				continue;
			}
            if(nxt < now || ((exp(now - nxt / T) < rand() / RAND_MAX)))
			{
			    now = nxt;
				continue;
			}
            sp(E[x], E[y]);
        }
	}
	cout << ans;
	return 0;
}
