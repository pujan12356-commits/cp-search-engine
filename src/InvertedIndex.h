#pragma once
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include "Document.h"
#include "Parser.h"

using namespace std;

class InvertedIndex{
    unordered_map<string,vector<int>> index;
    int totalDocs = 0;
public:
    void addDocument(const Document &doc){
        Parser p;
        auto tokens = p.parse(doc.content);
        for(auto &token: tokens){
            auto &list = index[token];
            if(list.empty() || list.back()!=doc.id) list.push_back(doc.id);
        }
        totalDocs++;
    }

    vector<int> lookup(const string &term){
        if(index.count(term)) return index[term];
        return {};
    }

    vector<int> andSearch(const string &a, const string &b){
        auto l1 = lookup(a), l2  = lookup(b);
        vector<int> result;
        set_intersection(l1.begin(),l1.end(),
                    l2.begin(),l2.end(),
                    back_inserter(result));
        return result;                   
    }

    vector<int> orSearch(const string &a, const string &b){
        auto l1 = lookup(a), l2  = lookup(b);
        vector<int> result;
        set_union(l1.begin(),l1.end(),
                    l2.begin(),l2.end(),
                    back_inserter(result));
        return result;                   
    }

    int getTotalDocs(){ return totalDocs; }

    int getDocFreq(const string &term){
        return index.count(term) ? index[term].size(): 0;
    }
};