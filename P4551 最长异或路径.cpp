#include<iostream>
#include<algorithm>
#include<bitset>
#include<cstring>
#include<vector>

#define endl '\n'

using namespace std;
using LL = long long;

const int MAXN = 1e5+5;

int n;
int tot;
int ans;
int a[MAXN];

struct Edge{
    int v, w;
    Edge *next;
}pool[MAXN * 2], *h[MAXN];

struct trie{
    int ch[2];
}t[MAXN * 32];

void insert(int num)
{
    int p = 0;
    for(int i = 31; i >= 0; i--)
    {
        int x = (num >> i) & 1;
        if(!t[p].ch[x])
            t[p].ch[x] = ++tot;
        p = t[p].ch[x];
    }
}

void addEdge(int x, int y, int w)
{
    static int cnt = 0; 
    Edge *p = &pool[++cnt];
    p->v = y;
    p->w = w;
    p->next = h[x];
    h[x] = p;
}

void dfs(int num, int fa)
{
    for(Edge *p = h[num]; p; p = p->next)
    {
        if(p->v == fa)
            continue;
        a[p->v] = a[num] ^ p->w;
        //cout << a[num] << " " << (a[num] ^ p->w) << endl;
        insert(a[p->v]); 
        dfs(p->v, num);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    for(int i = 1; i <= n-1; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    dfs(1, 0);

    // for(int i = 1; i <= 3; i++) cout << a[i] << " ";

    for(int i = 1; i <= n; i++)
    {
        int p = 0;
        int num = 0;
        for(int j = 31; j >= 0; j--)
        {
            int x = (a[i] >> j) & 1;
            if(t[p].ch[x^1])
            {
                num += (1 << j);
                p = t[p].ch[x^1];
            }
            else
                p = t[p].ch[x];
        }
        ans = max(ans, num);
    }

    cout << ans << endl;

    return 0;
}