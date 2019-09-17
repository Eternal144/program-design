//
//  main.cpp
//  confess
//
//  Created by Sisi Lee on 2019/8/25.
//  Copyright © 2019 Sisi Lee. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <cmath>
#include <fstream>
#define random(x)(rand()%x)
using namespace std;
struct Edge{
    int s;
    int t;
};
struct Node{
    int id;
    int pushTime; //记录入栈时间
    int popTime; //记录出栈时间
    set<int> adjNodes;
};
class Love{
private:
    vector<Node> tree; //各条边的集合，用于生成一棵树。
    int nodeN; // 节点的总个数。
    int clock;
    vector<int> visited;
public:
    void init(int n){
        nodeN = n;
        clock = 0;
        visited.resize(n,0); //初始化数组。
        tree.resize(n);
    }
    void createTree(){
        for (int i = 0; i < nodeN-1; i++){  //输入边的时候就已经成树了。
            int s;int t;
            cin>>s>>t;
            if(tree[s].id != s){ //已经存在，更新next。
                tree[s].id = s;
            }
            if(tree[t].id == t){ //已经存在，更新next。
                tree[t].id = t;
            }
            //不用查找，set自动去重
            if(s < t){
                tree[s].adjNodes.insert(t);
            }else{
                tree[t].adjNodes.insert(s);
            }
        }
    }
    //从0开始dfs
    void dfs(int n){
        visited[n] = 1;
        tree[n].pushTime = ++clock;
        set<int>::iterator it = tree[n].adjNodes.begin();
        while(it != tree[n].adjNodes.end()){
            if(visited[*it] == 0){ //还没有访问，压栈
                dfs(*it);
            }
            it++;
        }
        tree[n].popTime = ++clock;
    }
    //利用深度优先遍历，记录出入栈时间。
    void record(){
        dfs(0);
    }
    //判断b是不是a的祖先。
    bool ancestors(int a,int b){
        if(tree[b].pushTime < tree[a].pushTime && tree[b].popTime > tree[a].popTime){
            return 1;
        }
        return 0;
    }
    //真正找公共祖先。
    int search(int n, int s, int t){
        //判断所有的儿子
        set<int>::iterator it = tree[n].adjNodes.begin();
        while(it != tree[n].adjNodes.end()){//找不到这样一个儿子区间。那说明就是最近的了。
            if(tree[*it].pushTime < s && tree[*it].popTime > t){
                n = search(*it, s, t);
                break;
            }
            it++;
        }
        return n;
    }
    //获取a和b最近的共同祖先。
    int getLastCommonAnc(int a, int b){
        int s = min(tree[a].pushTime,tree[b].pushTime);
        int t = max(tree[a].popTime,tree[b].popTime);
        return search(0,s,t);
    }
    //判断一个点是不是另一个点的邻接。
    bool adjJudge(int a, int b){
        set<int>::iterator it = tree[a].adjNodes.begin();
        while(it != tree[a].adjNodes.end()){
            if(*it == b){
                return true;
            }
            it++;
        }
        return false;
    }
    //判断c是不是a或者b的祖先，或者是两个的最近共同祖先。题目提示没有考虑到。
    void judge(int a, int b, int c){
        int ancA = ancestors(a, c);
        int ancB = ancestors(b, c);
        if((ancA ^ ancB) == 1){ //是其中一个的祖先。
            cout<<"yes"<<endl;
        }else if(adjJudge(a, b) || adjJudge(b, a)){ //一个是另一个的邻接矩阵，如果c是任意两个之一，则可以，否则不行
            if(c == a || c == b){
                cout<<"yes"<<endl;
            }else{
                cout<<"no"<<endl;
            }
        }
        else if(getLastCommonAnc(a, b) == c){ //c是AB最近的祖先。找到最近的t共同祖先，并且和c判断。
            cout<<"yes"<<endl;
        }else{
            cout<<"no"<<endl;
        }
    }
    //输入测试数据。
    void inputForJudge(){
        int jn = 0;
        cin>>jn;
        for(int i = 0; i < jn; i++){
            int a,b,c;
            cin>>a>>b>>c;
            judge(a,b,c);
        }
    }
    //开始判断了
    void loveMain(int n){
        init(n);
        createTree();
        record();
        inputForJudge();
    }
};

void getTestData(string fileName){
    ofstream file(fileName);
    srand(static_cast<unsigned  int>(time(nullptr)));
    int num = random(100);
    file << num << "\n";
    set<int> connect;
    set<int> unconnect;
    connect.insert(0); //未连接村庄
    for(int i = 1; i < num; i++){ //已连接村庄。
        unconnect.insert(i);
    }
    for(int i = 0; i < num-1; i++){
        //从连接和未连接中随机拿一个。
        int a = random(connect.size()); //0
        set<int>::iterator ita = connect.begin();
        while(a!=0){
            ita++;
            a--;
        }
        a = random(unconnect.size());
        set<int>::iterator itb = unconnect.begin();
        while(a!=0){
            itb++;
            a--;
        }
        connect.insert(*itb);
        unconnect.erase(*itb);
        file << *ita <<" "<< *itb <<"\n";
    }
    int testN = random(5000);
    file << testN <<"\n";
    for(int j = 0; j < testN; j++){
        int a = random(num);
        int b = random(num);
        int c = random(num);
        file << a <<" "<< b <<" "<< c <<"\n";
    }
    file << 0 <<"\n";
}

int main(int argc, const char * argv[]) {
    getTestData("test.txt");
    freopen("test.txt","r",stdin);
    ios::sync_with_stdio(false);
    int nodeN;
    while(cin>>nodeN && nodeN!=0){
        Love love;
        love.loveMain(nodeN);
    }
    return 0;
}
