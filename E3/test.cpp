//
//  main.cpp
//  test.cpp
//
//  Created by Sisi Lee on 2019/8/22.
//  Copyright © 2019 Sisi Lee. All rights reserved.
//


#include <iostream>
#include<map>
#include<vector>
using namespace std;
static int INF = 0xfff;
static int MAXV = 500;
int num;
int vsize = 0;
int f[500][500];//记录网络流
int c[500][500]; //记录网络流容量，作为判断使用，不可更改
vector<int> visited; //下标为节点序号,在遍历的时候，确定是否访问过，
vector<int> pre;//下标为节点序号,在标记节点的时候获得的前一个节点。
vector<int> remain; //下标为节点序号，在遍历的时候，获取这个节点和前一个节点之间的剩余流量 = 容量 - 流量。
map<string,int> planet;
//由输入限制，0必为src，1必为dest
void freshMap(string s){
    //如果不包含的时候
    map<string,int>::iterator iter = planet.find(s);
    if(iter == planet.end()){
        cout<<"成功添加s"<<s<<"值为"<<planet.size()<<endl;
        planet[s] = (signed)planet.size();
    }
}
void DFS (int u){ //L利用深度优先遍历的方式找到一条j可行的增广路，前向边不行则考虑后向边。
    int v;
    //一旦找到了一条到汇点的路就可以返回了
    if(visited[1] == 1){
        return;
    }
    visited[u] = 1;
    //从顶点u出发找一条增广路，遍历前向边
    for(v = 1; v < vsize; v++){
        if(c[u][v] > 0 && c[u][v]!= INF && visited[v] == 0 && c[u][v] > f[u][v]){
            remain[v] = c[u][v] - f[u][v];
            pre[v] = u;
            // cout<<"从"<<v楚大
            DFS(v);
        }
    }
    //遍历后向边
    for(v = 1; v < vsize; v++){
        if(c[v][u] > 0 && c[v][u]!=INF && visited[v] == 0 && f[v][u] > 0){
            remain[v] = f[v][u];
            pre[v] = -u;
            DFS(v);
        }
    }
}
void adjustment(){ //处理整条增广路，正向弧反向弧，记录这条路上的流量。
    int u,v,min = INF;
    for(v = 0; v < vsize; v++){
        if(remain[v] != 0 && remain[v] < min){
            min = remain[v];
        }
    }
    u = 1;
    v = pre[1];
    while(true){
        if(v >= 0){ //如果有节点可到达汇点,且属于前向边
            f[v][u] += min; //(5,1)
            u = v;
        }else{ //如果有节点可到达汇点，且属于后向边
            f[u][v] -=min;
            u = -v;
        }
        //到达源点就结束了
        if(u == 0){
            break;
        }
        v = pre[u];
    }
}
//
void flagInit(){
    //长度一开始会不确定，就分配内存
    if(visited.size() != vsize){
        visited.resize(vsize);
        pre.resize(vsize);
        remain.resize(vsize);
    }
    for(int i = 0; i < vsize; i++){
        visited[i] = 0;
        pre[i] = -1;
        remain[i] = 0;
    }
}
int main(){
    string src,dest;
    while((cin >> src >> dest >> num) && num != 0){
        //把上次的数据清空
        if(vsize != 0){
            for (int i = 0; i < vsize; i++){
                for (int j = 0; j < vsize; j++)
                {
                    f[i][j] = 0;
                    c[i][j] = INF;
                }
            }
        }else{
            for(int i = 0; i < MAXV; i++){
                for(int j = 0; j < MAXV; j++){
                    f[i][j] = 0;
                    c[i][j] = INF;
                }
            }
        }
        
        planet.clear();
        //输入一个src，就应该转化为一个序列号。
        freshMap(src);freshMap(dest);
        for(int i = 0; i < num; i++){
            string s1,s2;
            int capacity;
            cin >> s1 >> s2 >> capacity;
            freshMap(s1);freshMap(s2);
            c[planet[s1]][planet[s2]] = capacity;
        }
        vsize = (signed)planet.size(); //顶点数。
        while (true) //要一直回溯查找增广路
        {
            flagInit();
            pre[0] = 0; //放置死循环
            remain[0] = INF; //初始化源点，我也不知道为什么要这样初始化。
            DFS(0); //从源点开始深度优先搜索，找到了路径就会停下
            if(visited[1] == 0){
                break;
            }
            adjustment();
        }
//        循环把总流得到
        int maxFlow = 0;
        for(int i = 0; i < vsize; i++){
            if(f[0][i] != INF){
                maxFlow += f[0][i];
            }
        }
        cout<<"最大流为："<<maxFlow<<endl;
        
    }
    return 0;
}

// 打印矩阵的代码
// for(int j = 0; j < planet.size(); j++){
//             for(int k = 0; k < planet.size(); k++){
//                 cout<<c[j][k]<<" ";
//             }
//             cout<<endl;
//         }

// map<string,int>::iterator it = planet.begin();
// for(int j = 0; j < num; j++){
//     cout<<it->first<<" "<<it->second<<endl;
//     it++;
// }


// 打印矩阵的代码
// for(int j = 0; j < planet.size(); j++){
//             for(int k = 0; k < planet.size(); k++){
//                 cout<<c[j][k]<<" ";
//             }
//             cout<<endl;
//         }

// map<string,int>::iterator it = planet.begin();
// for(int j = 0; j < num; j++){
//     cout<<it->first<<" "<<it->second<<endl;
//     it++;
// }

