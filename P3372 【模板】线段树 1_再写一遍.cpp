#include<cstdio>
#include<iostream>
#define mid ((l + r) / 2)
#define lc (num * 2)
#define rc (num * 2 + 1)
#define MAXN 100005 
#define LL long long

using namespace std;

LL n, m, sl, sr, k, ans;
char c;

struct Node{
	LL v;
	LL lazy;
	int len;
}t[MAXN * 3];

int read()
{
	int res = 0;
	c = getchar();
	while(c < '0' || c > '9') c = getchar();
	while(c >= '0' && c <= '9')
	{
		res *= 10;
		res += c - '0';
		c = getchar();
	}
	return res;
}

void buildtree(int l, int r, int num)
{
	if(l == r)
	{
		t[num].v = read();
		t[num].len = 1;
		return;
	}
	buildtree(l, mid, lc);
	buildtree(mid+1, r, rc);
	t[num].v = t[lc].v + t[rc].v;
	t[num].len = t[lc].len + t[rc].len;
}

void pushup(int num)
{
	t[num].v = t[lc].v + t[rc].v;
}

void pushdown(int num)
{
	t[lc].v += t[num].lazy * t[lc].len;
	t[rc].v += t[num].lazy * t[rc].len;
	t[lc].lazy += t[num].lazy;
	t[rc].lazy += t[num].lazy;
	t[num].lazy = 0;
}

void add(int l, int r, int num)
{
	if(l > sr || r < sl) return;
	if(l >= sl && r <= sr)
	{
		t[num].v += k * t[num].len;
		t[num].lazy += k;
		return;
	}
	pushdown(num);
	add(l, mid, lc);
	add(mid+1, r, rc);
	pushup(num);
}

void query(int l, int r, int num)
{
	if(l > sr || r < sl) return;
	if(l >= sl && r <= sr)
	{
		ans += t[num].v;
		return;
	}
	pushdown(num);
	query(l, mid, lc);
	query(mid+1, r, rc);
	//pushup(num);
}

int main()
{
	n = read(); m = read();
	buildtree(1, n, 1);
	for(int i = 1; i <= m; i++)
	{
		int t = read();
		if(t == 1)
		{
			sl = read(); sr = read(); k = read();
			add(1, n, 1);
		}
		else
		{
			sl = read(); sr = read();
			ans = 0;
			query(1, n, 1);
			cout << ans << endl;
		}
	}
	
	return 0;
} 
