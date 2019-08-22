#include <iostream>
#include<map>
using namespace std; 
static int MAX = 20;
int num;
map<string,int> planet;

void freshMap(string s){
    //如果不包含的时候
    if(planet.count(s) == 0){
        planet[s] = planet.size();
    }
}
int main(){
    string src,dest;
    //退出的时候要清空map
    while((cin >> src >> dest >> num) && num != 0){
        //输入一个src，就应该转化为一个序列号。
        freshMap(src);freshMap(dest);
        
        
    }
    return 0;
}
