//
//  main.cpp
//  virus
//
//  Created by Sisi Lee on 2019/8/26.
//  Copyright © 2019 Sisi Lee. All rights reserved.
//

#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;
struct Point{
    int x; //横坐标
    int y; //纵坐标
};

class Virus{
private:
    int row;
    int col;
    int normalN; //正常未被感染数。
    map<int,vector<Point>> infPoint; //初始被感染的点和它的坐标。
    map<int,int> infNum;
    vector<vector<int>> computers; //记录电脑的防御能力
    vector<vector<Point>> root; //记录根部的二维数组。
    vector<vector<vector<Point>>> tracer;
public:
    Virus(int n, int m){
        row = n;
        col = m;
        normalN = 0;
    }
    void init(){ //手动初始化这些向量
        //先建好二维数组。
        vector<int> tempInt;
        tempInt.resize(col,0);
        vector<Point> tempPoint;
        Point point;
        point.x = -1;
        point.y = -1;
        tempPoint.resize(col,point);
        vector<vector<Point>> tempList;
        vector<Point> aa;
        for(int j = 0; j < col; j++){
            tempList.push_back(aa);
        }
        for(int i = 0; i < row; i++){
            computers.push_back(tempInt);
            root.push_back(tempPoint);
            tracer.push_back(tempList);
        }
        
    }
    Point findRoot(int x, int y){
        Point p;
        if(root[x][y].x == -1){
            p.x = x; p.y = y;
            return p;
        }
        if(root[x][y].x == x && root[x][y].y == y){ //如果自己就是根节点。
            return root[x][y]; //把自己的坐标返回。
        }else{
            return findRoot(root[x][y].x,root[x][y].y);
        }
    }
    //防御能力1000，在h这里的时候直接更新。
    void getInput(){ //把-1h
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                cin>>computers[i][j];
                int cur = computers[i][j];
                Point point;
                if(cur > 0){ //是个病毒。病毒不管。
                    point.x = i;
                    point.y = j;
                    root[i][j] = point;
                    infPoint[cur].push_back(point);
                    infNum[cur] = 1;
                }else{ //没有的话先设为-1;
                    normalN++;
                    point.x = -1;
                    point.y = -1;
                    if(i != 0){ //不是第一排的，可跟上面的比较
                        if(computers[i-1][j] == cur){ //如果相等，抱团。
                            Point p; //将要添加进tracer的点。
                            point.x = i;
                            point.y = j;
                            if(root[i-1][j].x != -1){ //原来有值，要跟着新的
                                p = findRoot(i-1,j); //自己没值
                                //找到了原来的根节点。把自己插进去
//                                root[i][j] = p; //现在的点也指向原来的根节点。
                                tracer[p.x][p.y].push_back(point); //只插入自己就够了
                                point = p;
                            }else{ //原来没值，跟着现在的，两个都要插入进去。
                                p = findRoot(i, j);
                                root[i-1][j] = p;//根更新。waring。
                                Point p2;
                                p2.x = i-1; p2.y = j;
                                tracer[p.x][p.y].push_back(p2);
                                tracer[p.x][p.y].push_back(point);
                            }
                        }
                        root[i][j] = point;
                    }
                    if( j!= 0){ //不是第一列的，可跟左边的比较
                        if(computers[i][j-1] == cur){ //左边和当前的相等，抱团。
                            point.x = i;
                            point.y = j;
                            Point p;
                            if(root[i][j-1].x != -1){
                                p = findRoot(i, j-1);
                                point = p;
                                tracer[p.x][p.y].push_back(point);
                            }else{
                                //如果是自己怎么办
                                p = findRoot(i, j);
                                root[i][j-1] = p;
                                Point p2 ;
                                int n = (signed)tracer[p.x][p.y].size()-1;
                                if(n >= 0){
                                    p2 = tracer[p.x][p.y][n];
                                    if(p2.x!= i || p2.y != j){
                                        tracer[p.x][p.y].push_back(point);
                                    }
                                }else{
                                    tracer[p.x][p.y].push_back(point);
                                }
                                p2.x = i; p2.y = j-1;
                                tracer[p.x][p.y].push_back(p2);
                            }
                        }
                        root[i][j] = point;
                    }
                }
            }
        }
    }
    void spread(Point p,int day){
        int type = computers[p.x][p.y];
        if(p.x!=0){ //不在第一排,就可以检测上面
            int up = computers[p.x-1][p.y];
            if(up < 0 && up >= day ){ //满足感染条件。
                Point p1 = root[p.x-1][p.y]; //都指向了一个虚拟根节点。
                if(p1.x == -1){//是个空的。
                    p1.x = p.x-1; p1.y = p.y;
                    computers[p1.x][p1.y] = type;
                    infNum[type] = ++infNum[type];
                    infPoint[type].push_back(p1);
                    
                }else{
                    vector<Point> temp = tracer[p1.x][p1.y]; //找到所有要被感染的点；
                    for(int j=0; j<temp.size(); j++){
                        p1 = temp[j];
                        computers[p1.x][p1.y] = type;
                        infPoint[type].push_back(p1);
                        infNum[type] =  ++infNum[type];
                    }
                }
            }
        }
        if(p.y!=0){ //不在第一列，k就可以检查左边
            int left = computers[p.x][p.y-1];
            if(left < 0 && left >= day){
                Point p1 = root[p.x][p.y-1];
                if(p1.x == -1){//是个空的。
                    p1.x = p.x; p1.y = p.y-1;
                    computers[p1.x][p1.y] = type;
                    infNum[type] = ++infNum[type];
                    normalN--;
                    infPoint[type].push_back(p1);
                    
                }else{
                    vector<Point> temp = tracer[p1.x][p1.y];
                    for(int j=0; j<temp.size(); j++){
                        p1 = temp[j];
                        computers[p1.x][p1.y] = type;
                        infPoint[type].push_back(p1);
                        infNum[type] = ++infNum[type];
                        normalN--;
                    }
                }
                
            }
        }
        if(p.x < row-1){ //检查下面。
            int down = computers[p.x+1][p.y];
            if(down < 0 && down >= day){
                Point p1 = root[p.x+1][p.y];
                if(p1.x == -1){//是个空的。
                    p1.x = p.x+1; p1.y = p.y;
                    computers[p1.x][p1.y] = type;
                    infNum[type] = ++infNum[type];
                    normalN--;
                    infPoint[type].push_back(p1);
                }else{
                    vector<Point> temp = tracer[p1.x][p1.y];
                    for(int j=0; j<temp.size(); j++){
                        p1 = temp[j];
                        computers[p1.x][p1.y] = type;
                        infPoint[type].push_back(p1);
                        infNum[type] = ++infNum[type];
                        normalN--;
                    }
                }
                
                
            }
        }
        if(p.x < col-1){ //检查右边。
            int down = computers[p.x][p.y+1];
            if(down < 0 && down >= day){
                Point p1 = root[p.x][p.y+1];
                if(p1.x == -1){//是个空的。
                    p1.x = p.x; p1.y=p.y+1;
                    computers[p1.x][p1.y] = type;
                    infNum[type] = ++infNum[type];
                    normalN--;
                    infPoint[type].push_back(p1);
                }else{
                    vector<Point> temp = tracer[p1.x][p1.y];
                    for(int j=0; j<temp.size(); j++){
                        p1 = temp[j];
                        computers[p1.x][p1.y] = type;
                        infPoint[type].push_back(p1);
                        infNum[type] = ++infNum[type];
                        normalN--;
                    }
                }
                
            }
        }
    }

    void Infection(){ //开始感染。
        int day = -1;
        while(normalN > 0){ //只要还有电脑没感染。
            for(int i=1; i<=infPoint.size(); i++){ //有多少种类型的就要遍历多少次。
                Point p;
                for(int j = 0; j < infPoint[i].size(); j++){
                    p = infPoint[i][j];//被感染的电脑。传播到四周。
                    spread(p,day);
                }
        }
        day--;
    }
    }
    
    void solve(){
        int n;
        cin>>n;
        int a;
        for(int i = 0; i<n; i++){
            cin>>a;
            cout<<"共有"<<infNum[a]<<"个"<<endl;
        }
    }
    //在这里更新点，进行抱团。当前的day为1，抱团1。
    void virusMain(){
        init();
        getInput();
        Infection();
        solve();
    }
};

int main(int argc, const char * argv[]) {
    freopen("aaa.txt", "r", stdin);
    ios::sync_with_stdio(false);
    int row,col;
    while(cin>>row>>col && row!= 0 && col!= 0){
        Virus* virus = new Virus(row,col);
        virus->virusMain();
        cout<<"哈哈"<<endl;
    }
    return 0;
}
