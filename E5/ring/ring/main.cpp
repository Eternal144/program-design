//
//  main.cpp
//  ring
//
//  Created by Sisi Lee on 2019/8/25.
//  Copyright © 2019 Sisi Lee. All rights reserved.
//分治法解决套圈问题。

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#define random(x)(rand()%x)
using namespace std;
const static int INF = 0xffff;

struct Point{
    float x;
    float y;
};

class Ring{
private:
    int num;
    float radius; //所求半径。
public:
    vector<Point> pointArr; //记录所有玩具的坐标。
    vector<Point> pointSortX;
    vector<Point> pointSortY;
    Ring(int n){
        this->num = n;
        pointArr.resize(n);
    }
    void addPoint(){
        for(int i = 0; i<num; i++){
            cin>>pointArr[i].x>>pointArr[i].y;
        }
    }
    //还要空出一格来。
    int PartitionX(int s, int t){
        int low = s;
        int high = t;
        Point pivotkey = pointSortX[s];
        while(low < high){
            while(low < high && pointSortX[high].x >= pivotkey.x){
                high--;
            }
            pointSortX[low] = pointSortX[high];
            while (low < high && pointSortX[low].x <= pivotkey.x) {
                low++;
            }
            pointSortX[high] = pointSortX[low];
        }
        pointSortX[low] = pivotkey;
        return low;
    }
    int PartitionY(int s, int t){
        int low = s;
        int high = t;
        Point pivotkey = pointSortY[s];
        while(low < high){
            while(low < high && pointSortY[high].y >= pivotkey.y){
                high--;
            }
            pointSortY[low] = pointSortY[high];
            while(low < high && pointSortY[low].y <= pivotkey.y){
                low++;
            }
            pointSortY[high] = pointSortY[low];
        }
        pointSortY[low] = pivotkey;
        return low;
     }
    void QSortX(int low, int high){
        if(low < high){
            int pivotloc = PartitionX(low, high);
            QSortX(low, pivotloc);
            QSortX(pivotloc+1, high);
        }
    }
    void QSortY(int low, int high){
        if(low < high){
            int pivotloc = PartitionY(low, high);
            QSortY(low, pivotloc);
            QSortY(pivotloc+1, high);
        }
    }
    //在这里排好x和y
    void sort(){
        pointSortX = pointArr;
        pointSortY = pointArr;
        QSortX(0,num-1);
        QSortY(0,num-1);
    }
    
    float dis(Point p1, Point p2){
        float xdt = p1.x-p2.x;
        float ydt = p1.y-p2.y;
        return sqrt(pow(xdt,2)+pow(ydt,2));
    }
    
    //一个范围，求出最后的一个距离返回。
    float divide(float s, float t){
        int flag = 0; //标记这段区间是否有点。
        //判断这个区域是不是只有一个点
        for(int i = 0; i < num; i++){
            //找到一个处在里面的点。
            if(pointSortX[i].x >= s && pointSortX[i].x <= t){
                //在这个区间有点。
                flag = 1;
                //前一个点不在，后一个点也不在。之间只有一个点
//                作为第一个被检测到的点：前面应该没有在范围内的了。
//                当为最后一个点时：已经只有一个点
//                否则就是下一个点也不在这个范围内
                if(i == num-1 || pointSortX[i+1].x > t){
                    return INF;
                }
                // 作为第一个被检测到的点：前面应该没有在范围内的了。
//                作为最后一个点已经讨论过了。作为倒数第二个点时
                else if(pointSortX[i+1].x <= t){ //区域内只有两个点
                    if(i < num-2){
                        if(pointSortX[i+2].x >= t){ //也可以考虑
                            return dis(pointSortX[i], pointSortX[i+1]);
                        }
                    }else{
                        return dis(pointSortX[i], pointSortX[i+1]);
                    }
                }
//                break;
            }
        }
        if(flag == 0){ //在这段区间没点。
            return INF;
        }
        //在这段区间至少有3点,考虑分治。
        float delta = INF;
        if(s < t){
            float mid = (s+t)/2;
            delta = min(divide(s,mid),divide(mid,t)); //左右两边较小的一个。
            float left = delta == INF ? INF : mid - delta;
            float right = delta == INF ? INF : mid + delta;
            //划分两边区域,把合适的点找出来，再根据原来y轴排序的顺序储存。
            vector<Point> temp;
            for (int i = 0; i < num; i++){ //这里进行了n次遍历肯定是不行的。
                if(pointSortY[i].x >= left && pointSortY[i].x <= right){
                    temp.push_back(pointSortY[i]);
                }
            }
            //只要那个区域里还有点没有考虑 。。。。 @@哭了这里忘记考虑size为0的情况。@@
            if( temp.size() > 0){
                for(int i = 0; i < temp.size()-1; i++){
                    for(int j = i+1; j < temp.size(); j++){
                        if(temp[j].y - temp[i].y > delta){
                            break;
                        }else{
                            delta = min(dis(temp[j],temp[i]),delta);
                        }
                    }
                }
            }
        }
        return delta;
    }
    
    float getRadius(){
        if( num == 1){
            return 0;
        }
        return divide(pointSortX[0].x,pointSortX[num-1].x);
    }
};

void getTestData(string fileName){
    ofstream file(fileName);
    srand(static_cast<unsigned  int>(time(nullptr)));
//    int n = random(100); // 输入测试数据
    int n = 20000;
    file << n <<"\n";
    for (int j = 0; j < n; ++j) {
        double x = rand() / (double) (RAND_MAX / 10000);
        double y = rand() / (double) (RAND_MAX / 10000);
        file << x << " " << y << "\n";
    }
    file << 0 << endl;
}

int main(int argc, const char * argv[]) {
    getTestData("test.txt");
    freopen("test.txt", "r", stdin);
    int n;
    ios::sync_with_stdio(false);
    while(cin >> n && n!=0 ){
        Ring* ring = new Ring(n);
        ring->addPoint(); //添加了所有的点。按照快排的方式排序。
        ring->sort(); //根据x坐标和y坐标排序。排俩。
        float aa = ring->getRadius();
        cout<<"两个玩具最短距离为"<<fixed << showpoint << setprecision(2) <<aa/2<<endl;
    }
    return 0;
}
