#include<cstdio>
#include<iostream>
#include<algorithm>
#define MAXN 200005
#define mid ((l + r) / 2)

using namespace std;

int n, m, rank[MAXN], v[MAXN], p[MAXN];
int cnt;
struct Node{
	int v;
	int l, r;
	Node *lc, *rc;
}pool[MAXN * 40], *root[MAXN];

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
	if(l == r) return p;
	p->lc = buildemptytree(l, mid);
	p->rc = buildemptytree(mid+1, r);
	return p;
}

Node* buildtree(Node *pre, int c)
{
    Node *p = &pool[++cnt];
    *p = *pre;
    p->v++;
    if(p->l == p->r) return p;
    if(c <= p->lc->r) p->lc = buildtree(p->lc, c);
    else p->rc = buildtree(p->rc, c);
    return p;
}

int query(Node *a, Node *b, int k)
{
	if(a->l == a->r) return a->l;
	int tmp = b->lc->v - a->lc->v;
	if(tmp >= k) return query(a->lc, b->lc, k);
	return query(a->rc, b->rc, k - tmp);
}

bool cmp(int a, int b)
{
	return v[a] < v[b];
}

void pr(Node *rt)
{
	printf("[l:%d, r:%d] val:%d\n", rt->l, rt->r, rt->v);
	if(rt->l == rt->r) return ;
	pr(rt->lc);
	pr(rt->rc);
}

int main()
{
	n = read();
	for(int i = 1; i <= n; i++)
	{
		v[i] = read();
		p[i] = i;
	}
	sort(p+1, p+n+1, cmp);//p[i]表示排名为i的人所在位置 
	for(int i = 1; i <= n; i++)
	    rank[p[i]] = i; //rank记录离散化后的v
	m = read();
//	for(int i = 1; i <= n; i++)
//	    cout << rank[i] << " ";
//	return 0;
//	cout << endl;

	root[0] = buildemptytree(1, n);
	for(int i = 1; i <= n; i++)
	{
		root[i] = buildtree(root[i-1], rank[i]);
		//pr(root[i]); cout << endl;
	}
	int x, y, k;
	while(m--)
	{
		x = read(); y = read(); k = read();
		printf("%d\n", v[p[query(root[x-1], root[y], k)]]); //x-1!!!!!!!
	}	 
	return 0;
}
