#include<cstdio>
#include<iostream>
#define MAXN 1000005
#define mid ((l + r) / 2)

using namespace std;

int n, m, cnt, k, d;
struct Node{
	Node *lc, *rc;
	int v;
}t[MAXN*30], *root[MAXN];

int read()
{
	char c = getchar();
	int res = 0;
	while(c < '0' || c > '9') c = getchar();
	while(c >= '0' && c <= '9')
	{
		res *= 10;
		res += c - '0';
		c = getchar();
	}
	return res;
}

Node *buildtree(int l, int r)
{
	Node *p = &t[++cnt];
	if(l == r)
	{
		p->v = read();
		return p;
	}
	p->lc = buildtree(l, mid);
	p->rc = buildtree(mid+1, r);
	return p;
}

Node *add(Node *now, int l, int r)
{
	Node *p = &t[++cnt];
	if(l == r)
	{
		p->v = d;
		return p;
	}
	if(k <= mid)
	{
		p->lc = add(now->lc, l, mid);
		p->rc = now->rc;
	}
	else
	{
		p->lc = now->lc;
		p->rc = add(now->rc, mid+1, r);
	}
	return p;
}

int query(Node *now, int l, int r)
{
	if(l == r) return now->v;
	if(k <= mid) return query(now->lc, l, mid);
	return query(now->rc, mid+1, r);
}

int main()
{
	n = read(); m = read();
	root[0] = buildtree(1, n);
	for(int i = 1; i <= m; i++)
	{
		int ver = read();
		int t = read();
		if(t == 1)
		{
			k = read(); d = read();
			root[i] = add(root[ver], 1, n);
			//cout << "S";
		}
		if(t == 2)
		{
			k = read();
			root[i] = root[ver];
			printf("%d\n", query(root[i], 1, n));
		}
	}
	return 0;
}
