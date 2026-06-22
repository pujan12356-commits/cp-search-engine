#include <iostream>
#include "Document.h"
#include "Parser.h"
#include "InvertedIndex.h"

using namespace std;

int main() {
    Document d1(0, "graph",
        "graph bfs dfs graph");

    Document d2(1, "tree",
        "binary search tree graph");

    InvertedIndex idx;

    idx.addDocument(d1);
    idx.addDocument(d2);

    auto res = idx.lookup("graph");

    cout << "graph:\n";

    for (int x : res)
        cout << x << " ";

    cout << "\n";
}