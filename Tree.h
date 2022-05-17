//
// Created by notoverflow on 14/04/2022.
//

#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include "Node.h"
#include "string"
#include "List.h"

class Tree {


public:
    Tree();
    Tree(string name, bool printer);
    ~Tree();

    Node *r;

    Node *whereIAm;

    void coding();
    string coding(char *s, int N, double &compression);

    void printCodes();

    char *endCoding(string s, int &N);
    void saveTree(ofstream &file);

    void loadTree(unsigned char *c, int &index);

    void decoding(unsigned char *c, int N, int &index, string &s);

private:

    unsigned char toComplete;

    std::string codes[256];

    void createTree(List l);

    void goHead();

    bool goLeftRight(bool g);
};


#endif //HUFFMAN_TREE_H
