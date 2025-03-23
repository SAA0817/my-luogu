#include<iostream>
#include<algorithm>
#include<bitset>
#include<cstring>
#include<vector>
#include<map>

#define endl '\n'

using namespace std;
using LL = long long;

const int MAXN = 15;

LL dp[MAXN][1 << MAXN][MAXN * MAXN];
bool l[1 << MAXN];
int n, maxk;
LL ans;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> maxk;

    for(int i = 0; i < (1 << n); i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i & (1 << j))
                if(j != 0 && (i & (1 << (j-1))))
                    break;
            if(j == n-1)
            {
                l[i] = 1;
                dp[1][i][__builtin_popcount(i)] = 1;
            }
        }    
    }

    for(int s = 2; s <= n; s++)
    {
        for(int i = 0; i < (1 << n); i++)
        {
            if(!l[i]) continue;
            for(int j = 0; j < (1 << n); j++)
            {
                if(!l[j]) continue;
                for(int k = 0; k < n; k++)
                {
                    if(i & (1 << k))
                    {
                        if(j & (1 << k))
                            break;
                        if(j & (1 << (k-1)))
                            break;
                        if(k != n-1 && j & (1 << (k+1)))
                            break;
                    }
                    if(k == n-1)
                        for(int t = __builtin_popcount(i); t <= min(maxk, k * s); t++)
                            dp[s][i][t] += dp[s-1][j][t-__builtin_popcount(i)];
                }
                
            }
        }
    }
    
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j < (1 << n); j++)
        {
            // cout << dp[i][j][maxk] << " ";
            ans += dp[i][j][maxk];
        }
        // cout << endl;
    }
        

    cout << ans << endl;

    
    return 0;
}