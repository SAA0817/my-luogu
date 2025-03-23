#include<cstdio>
#include<iostream>
#define MAXN 1000005
#define mid ((r + l) / 2)

using namespace std;

int n, m;
int k, cnt;
struct Node{
	int v;
	int l, r;
	Node *lc, *rc;
}pool[MAXN*40], *root[MAXN];


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

Node *buildemptytree(int l, int r)
{
	Node *p = &pool[++cnt];
	p->l = l; p->r = r;
	if(l == r) 
	{
		p->v = read();
		return p;
	}
	p->lc = buildemptytree(l, mid);
	p->rc = buildemptytree(mid+1, r);
	return p;
}

Node *buildtree(Node *pre, int c)
{
	Node *p = &pool[++cnt];
	*p = *pre;
	if(p->l == p->r)
	{
		p->v = k;
		return p;
	}
	if(c <= p->lc->r) p->lc = buildtree(pre->lc, c);
	else p->rc = buildtree(pre->rc, c);
	return p;
}

int query(Node *p, int c)
{
	if(p->l == p->r) return p->v;
	if(c <= p->lc->r) return query(p->lc, c);
	return query(p->rc, c);
}

int main()
{
	n = read(); m = read();
	root[0] = buildemptytree(1, n);
	for(int i = 1; i <= m; i++)
	{
		int ver = read();
		int type = read();
		if(type == 1)
		{
			int loc = read(); k = read();
			root[i] = buildtree(root[ver], loc);
		}
		else
		{
			int loc = read();
			root[i] = root[ver];
			printf("%d\n", query(root[ver], loc));
		}
	}
	return 0;
}
