#include<cstdio>
#include<iostream>
#define MAXN 205

using namespace std;

int s[MAXN];
int n;
int dfn[MAXN];
int map[MAXN][MAXN];
bool vis[MAXN];

void init()
{
	for(int i = 1; i <= n; i++)
	{
		dfn[i] = 0;
		s[i] = 0;
		vis[i] = 0;
	}
}

bool dfs(int u, int vistime)
{
	dfn[u] = vistime;
	for(int i = 1; i <= n; i++)
	{
		if(!vis[i] && map[u][i])
		{
			s[i] = u;
			vis[i] = 1;
			return true;
		}
	}
	for(int i = 1; i <= n; i++)
	{
		if(map[u][i])
		{
			if(dfn[s[i]] == vistime) continue;
			if(dfs(s[i], vistime)) return true;
		}
	}
	return false;
}

int main()
{
	int D;
	scanf("%d", &D);
	while(D--)
	{
		scanf("%d", &n);
		init();
		for(int i = 1; i <= n; i++)
		    for(int j = 1; j <= n; j++)
		        scanf("%d", &map[i][j]);
		for(int i = 1; i <= n; i++)
		{
			if(!dfs(i, i))
			{
				printf("No\n");
				break;
			}
			if(n == i)printf("Yes\n");
		}
	}
	return 0;
}
