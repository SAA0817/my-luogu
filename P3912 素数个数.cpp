#include<cstdio>
#include<iostream>
#define MAXN 100000005

using namespace std;

bool vis[MAXN];
int ans;
int main()
{
	int n;
	cin >> n;
	ans = n - 1;
	for(int i = 2; i*i <= n; i++)
	{
		if(!vis[i])
		{
			vis[i] = 1;
			for(int j = i * 2; j <= n; j += i)
			{
				if(!vis[j]) ans--;
				vis[j] = 1;
			}
		}
	}
	cout << ans;
	return 0;
}
