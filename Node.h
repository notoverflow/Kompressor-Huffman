//
// Created by notoverflow on 12/04/2022.
//

#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H
#import "fstream"

using namespace std;
class Node {
    friend class Tree;
    friend class List;
    Node(char c, int i);

    friend class Tree;

    friend class List;

public:
    Node(int number, unsigned char c, Node *left, Node *right);

    Node(int val);

    Node(int number, unsigned char c);



    void print();

    void printNode(int niv, int nivMax);
    int depth();
private:
    int number;
    unsigned char c;

    Node *left;

    Node *right;

    Node *next;

    void insert(int val);

    void visit(char *code, int size, string *codes);

    void saveNode(ofstream &file);

    void loadNode(unsigned char *cTab, int &index);
};


#endif //HUFFMAN_NODE_H
