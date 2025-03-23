#include<cstdio>
#include<iostream>
#define MAXN 100005
#define mid ((l + r) >> 1)

using namespace std;

int n, m, cnt;
struct Node{
	int f, d;
	Node *lc, *rc;
}pool[MAXN * 30], *root[MAXN * 2];
int f[MAXN * 30];
int d[MAXN * 3];
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

Node *buildtree(int l, int r)
{
	Node *p = &pool[++cnt];
	if(l == r)
	{
		p->f = l;
		//p->d = 0;
		return p;
	}
	p->lc = buildtree(l, mid);
	p->rc = buildtree(mid+1, r);
	return p;
}

Node *changefa(Node *pre, int x, int f, int l, int r)
{
	Node *p = &pool[++cnt];
	*p = *pre;
	if(l == r) 
	{
		p->f = f;
		return p;
	}
	if(x <= mid) p->lc = changefa(p->lc, x, f, l, mid);
	else p->rc = changefa(p->rc, x, f, mid+1, r);
	return p;
}

int getnodef(Node *p, int num, int l, int r)
{
	if(l == r) return p->f;
	if(mid >= num) return getnodef(p->lc, num, l, mid);
	return getnodef(p->rc, num, mid+1, r);
}

int getnode_d(Node *p, int num, int l, int r)
{
	if(l == r) return p->d;
	if(mid >= num) return getnode_d(p->lc, num, l, mid);
	return getnode_d(p->rc, num, mid+1, r);
}

void add_d(Node *p, int num, int l, int r)
{
	if(l == r)
	{
		p->d += 1;
		return;
	}
	if(mid >= num)
	{
		add_d(p->lc, num, l, mid);
		return;
	}
	add_d(p->rc, num, mid+1, r);
	return;
}

int getf(Node *root, int num)
{
	int fa = getnodef(root, num, 1, n);
	//cout << fa << " " << num << endl;
	if(fa == num) return num;
	return getf(root, fa);
	//changefa(root, fa, t);
}

int query(Node *root, int a, int b)
{
	if(getf(root, a) == getf(root, b)) return 1;
	return 0;
}

int main() 
{
    n = read(); m = read();
    root[0] = buildtree(1, n);
    for(int i = 1; i <= m; i++)
    {
    	int type = read();
    	if(type == 1)
    	{
    		int x = read();
    		int y = read();
    		int dx = getnode_d(root[i-1], x, 1, n);
    		int dy = getnode_d(root[i-1], y, 1, n);
    		
    		if(dx <= dy)  root[i] = changefa(root[i-1], x, y, 1, n);
    		else  root[i] = changefa(root[i-1], y, x, 1, n);
    		if(dx == dy)  add_d(root[i], y, 1, n);
		}
		if(type == 2)
		{
			int ver = read();
			root[i] = root[ver];
		}
		if(type == 3)
		{
			int a = read();
			int b = read();
			root[i] = root[i-1];
			printf("%d\n", query(root[i], a, b));
		}
	}
	return 0;
}
