#include <iostream>

#include "btree.h"
#include <ctime>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
    BTree<int> MiArbol(4);
    srand(time(nullptr));
    int n = 35;
    for(int i = 1; i <= n; ++i){
        int value = 1+rand()%200;
        cout << value << " ";
        MiArbol.insert(value);
    }
    cout << endl;
    MiArbol.print();
    /*MiArbol.insert(45);
    MiArbol.insert(75);
    MiArbol.insert(100);
    MiArbol.insert(36);
    MiArbol.insert(120);
    MiArbol.insert(70);
    MiArbol.insert(11);
    MiArbol.insert(111);
    MiArbol.insert(47);
    MiArbol.insert(114);*/
    return 0;
}