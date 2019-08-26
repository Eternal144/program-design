#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
static int MAX_SIZE = 10000;
class UnionFindSet
{
    private:
    vector<int> parent; //代表子集树的根部
    vector<int> rank; //代表树的高度
    public:
    UnionFindSet(int n):parent(vector<int>(n)),
                        rank(vector<int>(n,0))
    {
        for(int i = 0; i < n; i++){
            parent[i] = i;
            // cout<<parent[i];
        }
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
    int findRoot(int x){
        return x == parent[x] ? x : (parent[x] = findRoot(parent[x]));
    }

    void unionBoth(int k1, int k2){
    //在这里保证只在根部拼接。减少时间复杂度。
        k1 = findRoot(k1);
        k2 = findRoot(k2);
      //在这里保证树拼接在高度低的那边，减少树的高度。
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
        int n = 0;
        vector<int> temp;
        for(int i = 0; i < parent.size(); i++){
            vector<int>::iterator it = find(temp.begin(),temp.end(),parent[i]);
            //如果没找到的话。
            if(it == temp.end()){
                temp.push_back(parent[i]);
            }
        }
        return temp.size();
    }
};
int main(){
    // 输入机器数量
    int number;
    while( (cin >> number) && number != 0){
        UnionFindSet *union_find_set = new UnionFindSet(number);
        char instruct; //指令
        while((cin >> instruct) && instruct != 'S'){
            int k1,k2; //接收机器
                cin >> k1 >> k2;
            if( instruct == 'C'){
                if(union_find_set->if_same(k1,k2)){ //如果找的到
                    cout << "yes" << endl;
                }else{//如果找不到
                    cout << "no" << endl;
                }
            }else if(instruct == 'I'){
                union_find_set->unionBoth(k1,k2);
            }
        }
        int numOfSets = union_find_set->getSetNumber();
        if(numOfSets == 1){
            cout << "The network is connected."<< endl;
        }else if(numOfSets == 0){
            cout << "No computer" << endl;
        }else{
            cout << "There are" << numOfSets << " components" << endl;
        }
        cout << endl;
    }
    return 0;
}