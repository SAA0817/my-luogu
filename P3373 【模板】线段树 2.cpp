#include<cstdio>
#include<iostream>
#define MAXN 100005
#define LL long long
#define lc (num * 2)
#define rc (num * 2 + 1)
#define mid ((l + r) / 2)

using namespace std;

int n, m, mod;
int x, y, k, ans;
char c;
struct Node{
	LL v;
	LL lazy;
	LL mul;
	LL len;
}t[MAXN << 1];

int read()
{
	int res = 0;
	while(c < '0' || c > '9')  c = getchar();
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
	t[num].mul = 1;
	if(l == r)
	{
		t[num].v = read();
		t[num].len = 1;
		return;
	}
	buildtree(l, mid, lc);
	buildtree(mid+1, r, rc);
	t[num].v = (t[lc].v + t[rc].v) % mod;
	t[num].len = t[lc].len + t[rc].len;
}

//ÏÈ³Ë ºó¼Ó

void clear(int num)
{
	t[num].v = (t[num].v * t[num].mul) % mod; t[num].mul = 1;
	t[num].v = (t[num].v + (t[num].lazy * t[num].len) % mod) % mod; t[num].lazy = 0;
}

void prtree(int l, int r, int num)
{
	cout << "l:" << l << " r:" << r << " v:" << t[num].v 
	<< " lazy:" << t[num].lazy << " mul:" << t[num].mul << endl;
	if(l == r) return;
	prtree(l, mid, lc);
	prtree(mid+1, r, rc);
}

//void falazy(int num)
//{
//	LL lazy = t[num].lazy; LL mul = t[num].mul;
//	clear(num); clear(lc); clear(rc);
//	t[lc].mul = (mul * t[lc].mul) % mod;
//	t[rc].mul = (mul * t[rc].mul) % mod;
//	t[lc].lazy = (lazy + t[lc].lazy) % mod;
//	t[rc].lazy = (lazy + t[rc].lazy) % mod;
//}

void pushdown(int num)
{
	t[lc].v = (t[lc].v * t[num].mul) % mod;
	t[rc].v = (t[rc].v * t[num].mul) % mod;
	t[lc].v = (t[lc].v + (t[num].lazy * t[lc].len)) % mod;
	t[rc].v = (t[rc].v + (t[num].lazy * t[rc].len)) % mod;
	t[lc].mul = (t[num].mul * t[lc].mul) % mod;
	t[rc].mul = (t[num].mul * t[rc].mul) % mod;
	t[lc].lazy = (t[num].lazy + ((t[num].mul * t[lc].lazy) % mod)) % mod;
	t[rc].lazy = (t[num].lazy + ((t[num].mul * t[rc].lazy) % mod)) % mod;
	t[num].mul = 1; t[num].lazy = 0;
}

void multi(int l, int r, int num)
{
	if(r < x || l > y) return;
	if(l >= x && r <= y)
	{
		t[num].v = (t[num].v * k) % mod;
		t[num].lazy = (t[num].lazy * k) % mod;
		t[num].mul = (t[num].mul * k) % mod;
		return;
	}
	pushdown(num);
	multi(l, mid, lc);
	multi(mid+1, r, rc);
	t[num].v = (t[lc].v + t[rc].v) % mod;
}

void add(int l, int r, int num)
{
	//l = 1 r = 5 x = 1 y = 4
	if(r < x || l > y) return;
	if(l >= x && r <= y)
	{
		t[num].lazy = (t[num].lazy + k) % mod;
		t[num].v = (t[num].v + (t[num].len * k) % mod) % mod;
		return;
	}
	pushdown(num);
	add(l, mid, lc);
	add(mid+1, r, rc);
	t[num].v = (t[lc].v + t[rc].v) % mod;
}

void check(int l, int r, int num)
{
	if(r < x || l > y) return;
	//falazy(num);
	
	if(l >= x && r <= y)
	{
		ans = (ans + t[num].v) % mod;
		//cout << "ANS:" << l << " " << r << " " << ans << endl;
		//prtree(1, n, 1);
		return;
	}
	pushdown(num);
	check(l, mid, lc);
	check(mid+1, r, rc);
}


int main()
{
	n = read(); m = read(); mod = read();
	buildtree(1, n, 1);
	
	for(int i = 1; i <= m; i++)
	{
		//prtree(1, n, 1);
		int t = read();
		if(t == 1)
		{
			x = read(); y = read(); k = read();
			multi(1, n, 1);
		}
		if(t == 2)
		{
			x = read(); y = read(); k = read();
			add(1, n, 1);
		}
		if(t == 3)
		{
			ans = 0;
			x = read(); y = read();
			check(1, n, 1);
			printf("%d\n", ans);
		}
	}
	return 0;
}
