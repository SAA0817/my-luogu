#include<iostream>
#include<algorithm>
#include<bitset>
#include<cstring>
#include<vector>
#include<map>
#include<queue>

#define endl '\n'

using namespace std;
using LL = long long;

const int MAXN = 1e5+5;
const int MAXM = 7e6+5;

LL n, m, q, u, v, t;

priority_queue<LL> q1;
queue<LL> q2, q3;

LL cnt2, cnt3;
LL a, b, c;



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> q >> u >> v >> t;

    for(int i = 1; i <= n; i++)
    {
        int num;
        cin >> num;
        q1.push(num);
    }

    for(int i = 1; i <= m; i++)
    {
        a = 0; b = 0; c = 0;

        if(!q1.empty())
        {
            a = q1.top();
            a += (i-1) * q;
        }
            
        if(!q2.empty())
        {
            b = q2.front();
            b += (cnt2 - 1) * q;
        }

        if(!q3.empty())
        {
            c = q3.front();
            c += (cnt3 - 1) * q;
        }

        if(a >= b && a >= c)
            q1.pop();
        else if(b >= a && b >= c)
        {
            q2.pop();
            cnt2--;
        }
        else
        {
            q3.pop();
            cnt3--;
        }

        cnt2++; cnt3++;
        LL tmp = max(a, max(b, c));
        q2.push(tmp * u / v);
        q3.push(tmp - tmp * u / v);

        if(i % t == 0) cout << tmp << " ";
    }

    cout << endl;

    for(int i = 1; i <= n+m; i++)
    {
        a = 0; b = 0; c = 0;

        if(!q1.empty())
        {
            a = q1.top();
            a += m * q;
        }
            
        if(!q2.empty())
        {
            b = q2.front();
            b += (cnt2 - 1) * q;
        }

        if(!q3.empty())
        {
            c = q3.front();
            c += (cnt3 - 1) * q;
        }

        if(a >= b && a >= c)
            q1.pop();
        else if(b >= a && b >= c)
        {
            q2.pop();
            cnt2--;
        }
        else
        {
            q3.pop();
            cnt3--;
        }

        // cnt2++; cnt3++;

        LL tmp = max(a, max(b, c));
        if(i % t == 0) cout << tmp << " ";

    }

    

    return 0;
}