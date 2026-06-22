#include "Parser.h"
#include <iostream>

int main() {
    Parser p;

    auto tokens =
        p.parse("The graph is in the tree and the binary search");

    for(auto &x : tokens)
        cout << x << "\n";
}