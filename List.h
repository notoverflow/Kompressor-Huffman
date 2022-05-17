//
// Created by notoverflow on 12/04/2022.
//

#ifndef HUFFMAN_LIST_H
#define HUFFMAN_LIST_H

#include "Node.h"
#include "string"

using namespace std;

class List {

    friend class Tree ;
public:
    List();


private:
    Node *head;
    int numberNode;


    void insertHead(Node *value);

    void readFile(const string &fileName);


    void insertHead(char value, int occurrence);

    void insertCharHead(unsigned char *tab, int size);
    void insertCharHead1(char *tab, int size);

    Node *deleteOccurrenceLower();

    Node *deleteMin();

    void printList();
};



#endif //HUFFMAN_LIST_H
