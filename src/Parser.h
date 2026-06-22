#pragma once
#include<string>
#include<set>
#include<vector>
#include<cctype>

using namespace std;

class Parser{
     set<string> stopWords = {
        "a","an","the","is","in","of","to",
        "and","or","for","with","it","as",
        "at","by","from","on","are","be","this"
     }; 
public:
     vector<string> parse(string text){
         vector<string> tokens;
         string token;
         for(char c: text){
            if(isalnum(c)) token+=tolower(c);
            else if(!token.empty()){
                if(!stopWords.count(token))
                    tokens.push_back(token);
                token = "";
            }
         }
         if(!token.empty() && !stopWords.count(token)) tokens.push_back(token);
         return tokens;
     }
};
