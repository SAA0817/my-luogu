#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long

using namespace std;

char c;
int x, y;
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

void exgcd(int a, int b)
{
	if(b == 0)
	{
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a%b);
	int t = x;
	x = y;
	y = t - a/b * y;
	return;
}

int main()
{
	int a, b;
	a = read(); b = read();
    exgcd(a, b);
    while(x < 0) x += b;
    //cout << b << endl;
    x %= b;
    printf("%d", x);
	return 0;
}
