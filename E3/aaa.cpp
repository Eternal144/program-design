#include<iostream>
#include<queue>
#include<map>
using namespace std;
const static int maxN = 100;
const static int maxM = maxN * maxN;
const static int INF = 0xffff;

class TravelGraph
{
private:
    int cnt;//边的数量，从0开始编号。
    int Head[maxN];//每一个点最后一条边的编号
    int Next[maxM];//指向对应点的前一条边
    int W[maxM];//每一条边的残量
    int V[maxM];//每一条边指向的点
    int Depth[maxN];//分层图中标记深度
    int cur[maxN];//cur就是记录当前点u循环到了哪一条边
public:
    int s;
    int t;//源点和汇点
    TravelGraph() {
        s = 0;
        t = 1;
    }
    map<string,int>planet;
    void init()
    {
        cnt=-1;
        memset(Head,-1,sizeof(Head));
        memset(Next,-1,sizeof(Next));
    }
    void _Add(int u,int v,int w)
    {
        cnt++;
        Next[cnt]=Head[u]; //还是没看懂那个这句代码。
        Head[u]=cnt;
        V[cnt]=v;
        W[cnt]=w;
    }
    void Add_Edge(int u,int v,int w)
    {
        _Add(u,v,w);
        _Add(v,u,0); //为了构造剩余图
    }
    
    
    int dfs(int u,int flow)
    {
        if (u==t)
            return flow;
        for (int& i=cur[u];i!=-1;i=Next[i])//注意这里的&符号，这样i增加的同时也能改变cur[u]的值，达到记录当前弧的目的
        {
            //在这里进行
            if ((Depth[V[i]]==Depth[u]+1)&&(W[i]!=0))
            {
                int di=dfs(V[i],min(flow,W[i]));
                if (di>0)
                {
                    W[i]-=di;
                    W[i^1]+=di;
                    return di;
                }
            }
        }
        return 0;
    }
    
    int bfs()
    {
        queue<int> Q;
        while (!Q.empty())
            Q.pop();
        memset(Depth,0,sizeof(Depth));
        Depth[s]=1;
        Q.push(s);
        do
        {
            int u=Q.front(); //返回队首元素
            Q.pop(); //弹出队首元素
            
            for (int i=Head[u];i!=-1;i=Next[i])
                if ((Depth[V[i]]==0)&&(W[i]>0))
                {
                    Depth[V[i]]=Depth[u]+1;
                    Q.push(V[i]);
                }
        }
        while (!Q.empty());
        if (Depth[t]>0)
            return 1;
        return 0;
    }
    int Dinic()
    {
        int Ans=0;
        while (bfs())
        {
            //这里的n应该是指顶点数
            for (int i = 0;
                 i < planet.size(); //获取到顶点数
                 i++)//每一次建立完分层图后都要把cur置为每一个点的第一条边
                cur[i]=Head[i];
            //通过dfs找到增广路，然后偶每次都把d加起来。
            while (int d=dfs(s,INF))
            {
                Ans+=d;
            }
        }
        return Ans;
    }
    void freshMap(string s){
        //如果不包含的时候
        map<string,int>::iterator iter =planet.find(s);
        if(iter == planet.end()){
            cout<<"成功添加s"<<s<<"值为"<<planet.size()<<endl;
            planet[s] = (signed)planet.size();
        }
//        planet["EAR"] = 0;
//        planet["AAA"] = 2;
//        planet["BBB"] = 3;
//        planet["CCC"] = 4;
//        planet["DDD"] = 5;
//        planet["MAR"] = 1;
    }
    //获取对应的序号
    int getNumber(string s){
        return planet[s];
    }
};

int main(){
    string src,dest;
    int num;
    while((cin >> src >> dest >> num) && num != 0){
        TravelGraph travel;
        travel.init();
        travel.freshMap(src);
        travel.freshMap(dest);
        for(int i = 0; i < num; i++){
            string s1,s2;
            int capacity;
            cin >> s1 >> s2 >> capacity;
            travel.freshMap(s1);
            travel.freshMap(s2);
            travel.Add_Edge(travel.getNumber(s1), travel.getNumber(s2), capacity);
        }
        int maxFlow = travel.Dinic();
        cout<<"最大流为："<<maxFlow<<endl;
    }
    return 0;
}