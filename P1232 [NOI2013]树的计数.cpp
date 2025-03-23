#include<cstdio>
#include<iostream>
#define LL long long
#define MAXN 200005

using namespace std;

int n, p;
int t[MAXN], pos[MAXN], a[MAXN], flag[MAXN], sta[MAXN];
double ans = 1.0;
double x[MAXN], s[MAXN];
char c;

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

int main()
{
	n = read();
	//��dfs���Ϊ12345 
	for(int i = 1; i <= n; i++)
	    t[read()] = i;  //t��¼��dfs���г��ֵ�ʱ�� 
	for(int i = 1; i <= n; i++)
	{
		int tmp = t[read()]; //��bfs��ת������¼ 
		a[tmp] = i; //a��¼��bfs���г��ֵ�ʱ�� 
		pos[i] = tmp; //��¼�µ�bfs�� 
	}
	//x��¼���� 
	x[1] = 1.0; 
	for(int i = 1; i < n; i++)//����bfs��˳�� 
    {
	    //��i��bfs�����dfs����i����һ������bfs��
	    //��ô˵��dfsһ���ص�����������ϵĵط�
		//����i+1��i���ϲ㣬��iΪҶ�ӽڵ� 
        if(pos[i] > pos[i+1]) x[i] = 1.0; 
        if(x[i] == 1.0)  
        {  
            flag[i]++; //i��Ҷ�ӽڵ� 
            flag[i+1]--;  
        }
        //s[i]��¼bfs��iΪֹȷ����Ҷ�ӽ��ĸ��� 
        s[i] = s[i-1] + x[i];
    }
    for(int i = 1; i < n; i++)//����dfs��˳�� 
        if(a[i] < a[i+1])
        {  
            if(s[a[i+1]-1] - s[a[i]-1] > 0)  //dfs�����ڵ�������֮�������Ҷ�ӽڵ� 
            {  
                flag[a[i]]++; //i��Ҷ�ӽڵ� 
                flag[a[i+1]]--;  
            }  
            else sta[++p] = a[i];//��ȷ�������ýڵ���ջ 
        }  
    for(int i = 1; i <= n; i++)  
        flag[i] += flag[i-1];  
    for(int i = 1; i <= p; i++)//��ջ��������δȷ���ı��Ϊ0.5 
        if(flag[sta[i]] == 0)
		    x[sta[i]] = 0.5;//flag[xi]==1��ζ��xi��ֵ�Ѿ���ȷ��   
    for(int i = 1; i <= n; i++)  
        ans += x[i];  
    printf("%.3lf", ans);  
	return 0;
}
