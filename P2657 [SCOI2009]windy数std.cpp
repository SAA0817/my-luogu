/*数位dp入门题 
dp[i][j]表示长度为i的数字的最高位是j时的windy数个数 
dp[i][j] = sum(dp[i-1][k]) |j-k|>=2
统计结果时，首先把区间[a,b]转换为区间[0,b]-[0,a-1]
然后计算0到a区间内的windy数时，设a的长度为len，需要分三种情况进行讨论:
1、累加所有长度<len的开头非零的windy数的个数 
2、累加长度==len且最高位<a的最高位的windy数个数 
3、累加长度==len且最高位==a的最高位的windy数个数 */
#include<cstdio>
#include<cmath> 
#define MAXN 12
using namespace std;
int x[MAXN], dp[MAXN][MAXN];
int cal(int a)
{
	if(a == 0) return 0;   //a==0时要特判一下 
	int len = 0, res = 0;  //len是a的长度
	while(a)
	{
		x[++len] = a % 10;
		a = a / 10;
	}
	for(int i = 1; i < len; i++)     //情况1，遍历所有长度<len的情况，注意j要>0 
		for(int j = 1; j < 10; j++)
			res += dp[i][j]; 
	for(int i = 1; i < x[len]; i++)  //情况2，遍历所有最高位<a的最高位的情况 
		res += dp[len][i];
	for(int i = len - 1; i; i--)     //情况3，暴力枚举每个位置上所有的可能 
	{
		for(int j = 0; j < (i == 1 ? x[i] + 1 : x[i]); j++)//注意最低位的处理！！小心！ 
			if(abs(x[i + 1] - j) > 1) res += dp[i][j];
		if(abs(x[i + 1] - x[i]) <= 1) break;
	}
	return res;
}
int main()
{
	int a, b;
	scanf("%d%d", &a, &b);
	for(int i = 0; i < 10; i++) dp[1][i] = 1; //0,1,...,9都是windy数
	for(int i = 2; i <= 10; i++)
		for(int j = 0; j <= 9; j++)
			for(int k = 0; k <= 9; k++)
				if(abs(j - k) > 1) dp[i][j] += dp[i-1][k]; 
	printf("%d", cal(b) - cal(a - 1));
	return 0;
}
