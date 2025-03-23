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
	//将dfs序变为12345 
	for(int i = 1; i <= n; i++)
	    t[read()] = i;  //t记录在dfs序中出现的时间 
	for(int i = 1; i <= n; i++)
	{
		int tmp = t[read()]; //将bfs序转换并记录 
		a[tmp] = i; //a记录在bfs序中出现的时间 
		pos[i] = tmp; //记录新的bfs序 
	}
	//x记录层数 
	x[1] = 1.0; 
	for(int i = 1; i < n; i++)//按照bfs的顺序 
    {
	    //若i的bfs序大于dfs序中i的下一个数的bfs序
	    //那么说明dfs一定回到了两层或以上的地方
		//所以i+1在i的上层，且i为叶子节点 
        if(pos[i] > pos[i+1]) x[i] = 1.0; 
        if(x[i] == 1.0)  
        {  
            flag[i]++; //i是叶子节点 
            flag[i+1]--;  
        }
        //s[i]记录bfs到i为止确定的叶子结点的个数 
        s[i] = s[i-1] + x[i];
    }
    for(int i = 1; i < n; i++)//按照dfs的顺序 
        if(a[i] < a[i+1])
        {  
            if(s[a[i+1]-1] - s[a[i]-1] > 0)  //dfs序相邻的两个点之间出现了叶子节点 
            {  
                flag[a[i]]++; //i是叶子节点 
                flag[a[i+1]]--;  
            }  
            else sta[++p] = a[i];//不确定，将该节点入栈 
        }  
    for(int i = 1; i <= n; i++)  
        flag[i] += flag[i-1];  
    for(int i = 1; i <= p; i++)//出栈，将其中未确定的标记为0.5 
        if(flag[sta[i]] == 0)
		    x[sta[i]] = 0.5;//flag[xi]==1意味着xi的值已经被确定   
    for(int i = 1; i <= n; i++)  
        ans += x[i];  
    printf("%.3lf", ans);  
	return 0;
}
