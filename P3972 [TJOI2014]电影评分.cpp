//注：后缀平衡树+splay，非自己完成，有时间再自己写一遍（主要是不会= =） 
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define inf 1LL<<60
#define ll long long
#define N 100010

using namespace std;

inline char gc(){
    static char buf[1<<16],*S,*T;
    if(S==T){T=(S=buf)+fread(buf,1,1<<16,stdin);if(T==S) return EOF;}
    return *S++;
}
char op[5];
inline void get_S(){
    char ch=gc();
    while(ch<'A'||ch>'Z') ch=gc();op[1]=ch;
}
inline int read(){
    int x=0,f=1;char ch=gc();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=gc();}
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=gc();
    return x*f;
}
int n,fa[N],c[N][2],sz[N],last[N],rt=0,tim[N],owo=0,v[N],dec[N];
int ls[N],rs[N],fir[N],sec[N],rnd[N],num=0,_rt=0;ll tag[N];
inline int comp(int x,int y){//1-> x<y 0-> x>y 2-> x==y
    if(fir[x]<fir[y]) return 1;if(fir[x]>fir[y]) return 0;
    if(tag[sec[x]]<tag[sec[y]]) return 1;
    if(tag[sec[x]]>tag[sec[y]]) return 0;return 2;
}
inline void rebuild(int p,ll l,ll r){
    if(!p) return;
    ll mid=l+r>>1;tag[p]=mid;rebuild(ls[p],l,mid);rebuild(rs[p],mid+1,r);
}
inline void rturn(int &y,ll l,ll r){
    int x=ls[y];ls[y]=rs[x];rs[x]=y;y=x;rebuild(y,l,r);
}
inline void lturn(int &y,ll l,ll r){
    int x=rs[y];rs[y]=ls[x];ls[x]=y;y=x;rebuild(y,l,r);
}
int ff;
inline void _ins(int &p,ll l,ll r){
    if(!p){p=num;ls[p]=rs[p]=0;rnd[p]=rand();tag[p]=l+r>>1;return;}
    int op=comp(num,p);ll mid=l+r>>1;
    if(op==2){ff=p;return;}
    if(op==1){_ins(ls[p],l,mid);if(rnd[ls[p]]<rnd[p]) rturn(p,l,r);return;}
    _ins(rs[p],mid+1,r);if(rnd[rs[p]]<rnd[p]) lturn(p,l,r);
}
inline void update(int p){
    int l=c[p][0],r=c[p][1];
    sz[p]=sz[l]+sz[r]+1;
}
inline void rotate(int x,int &k){
    int y=fa[x],z=fa[y],l=x==c[y][1],r=l^1;
    if(y==k) k=x;
    else c[z][y==c[z][1]]=x;
    fa[c[x][r]]=y;fa[y]=x;fa[x]=z;
    c[y][l]=c[x][r];c[x][r]=y;update(y);update(x);
}
inline void splay(int x,int &k){
    while(x!=k){
        int y=fa[x],z=fa[y];
        if(y!=k){
            if(x==c[y][1]^y==c[z][1]) rotate(x,k);
            else rotate(y,k);
        }rotate(x,k);
    }
}
inline bool cless(int x,int y){
    if(v[x]>v[y]) return 1;if(v[x]<v[y]) return 0;
    if(tag[dec[x]]>tag[dec[y]]) return 1;
    if(tag[dec[x]]<tag[dec[y]]) return 0;
    return tim[x]<tim[y];
}
inline void ins(int &p,int x,int Fa){
    if(!p){p=x;fa[p]=Fa;c[p][0]=c[p][1]=0;splay(p,rt);return;}
    if(cless(x,p)) ins(c[p][0],x,p);
    else ins(c[p][1],x,p);
}
inline void del(int x){
    splay(x,rt);
    if(c[x][0]*c[x][1]==0){
        rt=c[x][0]+c[x][1];fa[c[x][0]+c[x][1]]=0;return;
    }int pre=c[x][0],succ=c[x][1];
    while(c[pre][1]) pre=c[pre][1];
    while(c[succ][0]) succ=c[succ][0];
    splay(pre,rt);splay(succ,c[pre][1]);
    c[succ][0]=fa[x]=0;update(succ);update(pre);
}
inline int getkth(int p,int k){
    if(sz[c[p][0]]+1==k) return p;
    if(k<=sz[c[p][0]]) return getkth(c[p][0],k);
    return getkth(c[p][1],k-sz[c[p][0]]-1);
}
int main(){
//  freopen("a.in","r",stdin);
    n=read();srand(20000712);
    while(n--){
        get_S();if(op[1]=='Q'){printf("%d\n",getkth(rt,read()));continue;}
        if(op[1]=='R'){
            int x=read(),tot=read(),res=0;
            while(tot--){int y=read();if(tim[last[y]]>tim[res]) res=last[y];last[y]=x;}
            v[x]=v[res];dec[x]=dec[res];tim[x]=++owo;sz[x]=1;ins(rt,x,0);continue;
        }if(op[1]=='C'){
            int x=read(),val=read();del(x);v[x]+=val;
            if(v[x]&1||dec[x]){
                ++num;sec[num]=dec[x];fir[num]=v[x]&1;dec[x]=num;
                ff=0;_ins(_rt,0,inf);if(ff) num--,dec[x]=ff;
            }v[x]>>=1;ins(rt,x,0);
        }
    }return 0;
}
