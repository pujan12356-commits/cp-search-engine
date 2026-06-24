#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Document.h"
#include "Parser.h"
#include "InvertedIndex.h"
#include "LRUCache.h"
#include "SpellCorrector.h"

using namespace std;

vector<Document> loadDocuments(const string &folder){
    vector<Document> docs;
    int id=0;
    vector<string> files = {"binary_search","dp","graph","sorting","trees"};
    for(auto &name: files){
        string path = folder + "/" + name + ".txt";
        ifstream file(path);
        if(!file.is_open()) continue;
        string content((istreambuf_iterator<char>(file)),istreambuf_iterator<char>());
        docs.push_back(Document(id++,name,content));
    }
    return docs;
}

double tfidf(const string &term,const Document &doc,int totalDocs,int docFreq,Parser &parser){
    auto tokens = parser.parse(doc.content);
    if(tokens.empty()) return 0;
    int count =0;
    for(auto &token: tokens) if(token==term) count++;
    double tf = (double)count/tokens.size();
    double idf = log((double)totalDocs/(docFreq+1));
    return tf*idf;
}

void printResults(const vector<int> &ids, const vector<Document> &docs){
     if(ids.empty()){
        cout<<"No results found."<<endl;
        return;
     }
     for(int id: ids){
        cout<<"->"<<docs[id].title<<".txt"<<endl;
     }
}

int main(){
    auto docs = loadDocuments("../documents");
    InvertedIndex idx;
    for(auto &doc: docs) idx.addDocument(doc);
    vector<string> vocabulary = {"graph","dfs","bfs","tree",
                            "sorting","binary","search","dp"};
    cout<<"CP Search Engine-"<<docs.size()<<" documents indexed."<<endl;
    cout<<"Ready for queries"<<endl;
    cout << "Commands: <term>  |  "
         << "<term> AND <term>  |  "
         << "<term> OR <term>  |  quit" << endl;
    cout << string(50, '-') << endl;
    string query;
    Parser p;
    LRUCache cache(5);
    SpellCorrector sc;

    while(true){
        cout<<"\nSearch: ";
        getline(cin,query);
        if(query=="quit") break;
        auto andPos = query.find(" AND ");
        auto orPos = query.find(" OR ");
        
        if(andPos!=string::npos){
            string a = query.substr(0,andPos);
            string b = query.substr(andPos+5);
            auto results = idx.andSearch(a,b);
            printResults(results,docs);
        }
        else if(orPos!=string::npos){
            string a = query.substr(0,orPos);
            string b = query.substr(orPos+4);
            auto results = idx.orSearch(a,b);
            printResults(results,docs);
        }
        else{
            auto results = cache.get(query);
            if(!results.empty()) cout<<"CACHE HIT"<<endl;
            else{
                cout<<"CACHE MISS"<<endl;
                results = idx.lookup(query);
                if(results.empty()){
                   string suggestion = sc.suggest(query,vocabulary);
                   if(!suggestion.empty()) cout<<"Did you mean: "<<suggestion<<" ?"<<endl;
                   else{
                    cout<<"No results found."<<endl;
                   }
                   continue;
                }
                cache.put(query,results);
            }
            vector<pair<double,int>> scored;
            int docFreq = idx.getDocFreq(query);
            for(int id: results){
                double score = tfidf(query,docs[id],docs.size(),docFreq,p);
                scored.push_back({score,id});
            }
            sort(scored.rbegin(), scored.rend());
            for (auto& [score, id] : scored)
                cout << "  → " << docs[id].title
                     << ".txt (score: "
                     << score << ")" << endl;
        }
    }
    return 0;
}