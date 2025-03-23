/*��λdp������ 
dp[i][j]��ʾ����Ϊi�����ֵ����λ��jʱ��windy������ 
dp[i][j] = sum(dp[i-1][k]) |j-k|>=2
ͳ�ƽ��ʱ�����Ȱ�����[a,b]ת��Ϊ����[0,b]-[0,a-1]
Ȼ�����0��a�����ڵ�windy��ʱ����a�ĳ���Ϊlen����Ҫ�����������������:
1���ۼ����г���<len�Ŀ�ͷ�����windy���ĸ��� 
2���ۼӳ���==len�����λ<a�����λ��windy������ 
3���ۼӳ���==len�����λ==a�����λ��windy������ */
#include<cstdio>
#include<cmath> 
#define MAXN 12
using namespace std;
int x[MAXN], dp[MAXN][MAXN];
int cal(int a)
{
	if(a == 0) return 0;   //a==0ʱҪ����һ�� 
	int len = 0, res = 0;  //len��a�ĳ���
	while(a)
	{
		x[++len] = a % 10;
		a = a / 10;
	}
	for(int i = 1; i < len; i++)     //���1���������г���<len�������ע��jҪ>0 
		for(int j = 1; j < 10; j++)
			res += dp[i][j]; 
	for(int i = 1; i < x[len]; i++)  //���2�������������λ<a�����λ����� 
		res += dp[len][i];
	for(int i = len - 1; i; i--)     //���3������ö��ÿ��λ�������еĿ��� 
	{
		for(int j = 0; j < (i == 1 ? x[i] + 1 : x[i]); j++)//ע�����λ�Ĵ�����С�ģ� 
			if(abs(x[i + 1] - j) > 1) res += dp[i][j];
		if(abs(x[i + 1] - x[i]) <= 1) break;
	}
	return res;
}
int main()
{
	int a, b;
	scanf("%d%d", &a, &b);
	for(int i = 0; i < 10; i++) dp[1][i] = 1; //0,1,...,9����windy��
	for(int i = 2; i <= 10; i++)
		for(int j = 0; j <= 9; j++)
			for(int k = 0; k <= 9; k++)
				if(abs(j - k) > 1) dp[i][j] += dp[i-1][k]; 
	printf("%d", cal(b) - cal(a - 1));
	return 0;
}
