//
//  main.cpp
//  shopping
//
//  Created by Sisi Lee on 2019/8/25.
//  Copyright © 2019 Sisi Lee. All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>
#include <set>
using namespace std;
map<string,int> goods;

struct Conpon{ //建一个记录优惠券的结构体。包含所有类型。
    map<string,int> goodsN; //这个优惠券里面的每个商品对应的数量。
    float buyP; //购买这张优惠券所需要花的钱。
};

class Shop{
private:
    int types;
    int id; //用来唯一标识参与优惠券活动的商品。
    float spendAll;
    vector<Conpon> conpons; //储存了所有优惠券信息。
    vector<vector<vector<vector<vector<vector<int> > > > > >  dp;
    vector<string> goodsName;//所有商品名字。下标代表id，值为商品名称。
    map<string,int> combo; //参与优惠的商品集合。 string 为商品名称。 int为id。
    vector<int> numbers; //下标代表优惠商品。值代表数量。
    map<string,int> restGoods; //不参与优惠的商品。key为商品名称，value为数量。
public:
    Shop(int n){
        types = n;
        id = 0;
        spendAll = 0;
    }
    
    void getCoupons(){
        goodsName.resize(6,"");
        string s; //商品名称
        int n; //优惠券内商品的数量。
        float p;
        for(int i=0; i<types; i++){
            int involve;
            cin>>involve;
            for(int j=0; j<involve; j++){
                cin>>s>>n;
                conpons[i].goodsN[s] = n;
                map<string,int>::iterator it = combo.begin();
                while(it != combo.end() && it->first != s){
                    //没找到，则添加该优惠商品进这个集合。
                    it++;
                }
                if(it == combo.end()){
                    goodsName[id]=s;
                    combo[s] = id++;
                    //每一个被涉及的h商品都有一个唯一的id。
                }
            }
            cin>>p;
            conpons[i].buyP = p;
        }
        
    }
    //几种商品几维数组？太麻烦了。算了吧。。。。虽然可以多些点。
    void init(){
        conpons.resize(types);
        numbers.resize(6,0); //最多六种优惠商品。
    }
    
    void getBuying(){ //输入要购买的东西。
        // cout<<"gg0";
        int buyN;
        cin>>buyN;
        string s; //商品名称
        int n; //需要购买的商品数量
        map<string,int>::iterator it;
        for(int i=0; i<buyN; i++){ //获取想要购买的商品和数量。
            cin>>s>>n;
            it = combo.find(s);
            if(it != combo.end()){ //找到了，说明是优惠商品。
                numbers[combo[s]] = n;
            }else{ //说明不是优惠商品
                restGoods[s] = n;
            }
        }
        vector<vector<vector<vector<vector<int> > > > >  temp0;
        vector<vector<vector<vector<int> > > >  temp1;
        vector<vector<vector<int> > >  temp2;
        vector<vector<int> >  temp3;
        vector<int>  temp4;
        
        //初始容量都为0
        temp4.resize(6,0);
        temp3.resize(6,temp4);
        temp2.resize(6,temp3);
        temp1.resize(6,temp2);
        temp0.resize(6,temp1);
        dp.resize(6,temp0);
        //cout<<"gg0";
    }
    
    int getMin(vector<int>goodsNum){
        float min = 0;
        for(int i = 0;i < goodsNum.size();++i){
            min+=goodsNum[i]*goods[goodsName[i]];
        }
        for(int j = 0;j < conpons.size();++j){ //对于每一种优惠券。
            Conpon conpon=conpons[j];
            bool isEnough=true;
            for(int i = 0;i < goodsNum.size();++i){
                if(goodsNum[i]-conpon.goodsN[goodsName[i]]<0){ //容量满足优惠券所有数量。
                    isEnough=false;
                    break;
                }
            }
            if(isEnough){
                float cost= conpon.buyP;
                int n0 = goodsNum[0]-conpon.goodsN[goodsName[0]];
                int n1 = goodsNum[1]-conpon.goodsN[goodsName[1]];
                int n2 = goodsNum[2]-conpon.goodsN[goodsName[2]];
                int n3 = goodsNum[3]-conpon.goodsN[goodsName[3]];
                int n4 = goodsNum[4]-conpon.goodsN[goodsName[4]];
                int n5 = goodsNum[5]-conpon.goodsN[goodsName[5]];

                if(n0+n1+n2+n3+n4+n5==0){
                    dp[goodsNum[0]][goodsNum[1]][goodsNum[2]][goodsNum[3]][goodsNum[4]][goodsNum[5]]=cost;
                    return cost;
                    
                }
                if(dp[n0][n1][n2][n3][n4][n5]==0){
                    vector<int> t;
                    t.resize(6,0);
                    t[0]=n0;
                    t[1]=n1;
                    t[2]=n2;
                    t[3]=n3;
                    t[4]=n4;
                    t[5]=n5;
                    getMin(t);
                }
                
                float fee = dp[n0][n1][n2][n3][n4][n5]+cost;
                
                if(fee<min){
                    min=fee;
                }
                
            }
        }
        dp[goodsNum[0]][goodsNum[1]][goodsNum[2]][goodsNum[3]][goodsNum[4]][goodsNum[5]] =min;
        return min;
    }
    
    int getRest(){ //在这里返回没有优惠券的商品的价钱合。
        float a = 0;
        map<string,int>::iterator it = restGoods.begin();
        while(it != restGoods.end()){
            a += goods[it->first]*(it->second);
            it++;
        }
        return a;
    }
    
    //在这里打印最终花费的钱。
    void shopMain(){
        init();
        getCoupons();
        getBuying();
        spendAll = getMin(numbers) + getRest();
        cout<<"最少花费"<<spendAll<<"元钱";
    }
};

int main(int argc, const char * argv[]) {
    freopen("aaa.txt", "r", stdin);
    ios::sync_with_stdio(false);
    int num;
    cin>>num; //输入在售不同商品数量；
    for(int i=0; i<num; i++){
        string name;
        int price;
        cin>>name>>price;
        goods[name] = price;
    }
    int couponType; //优惠券种类数量
    while(cin>>couponType && couponType!=-1){
        Shop* shop = new Shop(couponType);
        cout<<"haha"<<endl;
        shop->shopMain();
    }
    return 0;
}
