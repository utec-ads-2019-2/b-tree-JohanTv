#include <iostream>

#include "btree.h"

using namespace std;

int main(int argc, char *argv[]) {
    BTree<int> MiArbol(4);
    MiArbol.insert(12);
    MiArbol.insert(21);
    MiArbol.insert(42);
    MiArbol.insert(47);
    MiArbol.insert(70);
}