#include<cstdio>
#include<algorithm>
#define MAXN 200005
#define MAXM 200005
using namespace std;
int n, m, x, y, k, tot, rank[MAXN];
struct node{
	int x, id;
	bool operator < (const node &tmp) const
	{return x < tmp.x;}
}a[MAXN];
struct tree{
	int v;
	tree *lson, *rson;
}*root[MAXM], pool[MAXM*40]; //小心数组开小 
tree *buildtree(int l, int r)
{
	tree *now = &pool[tot++];
	//now->l = l; now->r = r;
	if(l == r) return now;
	int m = (l+r)>>1;
	now->lson = buildtree(l, m);
	now->rson = buildtree(m+1, r);
	return now;
}
tree *insert(tree *old, int u, int l, int r)
{
	tree *now = &pool[tot++];
	//now->l = l; now->r = r;
	if(l == r)
	{
		now->v = 1;
		return now;
	}
	int m = (l + r) >> 1;
	now->lson = u <= m ? insert(old->lson, u, l, m) : old->lson;
	now->rson = u <= m ? old->rson : insert(old->rson, u, m+1, r);
	now->v = now->lson->v + now->rson->v;
	return now;
}
int ask(tree *left, tree *right, int k, int l, int r)
{
	if(l == r) return a[l].x;
	int m = (l + r) >> 1, tmp = right->lson->v - left->lson->v;
	if(tmp >= k)
		return ask(left->lson, right->lson, k, l, m);
	else
		return ask(left->rson, right->rson, k - tmp, m+1, r);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i].x), a[i].id = i;
	sort(a+1, a+n+1);
	for(int i = 1; i <= n; i++)
		rank[a[i].id] = i;
	root[0] = buildtree(1, n);
	for(int i = 1; i <= n; i++)
		root[i] = insert(root[i-1], rank[i], 1, n);
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &x, &y, &k);
		printf("%d\n", ask(root[x-1], root[y], k, 1, n));
	}
	return 0;
}
