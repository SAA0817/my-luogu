#include<cstdio>
#include<iostream>
#define LL long long
#define MAXN 100005
#define lc (num * 2)
#define rc (num * 2 + 1)
#define mid ((l + r) / 2)

using namespace std;

LL n, m, sl, sr, k, ans;
struct Node{
	LL v, lazy;
	LL len;
}t[MAXN * 4];
char c;

LL read()
{
	LL res = 0;
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
	if(r < sl || l > sr) return;
	pushdown(num);
	if(l >= sl && r <= sr)
	{
		t[num].v += t[num].len * k;
		t[num].lazy += k;
		return;
	}
	add(l, mid, lc);
	add(mid+1, r, rc);
	t[num].v = t[lc].v + t[rc].v;
}

void query(int l, int r, int num)
{
	if(r < sl || l > sr) return;
	if(l >= sl && r <= sr)
	{
		//cout << "s:"  << r << " " << l << " " << t[num].v << endl;
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
	int q;
	for(int i = 1; i <= m; i++)
	{
		q = read();
		if(q == 1)
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
