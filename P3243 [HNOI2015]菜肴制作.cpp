#include<cstdio>
#include<iostream>
#include<queue>
#define MAXN 100005

using namespace std;

char c;
int cnt;
int d[MAXN]; //»Î∂» 
int D, n, m, ans[MAXN];
priority_queue<int>q;

struct Edge{
	int v;
	Edge *next;
}pool[MAXN], *h[MAXN];

void init()
{
	for(int i = 1; i <= n; i++)
	{
		d[i] = 0;
		ans[i] = 0;
		h[i] = NULL;
	}
	cnt = 0;
	while(!q.empty())
	    q.pop();
}

void addEdge(int x, int y)
{
	Edge *p = &pool[++cnt];
	p->v = y;
	p->next = h[x];
	h[x] = p;
}

int read()
{
	c = getchar();
	int res = 0;
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
	D = read();
	while(D--)
	{
		n = read(); m = read();
		init();
		for(int i = 1; i <= m; i++)
		{	
			int x, y;
			x = read(); y = read();
			addEdge(y, x);
			d[x]++;
		}
		for(int i = 1; i <= n; i++)
		    if(d[i] == 0)
		        q.push(i);
		int t = 1;
		while(!q.empty())
		{
			ans[t] = q.top();
			q.pop();
			for(Edge *p = h[ans[t]]; p; p = p->next)
			{
				d[p->v]--;
				if(d[p->v] == 0)
				    q.push(p->v);
			}
			t++;
		}
		cout << t << endl;
		if(t != n + 1) printf("Impossible!");
		else
		for(int i = n; i >= 1; i--)
		    printf("%d ", ans[i]);
		printf("\n");
	}
	return 0;
}
