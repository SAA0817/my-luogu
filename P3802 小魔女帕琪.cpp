#include<cstdio>
#include<iostream>
#define LL long long

using namespace std;

double a[10], n;
double ans;

int main()
{
	for(int i = 1; i <= 7; i++)
	{
		cin >> a[i];
		n += a[i];
	}
	   
	printf("%.3lf", 5040*(a[1]*a[2]*a[3]*a[4]*a[5]*a[6]*a[7])/ (n * (n-1) * (n-2) * (n-3) * (n-4) * (n-5)));
	return 0;
}
