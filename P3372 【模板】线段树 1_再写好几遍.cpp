#include<cstdio>
#include<iostream>
#define lc (num * 2)
#define rc (num * 2 + 1)
#define mid ((l + r) / 2)
#define LL long long
#define MAXN 1000005 

using namespace std;

int n;
int sl, sr, k;
LL ans;
struct Node{
	LL lazy;
	LL v;
	int len;
}t[MAXN * 3];

LL read()
{
	LL res = 0;
	char c = getchar();
	while(c < '0' || c > '9') c = getchar();
	while(c >= '0' && c <= '9')
	{
		res *= 10;
		res += c - '0';
		c = getchar();
	}
	return res;
}

inline void pushup(int num)
{
	t[num].v = t[rc].v + t[lc].v;
}

void pushdown(int num)
{
	t[lc].v += t[lc].len * t[num].lazy;
	t[rc].v += t[rc].len * t[num].lazy;
	t[lc].lazy += t[num].lazy;
	t[rc].lazy += t[num].lazy;
	t[num].lazy = 0;
}

void buildtree(int num, int l, int r)
{
	if(l == r)
	{
		t[num].v = read();
		t[num].len = 1;
		return;
	}
	buildtree(lc, l, mid);
	buildtree(rc, mid+1, r);
	pushup(num);
	t[num].len = t[lc].len + t[rc].len;
}

void add(int num, int l, int r)
{
	if(r < sl || l > sr) return;
	if(l >= sl && r <= sr)
	{
		t[num].v += t[num].len * k;
		t[num].lazy += k;
		return;
	}
	pushdown(num);
	add(lc, l, mid);
	add(rc, mid+1, r);
	pushup(num);
}

void query(int num, int l, int r)
{
	if(r < sl || l > sr) return;
	if(l >= sl && r <= sr)
	{
		ans += t[num].v;
		return;
	}
	pushdown(num);
	query(lc, l, mid);
	query(rc, mid+1, r);
}

int main()
{
	n = read();
	int T = read();
	buildtree(1, 1, n);
	
	while(T--)
	{
		int type = read();
		if(type == 1)
		{
			sl = read(); sr = read(); k = read();
			add(1, 1, n);
		}
		else
		{
			ans = 0;
			sl = read(); sr = read();
			query(1, 1, n);
			printf("%lld\n", ans);
		}
	}
	return 0;
}
