#include <iostream>

#include "btree.h"

using namespace std;

int main(int argc, char *argv[]) {
    BTree<int> MiArbol(4);
    int n = 20;
    for(int i = 0; i < n; ++i){
        MiArbol.insert(2*i);
    }
    cout<<"Holi"<<endl;
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
}