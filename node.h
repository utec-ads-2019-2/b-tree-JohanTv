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
    Node<T>* father;

    bool isLeaf;

    int posCorrect(T data){
        int pos = 0;
        size_t n = keys.size();

        for (size_t i = 0; i < n; ++i) {
            if(data > keys[i]) ++pos;
            else break;
        }
        return pos;
    }

    void posCorrectChilds(T data1, T data2, Node<T>* newNode){
        auto n1 = posCorrect(data1);
        this->insertData(data1);
        auto n2 = posCorrect(data2);
        swap(this->childs[n1],this->childs[n2]);
        this->childs[n2] = newNode;
    }

    public: 
        Node(unsigned int size, Node<T>* father, bool isLeaf = true) : size(size), isLeaf(isLeaf) {
            this->father = father;
            childs.push_back(nullptr);
        }
        Node(unsigned int size,Node<T>* father, T data, bool isLeaf = true) : size(size), isLeaf(isLeaf) {
            this->father = nullptr;
            childs.push_back(nullptr);

            keys.push_back(data);
            childs.push_back(nullptr);
        }
        Node(unsigned int size,Node<T>* father, vector<T> otherKeys, vector<Node<T>*> otherChilds, bool isLeaf = true) : size(size), isLeaf(isLeaf) {
            this->father = father;
            keys.insert(keys.begin(),otherKeys.begin(),otherKeys.end());
            childs.insert(childs.begin(),otherChilds.begin(),otherChilds.end());
        }

        void insertData(T data){
            keys.push_back(data);
            sort(keys.begin(),keys.end());

            auto n = posCorrect(data);
            childs.insert(childs.begin()+n, nullptr);

        }

        void split(){
            if(father == nullptr) father = new Node<T>(size, nullptr, false);

            size_t mid = keys.size()/2;
            vector<T> vectorKeys(keys.begin()+(mid+1), keys.end());
            vector<Node<T>*> vectorChilds(childs.begin()+(mid+1), childs.end());

            Node<T>* newNode = new Node<T>(size, father, vectorKeys, vectorChilds);

            keys.erase(keys.begin()+(mid+1),keys.end());
            childs.erase(childs.begin()+(mid+1),childs.end());

            if(newNode->childs[0] != nullptr) newNode->isLeaf = false;

            father->posCorrectChilds(keys.back(),newNode->keys[0], newNode);
            keys.pop_back(); //split complete
        }


        //void setState(bool isLeaf){ this->isLeaf = isLeaf; }

    friend class BTree<T>;
};

#endif