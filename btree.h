#ifndef BTREE_H
#define BTREE_H

#include "node.h"
#include <algorithm>
#include <list>
template <typename T>
class BTree{
    private:
        Node<T>* root;
        size_t degree;


        void change(Node<T>**& pointer, T data){
            size_t pos = 0;
            size_t n = (*pointer)->keys.size();

            for (size_t i = 0; i < n; ++i) {
                if(data > (*pointer)->keys[i]) ++pos;
                else break;
            }
            pointer = &((*pointer)->childs[pos]);
        }

        bool findBTree(Node<T>**& pointer, T data){
            while ( (*pointer) ) {
                if (binary_search((*pointer)->keys.begin(), (*pointer)->keys.end(), data)) return true;

                if ((*pointer)->isLeaf) break;
                else change(pointer,data);
            }
            return false;
        }

        void insertInBTree(Node<T>** pointer, T data){
            (*pointer)->insertData(data);
            checkBTree(pointer);
        }

        void checkBTree(Node<T>** pointer){
            if(! isGood(*pointer) ){
                auto save = *pointer;

                if( (*pointer)->father == nullptr ){
                    (*pointer)->split();

                    save->father->childs[0] = save;
                    root = save->father;
                }
                else (*pointer)->split();

                if(save->father != nullptr) checkBTree(&(save->father));
            }
        }

        bool isGood(Node<T>* Node){
            return Node->keys.size() <= degree - 1;
        }



    public:
        BTree(unsigned int degree) : degree(degree){
            root = nullptr;
        };

        void insert(T data) {
            Node<T>** pointer = &root;
            if(!findBTree(pointer, data)){
                if( (*pointer) == nullptr ){
                    (*pointer) = new Node<T>(degree, nullptr);
                }
                insertInBTree(pointer, data);
            }
        }

        void print() {


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