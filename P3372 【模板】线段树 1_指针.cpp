#include<cstdio>
#include<iostream>
#define LL long long
#define mid ((l + r) / 2)
#define MAXN 100005 

using namespace std;

LL n, m, sl, sr, k, ans, cnt;
struct Node{
	LL v;
	LL lazy;
	int len;
	Node *lc, *rc;
}pool[MAXN * 2], *root;

LL read()
{
    bool flag = 0; LL res = 0; char c = getchar();
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

void pushdown(Node *p)
{
	p->lc->v += (p->lazy) * p->lc->len;
	p->rc->v += (p->lazy) * p->rc->len;
	p->lc->lazy += p->lazy;
	p->rc->lazy += p->lazy;
	p->lazy = 0;
}

void pushup(Node *p)
{
	p->v = p->lc->v + p->rc->v;
}

Node* buildtree(int l, int r)
{
	Node *p = &pool[++cnt];
	if(l == r)
	{
		p->v = read();
		p->len = 1;
		return p;
	}
	p->lc = buildtree(l, mid);
	p->rc = buildtree(mid+1, r);
	pushup(p);
	p->len = p->rc->len + p->lc->len;
	return p;
}

void add(Node *p, int l, int r)
{
	//cout << l << " " << r << endl;
	if(r < sl || l > sr) return;
	if(l >= sl && r <= sr)
	{
		p->v += k * p->len;
		p->lazy += k;
		return;
	}
	pushdown(p);
	add(p->lc, l, mid);
	add(p->rc, mid+1, r);
	pushup(p);
}

void query(Node *p, int l, int r)
{
	if(r < sl || l > sr) return;
	if(l >= sl && r <= sr)
	{
		ans += p->v;
		return;
	}
	pushdown(p);
	query(p->lc, l, mid);
	query(p->rc, mid+1, r);
}

int main()
{
	n = read(); m = read();
	root = buildtree(1, n);
	while(m--)
	{
		int t = read();
		if(t == 1)
		{
			sl = read(); sr = read(); k = read();
			add(root, 1, n);
		}
		else
		{
			ans = 0;
			sl = read(); sr = read();
			query(root, 1, n);
			printf("%lld\n", ans);
		}
	}
	return 0;
}
