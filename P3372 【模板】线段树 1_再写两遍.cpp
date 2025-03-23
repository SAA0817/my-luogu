#include<cstdio>
#include<iostream>
#define MAXN 100005
#define LL long long
#define lc (num * 2)
#define rc ((num * 2) + 1)
#define mid ((l + r) / 2)

using namespace std;

LL n, m, sl, sr, k, ans;
struct Node{
	LL v;
	int len;
	LL lazy;
}t[MAXN * 3];

int read()
{
	bool flag = 0; int res = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-')
	{
		flag = 1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		res *= 10;
		res += c - '0';
		c = getchar();
	}
	if(flag) return -res;
	return res;
}

void pushup(int num)
{
	t[num].v = t[lc].v + t[rc].v;
}

void pushdown(int num)
{
	t[lc].v += (t[num].lazy * t[lc].len);
	t[rc].v += (t[num].lazy * t[rc].len);
	t[lc].lazy += t[num].lazy;
	t[rc].lazy += t[num].lazy;
	t[num].lazy = 0;
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
	pushup(num);
	t[num].len = t[lc].len + t[rc].len;
}

void add(int l, int r, int num)
{
	if(r < sl || l > sr) return;
	if(l >= sl && r <= sr)
	{
		t[num].lazy += k;
		t[num].v += k * t[num].len;
		return;
	}
	pushdown(num);
	add(l, mid, lc);
	add(mid+1, r, rc);
	pushup(num);
}

void query(int l, int r, int num)
{
	if(r < sl || l > sr) return;
	if(l >= sl && r <= sr)
	{
		ans += t[num].v;
		return;
	}
	pushdown(num);
	query(l, mid, lc);
	query(mid+1, r, rc);
}

int main()
{
	n = read(); m = read();
	buildtree(1, n, 1);
	while(m--)
	{
		int t = read();
		if(t == 1)
		{
			sl = read();
			sr = read();
			k = read();
			add(1, n, 1);
		}
		else
		{
			ans = 0;
			sl = read(); sr = read();
			query(1, n, 1);
			printf("%lld\n", ans);
		}
	}
	return 0;
}
