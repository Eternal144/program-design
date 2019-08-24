//
//  main.cpp
//  cable
//
//  Created by Sisi Lee on 2019/8/23.
//  Copyright © 2019 Sisi Lee. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <set>
#include <stdlib.h>
using namespace std;

const static int INF = 0xff;
struct Point{
    float x;
    float y;
    float z;
};
class Cable{
private:
    float xlen; //x坐标长度
    float ylen; //y坐标长度
    float zlen; //z坐标长度
    float doorH; //门的高度
    int n;
    float len;
    vector<int> typeArr;//记录每个y序号所属墙的位置
    set<int> setChoose; //记录选中的序号。
public:
    //记录点的坐标和属于哪一道墙，在输入的时候就应该判断
    // map<Point,int> pointMap;
    int s; //起点
    int t; //终点
    vector<Point> point;
    //最短距离的邻接矩阵
    float** matrix;
    int doorType;
    // vector<vector<float>> matrix; //用来表示各个点之间的最短路径。
    Point door[4];//最后一行保存门的四个坐标
    Cable(float x, float y, float z,int n) :len(0){
        this->xlen = x;
        this->ylen = y;
        this->zlen = z;
        this->n = n;
    }
    void init(){
        matrix = new float*[n];
        for (int i = 0; i <= n; i++){
            matrix[i] = new float[n];
            for(int j = 0; j < n; j++){
                matrix[i][j] = 0;
            }
        }
        point.resize(n);
        typeArr.resize(n);
        for(int i = 0; i<n; i++){
            // Point temp;
            cin>>point[i].x>>point[i].y>>point[i].z;
            typeArr[i] = getWallNum(point[i]);
        }
        for(int j = 0; j<4; j++){
            cin>>door[j].x>>door[j].y>>door[j].z;
            //判断门属于哪面墙
            if(door[j].z!=0 && (door[j].x!=0 || door[j].y!=0)){
                doorType = getWallNum(door[j]);
            }
        }
    }
    //根据cp1和cp2判断之间有没有门，如果门高任何顶点，认为有门
     bool judgeDoor(int type){
         float xlen = 0;
         float ylen = 0;
         for(int i = 0; i < 4; i++){
             doorH = max(doorH,door[i].z);
             xlen = max(xlen,door[i].x);
             ylen = max(ylen,door[i].y);
         }
//         doorH = height;
         //如果门比两个插座都矮，不用考虑。
//         如果门与两个插座都不同面，也不用考虑
         if( (doorH > point[s].z && doorH > point[t].z) && (doorType != typeArr[s] || doorType != typeArr[t])){
             if(type == 0 && doorType == typeArr[s]){ //同面判断是否有门,门在同面才有影响
                 if(doorType%2 == 0){ //判断x
                     if(xlen < point[s].x || xlen < point[t].x){
                         return true;
                     }
                 }else{
                     if(ylen < point[s].y || ylen < point[s].y){
                         return true;
                     }
                 }
             }else{ //相邻判断是否有门
                 //两个点不同面，门可能在两个点之中的一个面中。
                 //same表示与门同一个面，diff表示与门不同一个面
                 int same = doorType == typeArr[s] ? s : t;
                 int diff = same == s ? t : s;
                 int flag;
                 if(doorType%2 == 0){ //判断x
                     flag = point[diff].x > point[same].x;
                     if(flag){
                         return xlen > point[same].x;
                     }else{
                         return xlen < point[same].x;
                     }
                 }else{ //判断y
                     flag = point[diff].y > point[same].y;
                     if(flag){
                         return ylen > point[same].y;
                     }else{
                         return ylen < point[same].y;
                     }
                 }
             }
         }
         return false;
    }
    
