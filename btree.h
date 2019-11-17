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

        Node<T>* findFather(Node<T>* nodeChild){
            Node<T>** pointer = &root;
            Node<T>* father = nullptr;
            while ( (*pointer) ) {
                if ( (*pointer) == nodeChild ) break;
                else{
                    father = *pointer;
                    change(pointer,nodeChild->keys[0]);
                }
            }
            return father;

        }

        void checkBTree(Node<T>** pointer){
            if( problemNode(*pointer) ){
                auto father = findFather((*pointer));
                auto save = father;
                if( father == nullptr ){
                    (*pointer)->split( father );

                    father->childs[0] =(*pointer);
                    root = father;
                }
                else (*pointer)->split( father );

                if(save != nullptr){
                    checkBTree(&(save));
                }
            }
        }

        void insertInBTree(Node<T>** pointer, T data){
            (*pointer)->insertData(data);
            checkBTree(pointer);
        }

        bool problemNode(Node<T>* Node){
            return !(Node->keys.size() <= degree - 1);
        }

        void printKeys(Node<T>* node){
            for (int i = 0; i <= node->keys.size(); ++i) {
                if(node->childs[i]) printKeys(node->childs[i]);
                if(i != node->keys.size()) cout<<node->keys[i]<<" ";
            }
        }

    public:
        BTree(unsigned int degree) : degree(degree){
            root = nullptr;
        };

        void insert(T data) {
            Node<T>** pointer = &root;
            if(!findBTree(pointer, data)){
                if( (*pointer) == nullptr ){
                    (*pointer) = new Node<T>(degree);
                }
                insertInBTree(pointer, data);
            }
        }

        void print(){
            printKeys(root);
        }

        T search(T data) {
            Node<T>** pointer = &root;
            if(findBTree(pointer,data)) return data;
            else throw new invalid_argument("No encontrado");
        }
        /*
        bool remove(int k) {}
        ~BTree();
         */
};

#endif