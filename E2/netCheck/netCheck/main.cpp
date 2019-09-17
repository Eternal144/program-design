//
//  main.cpp
//  netCheck
//
//  Created by Sisi Lee on 2019/9/1.
//  Copyright © 2019 Sisi Lee. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include<ctime>
#include <fstream>
#define random(x) (rand()%x)
using namespace std;
static  const int MAX_SIZE = 10000;

class UnionFindSet
{
private:
    vector<int> parent; //代表子集树的根部
    vector<int> rank; //代表树的高度
    set<int> count;
public:
    //传入节点数
    UnionFindSet(int n){
        parent.resize(n,-1);
        rank.resize(n,0);
    }
    UnionFindSet() : parent(vector<int>(MAX_SIZE)),
    rank(vector<int>(MAX_SIZE,0))
    {
        for(int i = 0; i < MAX_SIZE; i++){
            parent[i] = i;
            // cout<<parent[i];
        }
    }
    //找到某个节点所属树的根节点。
    // 如果该节点为根节点，则直接返回
    // 如果不是，则找到该节点的父节点的根节点，直到找到的父节点为根节点为止。
    //x会不存在
    int findRoot(int x){
        if(parent[x] == -1){
            parent[x] = x;
        }
        count.insert(x);
        return x == parent[x] ? x : (parent[x] = findRoot(parent[x]));
    }
    
    void unionBoth(int k1, int k2){
        //在这里保证只在根部拼接。减少时间复杂度。路径压缩
        k1 = findRoot(k1);
        k2 = findRoot(k2);
        //在这里保证树拼接在高度低的那边，减少树的高度。按秩合并
        if(rank[k1] > rank[k2]){
            parent[k2] = k1;
        }else{
            parent[k1] = k2;
            if(rank[k1] == rank[k2]){
                rank[k2]++;
            }
        }
    }
    bool if_same(int k1, int k2){
        return findRoot(k1) == findRoot(k2);
    }
    //返回子集数目
    int getSetNumber(){
        vector<int> temp; //专门用来记录根节点。
        count.clear(); //用来记录遍历过的节点。
        for(int i = 0; i < parent.size(); i++){
            set<int>::iterator it = count.find(parent[i]);
            int root;
            if(it == count.end()){
                 root = findRoot(i);//获取每个节点的根节点。
            }
            vector<int>::iterator itt = find(temp.begin(),temp.end(),root);
            if(itt == temp.end()){
                temp.push_back(root);
            }
        }
        return (signed)temp.size();
    }
};

void getTestData(string fileName){
    ofstream file(fileName);
    srand(static_cast<unsigned int>(time(nullptr)));
    int n = random(10000);
    file << n <<" \n";
    int rows = random(20000); //连接数应该比计算机数量多。
    for(int i = 0; i < rows; i++){ //
        int k1 = random(n);
        int k2 = random(n);
        while(k1 == k2){
            cout<<"这俩一样啦"<<endl;
            k2 = random(n);
        }
        if(k1 < n/2){
            file << "I " << k1 << " " << k2 <<" \n";
        }else{
            file << "C " << k1 << " " << k2 <<" \n";
        }
    }
}

int main(){
    string fileName = "test.txt";
    //在这里生成测试文件。
    getTestData("test.txt");
    freopen("test.txt", "r", stdin);
    ios::sync_with_stdio(false);
    int number;
    while( (cin >> number) && number != 0){
        UnionFindSet *union_find_set = new UnionFindSet(number);
        char instruct; //指令
        while((cin >> instruct) && instruct != 'S'){
            int k1,k2; //接收机器。在num为1的时候
            if(number == 1){
                cin >> k1;
                if( instruct == 'C'){
                    cout<<"yes"<<endl;
                }
            }else{
                cin >> k1 >> k2;
                if( instruct == 'C'){
                    if(union_find_set->if_same(k1-1,k2-1)){ //如果找的到
                        cout << "yes" << endl;
                    }else{//如果找不到
                        cout << "no" << endl;
                    }
                }else if(instruct == 'I'){
                    union_find_set->unionBoth(k1-1,k2-1);
                }
            }

        }
        int numOfSets = union_find_set->getSetNumber();
        if(numOfSets == 1){
            cout << "The network is connected."<< endl;
        }else if(numOfSets == 0){
            cout << "No computer" << endl;
        }else{
            cout << "There are " << numOfSets << " components" << endl;
        }
        cout << endl;
    }
    return 0;
}
