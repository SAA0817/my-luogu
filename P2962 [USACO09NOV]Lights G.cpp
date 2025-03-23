#include<iostream>
#include<algorithm>
#include<bitset>
#include<cstring>
#include<vector>
#include<map>

#define endl '\n'

using namespace std;
using LL = long long;

const int MAXN = 40;

int n, m;
LL e[MAXN];
int ans = 0x3f3f3f3f;
map<LL, int> mp;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for(int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        e[u] |= (1LL << (v-1));
        e[v] |= (1LL << (u-1));
    }

    for(int i = 1; i <= n; i++)
        e[i] |= (1LL << (i-1));

    // for(int i = 1; i <= n; i++)
    //     cout << i << " :" <<  bitset<10>(e[i]) << endl;

    for(int i = 0; i < (1 << (n/2)) ; i++)
    {
        LL t = 0;
        int cnt = 0;
        for(int j = 1; j <= n/2; j++)
            if(i & (1 << (j-1)))
            {
                t ^= e[j];
                cnt++;
            }
        // cout << bitset<10>(t) << endl;
        // if(i < 10) cout << bitset<40>(t) << endl;
        if(!mp.count(t)) mp[t] = cnt;
        else mp[t] = min(mp[t], cnt);
    }

    for(int i = 0; i < (1 << (n - n/2)); i++)
    {
        LL t = 0;
        int cnt = 0;
        for(int j = 1; j <= n - n/2; j++)
            if(i & (1 << (j-1)))
            {
                t ^= e[j + n/2];
                cnt++;
            }
        // cout << bitset<10>(t) << endl;
        t = t ^ ((1LL << n) - 1);
        // if(i < 10) cout << bitset<40>(t) << endl;
        if(mp.count(t)) 
        {
            ans = min(ans, cnt + mp[t]);
        }
    }

    if(ans == 0x3f3f3f3f) cout << -1 << endl;
    else cout << ans << endl;
    
    return 0;
}