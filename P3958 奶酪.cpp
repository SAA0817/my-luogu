#include<cstdio>
#include<iostream>
#define MAXN 1005
#define LL long long

using namespace std;

LL n, h, r;
LL sr;
int f[MAXN];
struct Hole{
	LL x, y, z;
	bool up, low;
}a[MAXN];

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

int getf(int num)
{
	if(f[num] == num) return num;
	return f[num] = getf(f[num]);
}

bool check(Hole a, Hole b)
{
	LL x = a.x - b.x; x *= x;
	LL y = a.y - b.y; y *= y;
	LL z = a.z - b.z; z *= z;
	
	if(x + y + z <= sr) return true;
	return false;
}

int main()
{
	int T = read();
	while(T--)
	{
		
		n = read(); h = read(); r = read();
		sr = r * r * 4;
		for(int i = 1; i <= n; i++)
		    f[i] = i;
		for(int i = 1; i <= n; i++)
		{
			a[i].x = read();
			a[i].y = read();
			a[i].z = read();
			a[i].low = 0; a[i].up = 0;
			if(a[i].z <= r) a[i].low = 1;
			if(a[i].z >= h - r) a[i].up = 1;
			//cout << a[i].low << " " << a[i].up << endl;
			for(int j = 1; j < i; j++)
			{
				if(getf(i) == getf(j))
				    continue;
				if(check(a[i], a[j]))
				{
					int x = getf(i), y = getf(j);
					a[y].low = a[x].low | a[y].low;
					a[y].up = a[x].up | a[y].up;
					f[x] = y;
				}
			}
		}
		for(int i = 1; i <= n; i++)
		{
			if(a[i].low && a[i].up)
		    {
		        printf("Yes\n");
		        break;
		    }
		    if(i == n)
		        printf("No\n");
		}
		    
	}
	return 0;
}
