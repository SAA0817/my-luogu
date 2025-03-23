#include<cstdio>
#include<iostream>
#define MAXN 100005 
#define MAXM 10000005
using namespace std;

struct Edge{
    int v;
    int dis;
    Edge *next;
}pool[MAXN << 1], *h[MAXN];

int n, m;
int size[MAXN]; //子树大小 
int maxsize[MAXN]; //最大子树大小 
int dis[MAXN]; //距离 
int query[MAXN]; //询问
int dis_q[MAXN];
int cnt, sum, root;
bool vis[MAXN], s[MAXN];
bool judge[MAXM];
char c;

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

void addEdge(int x, int y, int dis)
{
    Edge *p = &pool[++cnt];
    p->v = y;
    p->dis = dis;
    p->next = h[x];
    h[x] = p;
}

void getroot(int u, int fa)
{
    for(Edge *p = h[u]; p; p = p->next)
    {
        if(p->v == fa || vis[p->v]) continue;
        getroot(p->v, u);
        size[p->v] += p->dis;
        maxsize[u] = max(maxsize[u], size[p->v]);
        size[u] += size[p->v];
    }
    maxsize[u] = max(maxsize[u], sum - size[u]);
    if(maxsize[u] < maxsize[root])
        root = u;
}

void getdis(int u, int fa)
{
    dis_q[++cnt] = dis[u];
    for(Edge *p = h[u]; p; p = p->next)
    {
        if(p->v == fa || vis[p->v]) continue;
        dis[p->v] = dis[u] + p->dis;
        getdis(p->v, u);
    }
}


void calc(int u)
{
    int cnt_q = 0;
    int q[MAXN];
    for(Edge *p = h[u]; p; p = p->next)
    {
    	if(vis[p->v]) continue;
    	cnt = 0;//子树中dis的数量 
    	dis[p->v] = p->dis;
    	getdis(p->v, u);
    	for(int j = cnt; j; j--) //枚举当前子树中的dis 
    		for(int i = 1; i <= m; i++) //枚举询问 
    		    if(!s[i] && judge[query[i] - dis_q[j]]) 
    		    {
    		    	s[i] = 1; 
    		    	//cout << "solved:" << dis_q[j] << " q: " << query[i] << endl;
    		    }
    		    	
        for(int j = cnt; j; j--) //枚举当前子树中的dis 
        {
            q[++cnt_q] = dis_q[j]; //记录所有子树中的dis 
            judge[dis_q[j]] = 1;
        }
    }
    for(int i = 1; i <= cnt_q; i++)
    {
    	//cout << q[i] << " ";
    	judge[q[i]] = 0;
    }
}

void solve(int u)
{
    vis[u] = 1;
    judge[0] = 1;
    calc(u);
    for(Edge *p = h[u]; p; p = p->next)
    {
        if(vis[p->v]) continue;
        sum = size[p->v];
        root = 0;
        maxsize[root] = MAXM;
        getroot(p->v, u);
        solve(root);
    }
}

int main()
{
    n = read(); m = read();
    int u, v, dis;
    for(int i = 1; i < n; i++)
    {
    	u = read(); v = read(); dis = read();
    	addEdge(u, v, dis);
    	addEdge(v, u, dis);
    	sum += dis;
    }
    for(int i = 1; i <= m; i++)
        query[i] = read();
    root = 0;
    maxsize[root] = MAXM;
    getroot(1, -1);
    //cout << "root: " << root << endl;
    solve(root);
    
    for(int i = 1; i <= m; i++)
    {
        if(s[i]) printf("AYE\n");
        else printf("NAY\n");
    }
    return 0;
}
