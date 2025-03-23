#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#include<algorithm>
#include<vector>
#define Pair pair<int, int> 
#define MP(x, y) make_pair(x, y)
#define fi first
#define se second
using namespace std;
const int MAXN = 1001;
const double eps = 1e-10, Dlt = 0.97, INF = 1e9 + 7;
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
int N, M;
struct Edge {
    int u, v, w;
    bool operator < (const Edge &rhs) const {
        return w < rhs.w;
    }
}E[MAXN];
int link[MAXN][MAXN], num, fa[MAXN];
void unionn(int x, int y) {
    fa[x] = y;
}
int find(int x) {
    if(fa[x] == x) return fa[x];
    else return fa[x] = find(fa[x]);
}
vector<Pair> v[MAXN];
int dfs(int x, int cnt, int fa) {
    int ans = 0;
    for(int i = 0; i < v[x].size(); i++) {
        int to = v[x][i].fi, w = v[x][i].se;
        if(to != fa) ans += dfs(to, cnt + 1, x) + w * cnt;
    }
    return ans;
}
int solve() {
    int cur = INF, tot = 0, base = 0;
    for(int i = 1; i <= N; i++) fa[i] = i, v[i].clear();
    for(int i = 1; i <= M; i++) {
        int x = E[i].u, y = E[i].v;
        int fx = find(x), fy = find(y);
        if(fx == fy) continue;
        tot++; unionn(fx, fy); 
        v[x].push_back(MP(y, E[i].w));
        v[y].push_back(MP(x, E[i].w));
    }
    if(tot != N - 1) return INF;
    for(int i = 1; i <= N; i++)
        cur = min(cur, dfs(i, 1, 0));
    return cur;
}
int main() {
//    freopen("testdata.in", "r", stdin);
    srand((unsigned)time(NULL));
    memset(link, 0x7f, sizeof(link));
    N = read(); M = read();
    if(N == 1) {
        puts("0"); return 0;
    }
    for(int i = 1; i <= M; i++) {
        int x = read(), y = read(), w = read();
        link[x][y] = min(link[x][y], w);
        link[y][x] = min(link[y][x], w);
    }
    for(int i = 1; i <= N; i++) 
        for(int j = i + 1; j <= N; j++) 
            if(link[i][j] <= INF) 
                E[++num] = (Edge) {i, j, link[i][j]};
    sort(E + 1, E + num + 1);
    int ans = solve();
    int times = 200;
    while(times--) {
        int now = INF;
        for(double T = 100000; T > eps; T *= Dlt) {
            int x = rand() % num + 1, y = rand() % num + 1;
            //check(x, y);
            swap(E[x], E[y]);
            int nxt = solve();
            if(nxt < ans) {ans = nxt; continue;}
            if(nxt < now || ((exp(now - nxt / T) < rand() / RAND_MAX))) {now = nxt; continue;}
            swap(E[x], E[y]);
        }
    }
    printf("%d", ans);
    return 0;
}
/*
0 0
5000
10000
0
*/