    //当s和t之间有门时
     void withDoorLen(){
         if(point[s].x == point[t].x){
             len += fabs(point[s].y - point[t].y);
         }else{
             len += fabs(point[s].x - point[t].x);
         }
         len += doorH - point[s].z;
         len += doorH - point[t].z;
     }
     void withoutDoorLen(int type){
         len += fabs(point[s].x - point[t].x);
         len += fabs(point[s].y - point[t].y);
         if(type == 2){ //对面则需要走地上
             len += fabs(point[s].z + point[t].z);
         }else{
             len += fabs(point[s].z - point[t].z);
         }
         
     }
    //计算最短路径，并且更新矩阵
    //三种情况：
    //    1. 当两个点属于同一片墙时
    //    2. 当两个点属于相邻的墙时
    //    3. 当两个点属于对面的墙时
    //相邻也有可能有门哦！对面从下面走固定。
     void update(){
         //属于同一片墙
         int type = abs(typeArr[s] - typeArr[t]);
         if(type == 0){ //在同一面墙上
             if(judgeDoor(0)){
                 withDoorLen();
             }else{
                 withoutDoorLen(0);
             }
//         cout<<"点("<<point[s].x<<","<<point[s].y<<","<<point[s].z<<
//         ")"<<"与点("<<point[t].x<<","<<point[t].y<<","<<point[t].z<<
//         ")处于同一面墙上"<<endl;
         }else if(abs(type) == 2){ //在对面墙上
             withoutDoorLen(2);
         }else{ //在相邻墙上
             if(judgeDoor(1)){
                 withDoorLen();
             }else{
                 withoutDoorLen(1);
             }
         }
         //获取到len，根据n构建邻接矩阵
         matrix[s][t] = len;
//         matrix[t][s] = len;
         len = 0;
     }
    
    //找到u所有路径中最短的一条，设置最短路径的s和t。
    float getlen(float minL){
        for(int i = 0; i < n-1; i++){
            for(int j = i+1; j < n; j++){
                if(matrix[i][j] != 0 && matrix[i][j] < minL){
                    s = i;
                    t = j;
                    minL = matrix[i][j];
                }
            }
        }
        matrix[s][t] = 0;
        return minL;
    }
    //查找该序号是否已经添加进set
    bool find(int s){
        set<int>::iterator it = setChoose.find(s);
        if(it != setChoose.end()){
            return true;
        }else{
            return false;
        }
    }
    //利用算法算出来最短路径返回。
    int getMinLen(){
//        float finalL = 0;
        float slen;
        while (setChoose.size() != n) {
            slen = getlen(INF);
            if(!find(s) || !find(t)){
                len += slen;
            }
            if(!find(s)){
                setChoose.insert(s);
            }
            if(!find(t)){
                setChoose.insert(t);
            }
        }
        return ceil(len);
    }
    
    int getWallNum(Point p){
        if(p.y == 0){
            return 0;
        }else if(p.x == 0){
            return 1;
        }else if(p.y == ylen){
            return 2;
        }else if(p.x == xlen){
            return 3;
        }else{
            return INF;
        }
    }
};
//判断墙属于哪一面墙

int main(int argc, const char * argv[]) {
    //每次都能自动那个刷新。
    float xlen; //x坐标长度
    float ylen; //y坐标长度
    float zlen; //z坐标长度
    int n;
    while(cin >> xlen >> ylen >> zlen >> n){
        if(xlen==0 && ylen==0 && zlen==0 && n==0){
            break;
        }
        Cable* cable = new Cable(xlen,ylen,zlen,n);
        //创建大小为n的构造体数组,保存所有的点，点的序号为所在数组中的下标。
        cable->init();
        for(int i = 0; i<n-1; i++){
            for(int j = i+1; j<n; j++){
                cable->s = i;
                cable->t = j;
                cable->update();
                cout<<"s为："<<i<<"t为："<<j<<"最短距离为："<<cable->matrix[i][j]<<endl;
//                cout<<"t为："<<cable->matrix[t][s]<<endl;
            }
        }
        //图组好了，最后选出最短路径，再遍历加合
        cout<<"最短需要的长度为："<<cable->getMinLen()<<endl;
        cout<<"哈哈哈"<<endl;
        cout<<"哈哈哈"<<endl;
    }
    return 0;
}
