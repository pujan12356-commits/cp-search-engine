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

//double tfidf(){
   
//}

//void printResults(){
   
//}

int main(){
   
     auto docs = loadDocuments("../documents");

    for(auto &doc : docs)
        cout << doc.id << " "
             << doc.title << " "
             << doc.wordCount << endl;
             
    InvertedIndex idx;

    for(auto &doc : docs)
        idx.addDocument(doc);
    cout << idx.getTotalDocs() << endl;         

}