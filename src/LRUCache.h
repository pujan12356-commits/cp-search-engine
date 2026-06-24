#pragma once
#include<list>
#include<unordered_map>
#include<string>
#include<vector>

using namespace std;

class LRUCache{
     int cap;
     list<pair<string,vector<int>>> items;
     unordered_map<string,list<pair<string,vector<int>>>::iterator> mp;

public:
    LRUCache(int cap): cap(cap){}
    
    vector<int> get(string q){
        if(!mp.count(q)) return {};
        items.splice(items.begin(),items,mp[q]);
        return mp[q]->second;
    }

    void put(string q,vector<int> res){
        if(mp.count(q)){
            items.erase(mp[q]);
            mp.erase(q);
        }
        items.push_front({q,res});
        mp[q] = items.begin();
        if((int)items.size()>cap){
            mp.erase(items.back().first);
            items.pop_back();
        }
    }
};