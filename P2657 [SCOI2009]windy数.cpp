#include<cstdio>
#include<iostream>
#define LL long long

using namespace std;

int a, b;
int lena, lenb;
int dp[15][15];//dp[i][j] 表示i位，且第i位是j 
int mod;
int ans;
bool flag1, flag2;

void init()
{
	for(int j = 0; j <= 10; j++)
	    dp[1][j] = 1;
	for(int i = 2; i <= 10; i++)
	    for(int j = 0; j <= 9; j++)
	    {
	    	for(int k = 0; k <= 9; k++)
	    	{
	    		if(max(j - k, k - j) >= 2)
	    		    dp[i][j] += dp[i-1][k]; 
			}
			dp[i][10] += dp[i-1][j+1];//j=10表示前面全是零 
		}
	dp[0][10] = 1;
}

void pr()
{
	for(int i = 1; i <= 10; i++)
	{
		for(int j = 0; j <= 10; j++)
		   cout << dp[i][j] << " ";
		cout << endl;
	}
		
	    
}

int getlen(int num)
{
	int res = 0;
	while(num)
	{
		num /= 10;
		res++;
	}
	return res;
}

int getmod(int num)
{
	int res = 1;
	while(num / res >= 10)
	{
		res *= 10;
	}
	return res;
}

int main()
{
	init();
	//pr();
	scanf("%d%d", &b, &a);
	b -= 1;
	lena = getlen(a);
	lenb = getlen(b);
	mod = getmod(a);
	int pre = 99;
	ans = dp[lena][10];
	ans -= dp[lenb][10];
	while(lena)
	{
		int top = a / mod;
		if(!flag1)
		{
			for(int i = 1; i < top; i++)
		   		if(max(i - pre, pre - i) >= 2)
		        	ans += dp[lena][i];
		    flag1 = 1;
		}
		else
			for(int i = 0; i < top; i++)
			    if(max(i - pre, pre - i) >= 2)
			        ans += dp[lena][i];
	    if(lena == 1 && max(top - pre, pre - top) >= 2)
	        ans++;
		lena--;
		pre = top;
		a %= mod;
		mod /= 10;
	}
	//cout << ans << endl;
	pre = 99; 
	mod = getmod(b);
	while(lenb)
	{
		int top = b / mod;
		if(!flag2)
		{
			for(int i = 1; i < top; i++)
		    	if(max(i - pre, pre - i) >= 2)
		        	ans -= dp[lenb][i];
		    flag2 = 1;
		}
		else
			for(int i = 0; i < top; i++)
			    if(max(i - pre, pre - i) >= 2)
		    	    ans -= dp[lenb][i];
		if(lenb == 1 && max(top - pre, pre - top) >= 2)
	        ans--;
	    lenb--;
		pre = top;
		b %= mod;
		mod /= 10;
	}
	cout << ans;
	return 0;
}
