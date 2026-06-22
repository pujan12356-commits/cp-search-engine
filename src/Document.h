#pragma once
#include<string>
#include<cctype>

using namespace std;

class Document{
public:
     int id;
     string title;
     string content;
     int wordCount;

     Document(int id, string title, string content): id(id), title(title), content(content){
        wordCount=0;
        bool inWord = false;
        for(char c: content){
            if(isspace(c)) inWord = false;
            else if(!inWord){
                wordCount++;
                inWord=true;
            }
        }
     }
};