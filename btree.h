#ifndef BTREE_H
#define BTREE_H

#include "node.h"
#include <algorithm>
#include <list>
template <typename T>
class BTree{
    private:
        Node<T>* root;
        unsigned int degree;


        void change(Node<T>**& pointer, T data, size_t& pos){
            pos = 0;
            size_t n = (*pointer)->keys.size();

            for (size_t i = 0; i < n; ++i) {
                if(data > (*pointer)->keys[i]) ++pos;
                else break;
            }
            pointer = &((*pointer)->childs[pos]);
        }

        bool findBTree(Node<T>**& father, T data,size_t& pos){
            Node<T>** child = &root;
            //Node<T>* prev = nullptr;
            while ( (*child) ) {
                if (binary_search((*child)->keys.begin(), (*child)->keys.end(), data)) return true;

                if ((*child)->isLeaf) break;
                else{
                    father = child;
                    change(child,data,pos);
                    /*prev = child;
                    change(child, data, pos);
                    if(child != nullptr) father = prev;
                */
                }
            }
            return false;
        }

    public:
        BTree(unsigned int degree) : degree(degree){
            root = nullptr;
        };

        bool isGood(Node<T>* Node){
            return Node->isLeaf;
        }

        void insertInBTree(Node<T>** pointer, T data, size_t pos){

            if( pointer == nullptr ){
                root->insertData(data);
                if(!isGood(root)){

                    int mid = root->keys.size()/2;
                    T value = root->keys[mid];

                    Node<T>* newFather = new Node<T>(degree, value, false);
                    vector<T> otherVector(root->keys.begin()+(mid+1),root->keys.end());

                    Node<T>* otherChild = new Node<T>(degree, otherVector, true);
                    root->keys.erase(root->keys.begin()+mid,root->keys.end());

                    root->isLeaf = true;

                    newFather->childs[0] = root;
                    newFather->childs[1] = otherChild;
                    root = newFather;
                }
            }
            else{
                (*pointer)->childs[pos]->insertData(data);

            }

        }

        void insert(T data) {
            Node<T>** pointer = nullptr;
            size_t pos = 0;

            if(!findBTree(pointer, data, pos)){
                if( pointer == nullptr ){
                    if (root == nullptr ) root = new Node<T>(degree);
                }
                insertInBTree(pointer, data, pos);
            }
        }
        /*
        T search(T data) {

        }

        bool remove(int k) {

        }

        void print() {
        }

        ~BTree();*/
};

#endif