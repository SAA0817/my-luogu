#include<cstdio>
#include<stack>
#define MAXN 10005
#define MAXM 100005
using namespace std;
int n, m, x, y, tot, scccnt, dfn, a[MAXN], pre[MAXN], low[MAXN], scc[MAXN];
int sccv[MAXN], inde[MAXN], dp[MAXN];
//sccv����洢ÿ���������Ȩֵ��inde�洢ÿ����������
//dp[i]��ʾ��״̬�����Ǵ�i������ܵõ������Ȩֵ��
//���仯��������д��dp[u] = sccv[u]+max(dp[v]), u->v��ͨ
//��������˳��ʵ�֣���ʱdp[i]��ʾ�ľ��ǵ���i���ܵõ������Ȩֵ��
//���ƶ�Դ�·spfa�㷨���Ȱ��������Ϊ��ĵ������
//Ȼ�����bfs������dpֵ��ע��������һ���Ż���ֻ�����Ϊ��Ľ�������
//��֤ÿ���ڵ�ֻ����һ�� 
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
	for(int i = 1; i <= n; i++)       //���� 
		if(!pre[i]) dfs(i);
	/*printf("scccnt:%d\n", scccnt);
	for(int i = 1; i <= n; i++)
		printf("i:%d pre[i]:%d low[i]:%d scc[i]:%d\n", i, pre[i], low[i], scc[i]);*/
	buildgraph();                     //����ͼ 
	for(int i = 1; i <= scccnt; i++)  //���仯�������· 
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
