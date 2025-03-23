#include<cstdio>
#include<stack>
#define MAXN 10005
#define MAXM 100005
using namespace std;
int n, m, x, y, tot, scccnt, dfn, a[MAXN], pre[MAXN], low[MAXN], scc[MAXN];
int sccv[MAXN], inde[MAXN], dp[MAXN];
//sccv数组存储每个缩点的总权值，inde存储每个缩点的入度
//dp[i]表示的状态含义是从i点出发能得到的最大权值和
//记忆化搜索可以写成dp[u] = sccv[u]+max(dp[v]), u->v连通
//还可以用顺推实现，此时dp[i]表示的就是到达i点能得到的最大权值和
//类似多源最长路spfa算法，先把所有入度为零的点入队列
//然后进行bfs，更新dp值，注意这里有一个优化是只把入度为零的结点入队列
//保证每个节点只进队一次 
struct road{
	int v;
	road *next;
}*h[MAXN], *hnew[MAXN], pool[MAXM<<1];
stack<int> q;
void addedge(int u, int v)
{
	road *p = &pool[tot++];
	p->v = v; p->next = h[u]; h[u] = p;
}
void addedge2(int u, int v)
{
	road *p = &pool[tot++];
	p->v = v; p->next = hnew[u]; hnew[u] = p;
}
void dfs(int u)
{
	q.push(u);
	pre[u] = low[u] = ++dfn;
	for(road *p = h[u]; p; p = p->next)
	{
		int v = p->v;
		if(!pre[v])
		{
			dfs(v);
			low[u] = min(low[v], low[u]);
		}
		else if(!scc[v])
			low[u] = min(low[u], low[v]);
	}
	if(low[u] == pre[u])
	{
		scccnt++;
		while(true)
		{
			int tmp = q.top(); q.pop();
			scc[tmp] = scccnt;
			sccv[scccnt] += a[tmp];
			if(tmp == u) break;
		}
	}
}
void buildgraph()
{
	for(int i = 1; i <= n; i++)
		for(road *p = h[i]; p; p = p->next)
			if(scc[i] != scc[p->v])
				addedge2(scc[i], scc[p->v]);
}
int dfs2(int u)
{
	if(dp[u]) return dp[u];
	dp[u] = sccv[u];
	int maxv = 0;
	for(road *p = hnew[u]; p; p = p->next)
	{
		dfs2(p->v);
		if(dp[p->v] > maxv)
			maxv = dp[p->v];
	}
	dp[u] += maxv;
} 
int main()
{
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++)
	{
		scanf("%d %d", &x, &y);
		addedge(x, y);
	}
	for(int i = 1; i <= n; i++)       //缩点 
		if(!pre[i]) dfs(i);
	/*printf("scccnt:%d\n", scccnt);
	for(int i = 1; i <= n; i++)
		printf("i:%d pre[i]:%d low[i]:%d scc[i]:%d\n", i, pre[i], low[i], scc[i]);*/
	buildgraph();                     //建新图 
	for(int i = 1; i <= scccnt; i++)  //记忆化搜索求最长路 
		if(!dp[i]) dfs2(i);
	/*for(int i = 1; i <= scccnt; i++)
		printf("i:%d, dp[i]:%d\n", i, dp[i]);*/
	int ans = 0;
	for(int i = 1; i <= scccnt; i++)
		if(dp[i] > ans)
			ans = dp[i];
	printf("%d", ans);
	return 0;
}
