#include<cstdio>
#include<iostream>
#define LL long long
#define MAXN 200005
#define lc (num * 2)
#define rc (num * 2 + 1)
#define mid ((l + r) / 2)

using namespace std;

int n, m;
int sl, sr, k;
LL ans;
struct Node{
	LL lazy;
	LL v;
	int len;
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

void pushdown(int num)
{
	t[lc].v += t[num].lazy * t[lc].len;
	t[rc].v += t[num].lazy * t[rc].len;
	t[lc].lazy += t[num].lazy;
	t[rc].lazy += t[num].lazy;
	t[num].lazy = 0;
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
	n = read(); m = read();
	buildtree(1, 1, n);
	while(m--)
	{
		int type = read();
		if(type == 1)
		{
			sl = read(); sr = read(); k = read();
			add(1, 1, n);
			continue;
		}
		if(type == 2 || type == 3)
		{
			k = read(); sl = 1; sr = 1;
			if(type == 3) k = -k;
			add(1, 1, n);
		}
		if(type == 4 || type == 5)
		{
			ans = 0;
			if(type == 5) sl = sr = 1; 
			else
			{
				sl = read();
				sr = read();
			}
			query(1, 1, n);
			printf("%lld\n", ans); 
		}
	}
	return 0;
}
