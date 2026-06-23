#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Document.h"
#include "Parser.h"
#include "InvertedIndex.h"

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
    int count =0;
    for(auto &token: tokens) if(token==term) count++;
    double tf = (double)count/tokens.size();
    double idf = log((double)totalDocs/(docFreq+1));
    return tf*idf;
}

//void printResults(){
   
//}

int main() {
    auto docs = loadDocuments("../documents");
    InvertedIndex idx;
    for(auto &doc : docs)
        idx.addDocument(doc);
    Parser p;
    cout << tfidf(
        "graph",
        docs[2],
        idx.getTotalDocs(),
        idx.getDocFreq("graph"),
        p
    ) << endl;
}