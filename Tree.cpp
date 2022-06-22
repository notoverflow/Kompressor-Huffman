//
// Created by notoverflow on 14/04/2022.
//

#include <valarray>
#include "Tree.h"
#include "List.h"
#include "Node.h"
#include "iostream"

using namespace std;

Tree::Tree() : r(nullptr) {

}

Tree::Tree( string name, bool printer){

    List list;

    list.readFile(name);


    if (printer) {
        cout << "**********************\n";
        cout << "***  List of char  ***\n";
        cout << "**********************\n\n\n";

        list.printList();
        cout << "\n\n\n\n\n";

    }
    createTree(list);

    r->printNode(0,r->depth());


}

Tree::~Tree() {
    delete r;

}

//create tree sorted with list
void Tree::createTree(List l) {

    if (l.numberNode > 1) {


        Node *lowerOne;
        Node *lowerTwo;


        lowerOne = l.deleteOccurrenceLower();
        lowerTwo = l.deleteOccurrenceLower();


        lowerOne->next = nullptr;
        lowerTwo->next = nullptr;

        Node *node;

        node = new Node(lowerOne->number + lowerTwo->number, '|', lowerOne, lowerTwo);
        l.insertHead(node);
        createTree(l);
    } else {
        r = l.head;
    }
}


void Tree::coding(){
    char code[40];
    int size = 0;
    r->visit(code, size, codes);

}

void Tree::printCodes(){
    for (int i = 0; i < 256; ++i) {
        if (codes[i] != "") {
            cout << (char) i << " " << codes[i] << "\n";
        }
    }

}

string Tree::coding(char *s, int N, double &compression){

    string tpm;

    for (int i = 0; i < N; ++i) {
        tpm += codes[(unsigned char) s[i]];
    }

    compression = (double)N * 8. / (double)tpm.length();
    compression /= 8;
    return tpm;
}


//
char *Tree::endCoding(string s, int &N) {

    if (s.length() % 8 == 0) {
        toComplete = 0;
        N = s.length() / 8;
    } else {
        toComplete = 8 - s.length() % 8;
        N = s.length() / 8 + 1;
        s += "00000000";
    }

    char *c = new char[N];

    //int index;
    for (int i = 0; i < N; ++i) {
        c[i] = 0;
        for (int j = 0; j < 8; ++j) {
            if (s[i * 8 + j] == '1') {
                c[i] += pow(2, 7 - j);
            }
        }
    }

    return c;

}

//save tree in file
void Tree::saveTree(ofstream &file) {

    file << toComplete;
    r->saveNode(file);

}


//decompress

void Tree::loadTree(unsigned char *c, int &index){
    index = 0;
    toComplete = c[index];

    index++;
    r = new Node(0);

    r->loadNode(c, index);
}

void Tree::goHead(){
    whereIAm = r;
}

bool Tree::goLeftRight(bool g) {
    if (g) {
        whereIAm = whereIAm->left;
    } else {
        whereIAm = whereIAm->right;
    }
    return whereIAm->left == nullptr;
}

void Tree::decoding(unsigned char *c, int N, int &index, string &s) {
    long int size = (long int) (N - index ) * 8 - toComplete;


    long int bit = 7;
    //s is empty
    s = "";
    unsigned char car;

    goHead();
    car = c[index];
    for (long int i = 0; i < size; ++i) {
        if (i % 8 == 0) {
            car = c[index++];
            bit = 7;
        }
        if(goLeftRight(!(car & (1 << bit)))) {
            //we are on the sheet
            s += whereIAm->c;
          //  cerr << whereIAm->c;
            goHead();
        }
        bit--;
    }

}

