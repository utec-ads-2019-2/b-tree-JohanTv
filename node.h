#ifndef NODE_H
#define NODE_H

template <typename T>
class BTree;

#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class Node {
    unsigned int size;

    vector<T> keys;
    vector<Node<T>*> childs;

    bool isLeaf;

    public: 
        Node(unsigned int size, bool isLeaf = true) : size(size), isLeaf(isLeaf) {
            keys.reserve(size-1);
            childs.resize(size, nullptr);
        }
        Node(unsigned int size, T data, bool isLeaf = true) : size(size), isLeaf(isLeaf) {
            keys.reserve(size-1);
            childs.resize(size, nullptr);
            keys.push_back(data);
        }
        Node(unsigned int size, vector<T> otherKeys, bool isLeaf = true) : size(size), isLeaf(isLeaf) {
            keys.reserve(size-1);
            childs.resize(size, nullptr);
            keys.insert(keys.begin(),otherKeys.begin(),otherKeys.end());
        }

        void insertData(T data){
            keys.push_back(data);
            sort(keys.begin(),keys.end());
        }

        //void setState(bool isLeaf){ this->isLeaf = isLeaf; }

    friend class BTree<T>;
};

#endif