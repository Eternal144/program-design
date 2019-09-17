//
//  main.cpp
//  test
//
//  Created by Sisi Lee on 2019/9/4.
//  Copyright © 2019 Sisi Lee. All rights reserved.
//

//1.给每个点标高度 只有高处的水才能往地处流 一开始的高度都为0

//2.在所有的可行弧中不断的寻找增广路 可行弧的定义为 {(i,j) | dis[i]=dis[j]+1}
//
//3.遍历完当前节点后（流不出去了） 重新标记当前点的高度（保证下次再来的时候有路可走） dis[i]=min(dis[j])+1;
//
//4.检查是否存在断层 如果出现断层 则图中已不存在增广路 算法可以结束 否则从源点开始继续遍历
#include<iostream>
using namespace std;
const int inf = 0x7fffffff;
const int MAXN = 210;
const int MAXM = MAXN*MAXN;
int map[MAXN][MAXN]; //记录某条路径的容量。
int dis[MAXN];
int queue[MAXM];
int bef[MAXN];
int num[MAXN];
void set_dis(int end) //传进来了n，好像是顶点数
{
    int top(0),base(0);
    memset(dis,-1,sizeof(dis));
    memset(num,0,sizeof(num));
    queue[top++] = end;
    dis[end]=0;num[0] = 1;
    while(top!=base)
    {
        int pre = queue[base++];
        for(int i=end-1;i!=0;i--)
        {
            if(dis[i] != -1 || map[i][pre] == 0)
                continue;
            dis[i] = dis[pre]+1;
            queue[top++] = i;
            num[dis[i]]++;
        }
    }
}
int cmp(int x,int y)
{
    if(x<y)
        return x;
    return y;
}
int remark(int n,int a)
{
    int tmp=inf;
    for(int i=1;i!=n+1;i++)
        if(map[a][i]!=0&&dis[i]>=0)
            tmp=cmp(tmp,dis[i]+1);
    if(tmp==inf)
        tmp=n;
    return tmp;
    
}
int SAP(int n,int s)
{
    int j,a = s;int flow(0);
    memset(bef,-1,sizeof(bef));
    while(dis[s]<n)
    {
        for(j=1;j!=n+1;j++)
        {
            if(map[a][j]>0&&dis[a]-1==dis[j])
            {
                break;
            }
        }
        if(j<=n)
        {
            bef[j] = a;a = j;
            if(a==n)
            {
                int i = n,max(inf);
                while(bef[i]!=-1)
                {
                    max = cmp(max,map[bef[i]][i]);
                    i = bef[i];
                }
                i = n;
                while(bef[i]!=-1)
                {
                    map[bef[i]][i]-=max;
                    map[i][bef[i]]+=max;
                    i = bef[i];
                }
                flow+=max;a=s;
            }
        }
        else
        {
            int x = remark(n,a);
            num[x]++;num[dis[a]]--;
            if(num[dis[a]]==0)
                return flow;//间隙优化 gap
            dis[a]=x;
            if(a!=s)
                a=bef[a];
        }
    }
    return flow;
}

int main()
{
    freopen("aaa.txt", "r", stdin);
    ios::sync_with_stdio(false);
    int e,n;
    while(cin>>e>>n) //e代表边数。
    {
        memset(map,0,sizeof(map));
        while(e--)
        {
            int a,b,w;
            cin>>a>>b>>w;
            map[a][b] += w;
        }
        set_dis(n-1);
        cout<<SAP(n,1)<<endl;
    }
    return 0;
}
