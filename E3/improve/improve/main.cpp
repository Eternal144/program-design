#include<iostream>
#include<queue>
#include<map>
#include<ctime>
#include <random>
#include <fstream>

using namespace std;
const static int maxN = 100;
const static int maxM = maxN * maxN;
const static int INF = 0xffff;

class TravelGraph
{
private:
    int cnt;//边的数量，从0开始编号。
    int Head[maxN];//每一个点最后一条边的编号
    int Next[maxM];//下标为边号，值为这条边起始点指向的上一条边。用于广度优先遍历
    int W[maxM];//每一条边的残量
    int V[maxM];//每一条边指向的点
    int Depth[maxN];//分层图中标记深度
    int cur[maxN];//cur就是记录当前点u循环到了哪一条边
public:
    int s;
    int t;//源点和汇点
    map<string,int>planet;
    TravelGraph() {
        s = 0;
        t = 1;
    }
    void init()
    {
        cnt = -1;
        memset(Head,-1,sizeof(Head));
        memset(Next,-1,sizeof(Next));
    }
    //记录边的信息
    void add(int u,int v,int w)
    {
        cnt++;
        Next[cnt] = Head[u];
        Head[u] = cnt;
        V[cnt] = v;
        W[cnt] = w;
    }
    void addEdge(int u,int v,int w)
    {
        add(u,v,w);
        add(v,u,0); //为了构造剩余图
    }
    int bfs()
    {
        queue<int> Q;
        memset(Depth,0,sizeof(Depth));
        Depth[s]=1;
        Q.push(s);
        do
        {
            int u = Q.front(); //返回队首元素
            Q.pop(); //弹出队首元素
            
            for (int i = Head[u];i != -1;i = Next[i])
                if ((Depth[V[i]] == 0)&&(W[i] > 0))
                {
                    Depth[V[i]] = Depth[u] + 1;
                    Q.push(V[i]);
                }
        }
        while (!Q.empty());
        if (Depth[t] > 0)
            return 1;
        return 0;
    }
    
    int dfs(int u,int flow)
    {
        if (u==t)
            return flow;
        //当前弧的作用就是记录一下该点下一条还能增广的弧，因为在流的过程中找到一条增广路以后就会把这条路流满，但是在下一次增广的过程中，因为第一次找到的增广路可能还有流量，如果再次到达这个点，就无法到达汇点，就找到了不能增广的路进行增广。
        for (int& i=cur[u];i!=-1;i = Next[i])//注意这里的&符号，这样i增加的同时也能改变cur[u]的值，达到记录当前弧的目的
        {
            //在这里进行。最短路径而且有容量
            if ((Depth[V[i]]==Depth[u]+1)&&(W[i]!=0))
            {
                int di = dfs(V[i],min(flow,W[i]));
                if (di > 0)
                {
                    W[i] -= di;
                    W[i^1] += di;
                    return di;
                }
            }
        }
        return 0;
    }
    
    int Dinic(){
        int flow=0;
        while (bfs()) //刷新每一个节点存在可行流上节点的深度。
        {
            //获取到顶点数
            for (int i = 0;i < planet.size();i++)//每一次建立完分层图后都要把cur置为每一个点的第一条边
                cur[i]=Head[i];
            //通过dfs找到增广路，然后偶每次都把d加起来。
            while (int d=dfs(s,INF))
            {
                flow+=d;
            }
        }
        return flow;
    }
    
    void freshMap(string s){
        //如果不包含的时候
        map<string,int>::iterator iter =planet.find(s);
        if(iter == planet.end()){
            planet[s] = (signed)planet.size();
        }
    }
};


char letter[26] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z',
    'X', 'C', 'V', 'B', 'N', 'M'};

// 获得城市名字
string getName() {
    srand(static_cast<unsigned int>((int) time(nullptr)));
    string name = string(1, letter[random() % 8]);
    name.append(1, letter[random() % 18]);
    name.append(1, letter[random() % 26]);
    return name;
}

void getTestData(string s) {
    ofstream file(s);
    int n = 500;
    string start = "EAR"; // 始点
    string end = "MAR"; // 汇点
    int fromStart = random() % 15;// 从始点出发的路径数目
    int toEnds = random() % 15;// 回到汇点的路径数目
    int plants = 100;  // 星球数
    string plantsname[plants]; //城市名字
    for (int j = 0; j < plants; ++j) {
        // 获得星球名字
        plantsname[j] = getName();
    }
    file << "EAR MAR " << n << endl; // 保证始点到汇点一定有路径，每组测试数据的第1行包含旅行的起点星球和终点星球的名称和一个不超过500的正整数N
    srand(static_cast<unsigned int>((int) time(nullptr)));
    for (int i = 0; i < fromStart; ++i) {
        // 随机生成从始点出发的路径
        file << start << " " << plantsname[random() % plants] << " " << random() % 500 << endl;
    }
    for (int k = 0; k < toEnds; ++k) {
        // 随机生成回到汇点的路径
        file << plantsname[random() % plants] << " " << end << " " << random() % 500 << endl;
    }
    for (int l = 0; l < n - fromStart - toEnds; ++l) {
        // 生成中间路径
        file << plantsname[random() % plants] << " " << plantsname[random() % plants] << " " << random() % 500 << endl;
    }
    // 测试用例结束
    file << "EAR MAR 0" << endl;
}

int main(){
    clock_t sTime,eTime;
    sTime = clock();
    getTestData("test.txt");
    freopen("test.txt", "r", stdin);
    ios::sync_with_stdio(false);
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
            travel.addEdge(travel.planet[s1], travel.planet[s2], capacity);
        }
        int maxFlow = travel.Dinic();
        cout<<"最大流为："<<maxFlow<<endl;
    }
    eTime = clock();
    cout << "The run time is: " <<(double)(eTime - sTime) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}
