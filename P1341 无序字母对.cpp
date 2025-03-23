#include<cstdio>
#include<iostream>
#include<algorithm>
#define MAXN 200

using namespace std;

int n;
char c;
int a[MAXN][MAXN];
int _cnt[MAXN];
int cnt = 0;
bool flag;int now = 200;
char ans[26 * 26 + 1];

int read()
{
    c = getchar();
    while(c < 'A' || c > 'z') c = getchar();
    return int(c);
}

void dfs(int num)
{
	for(int i = 'A'; i <= 'z'; i++)
	    if(a[num][i])
	    {
    		a[num][i]--; 
            a[i][num]--;
	    	dfs(i);
		}
	ans[n--] = num;
}
int main()
{
    cin >> n;
    int N = n;
    int x, y;
    for(int i = 1; i <= n; i++)
    {
        x = read(); y = read();
        a[x][y]++; a[y][x]++;
        now = min(now, x); now = min(now, y);
        _cnt[x]++; _cnt[y]++;
    }
    for(int i = 'A'; i <= 'z'; i++)
        if(_cnt[i] % 2 != 0)
        {
        	if(cnt == 0) now = i;
        	cnt++;
        }
    if(cnt != 0 && cnt != 2)
    {
    	printf("No Solution");
    	return 0;
	}
    dfs(now);
    for(int i = 0; i <= N; i++)
        cout << ans[i];
    return 0;
}

//iMDIGFBHGNCZAJQDUBOHIMHQEfNLZGRHZIPQMRNVAKxDcFeHbCpGUQOeMcIVBSJVPRkFgAqHjJWwJXVUYuEyIpHuJaZVpNdGgOfPTcJbLhNmMjPchUmPgSmeakhZdXijcvIqQbrDowQsXnqVuRrJxLyMvZpdvnxrUtRwXzTyStarejgujpimruplksjzqtkyuzvyxxtps
//iMDIGFBHGNCZAJQDUBOHIMHQEfNLZGRHZIPQMRNVAKxDcFeHbCpGUQOeMcIVBSJVPRkFgAqHjJWwJXVUYuEyIpHuJaZVpNdGgOfPTcJbLhNmMjPchUmPgSmeakhZdXijcvIqQbrDowQsXnqVuRrJxLyMvZpdvnxrUtRwXzTyStarejgujpimruplksjzqtkyuzvyxtps


/*
#include<cstdio>
#include<iostream>
#include<algorithm>
#define MAXN 200

using namespace std;

int n;
char c;
int a[MAXN][MAXN];
int _cnt[MAXN];
int cnt = 1;
bool flag;
char ans[26 * 26 + 1];

int read()
{
    c = getchar();
    while(c < 'A' || c > 'z') c = getchar();
    return int(c);
}

int main()
{
	cin >> n;
    int x, y;
    int now = 200;
	for(int i = 1; i <= n; i++)
	{
		x = read(); y = read();
		a[x][y]++; a[y][x]++;
		//now = min(now, x); now = min(now, y);
		//_cnt[x]++; _cnt[y]++;
	}
//	for(int i = 'A'; i <= 'Z'; i++)
//	    if(_cnt[i] % 2 != 0)
//	    {
//	    	now = i;
//	    	//cout << (char)now << " " << _cnt[i] << endl;
//	    	break;
//		}
//	ans[0] = (char)now;
//	//cout << (char)now;
	for(now = 'A'; now <= 'z'; now++)
	{
		ans[0] = (char)now;
		while(cnt <= n)
		{
			flag = 0;
			for(int i = 'A'; i <= 'z'; i++)
			{
				if(a[now][i])
				{
					a[now][i]--;// cout << now << " " << i << " " << a[now][i];
					a[i][now]--;// cout << now << " " << i << " " << a[now][i];
					//cout << (char)i << " ";
					ans[cnt] = (char)i;
					now = i;
					cnt++;
					flag = 1;
					break;
				}
			}
			if(!flag) break;
		}
		if(flag)
		{
			for(int i = 0; i <= n; i++)
	    		cout << ans[i];
	    	return 0;
		}
		
	}
	
	for(int i = 0; i <= n; i++)
	    cout << ans[i];
	return 0;
}


// IcCvXggwPpl
/*
10
Ic
Pw
Cv
pP
Xg
pl
cC
gg
gw
Xv
*/

