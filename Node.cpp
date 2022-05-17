//
// Created by notoverflow on 12/04/2022.
//

#include "Node.h"
#include "iostream"

using namespace std;


Node::Node(int val) : number(val), next(nullptr), left(nullptr), right(nullptr) {

}

Node::Node(char c, int i) {
    this->c = c;
    this->number = i;
    this->left = nullptr;
    this->right = nullptr;
}



Node::Node(int number, unsigned char c, Node *left, Node *right) : number(number), c(c), left(left), right(right) {

}

Node::Node(int number, unsigned char c) : number(number), c(c),left(nullptr), right(nullptr) {}



/**
 * insert a val in the tree
 * @param val value to insert
 */
void Node::insert(int val) {
    if (val < number) {
        if (left != nullptr) {
            left->insert(val);
        } else {
            left = new Node(val);
        }
    } else {
        if (right != nullptr) {
            right->insert(val);
        } else {
            right = new Node(val);
        }
    }
}


void Node::print() {
    std::cout << c << number<<std::endl;
    if (left != nullptr) {
        cout << "/";
        left->print();
    }
    if (right != nullptr) {
        cout << "\t\\";

        right->print();
    }
}


void Node::printNode(int niv, int nivMax) {

    if (left != nullptr) {
        left->printNode(niv + 1, nivMax);
        for (int i = 0; i < niv-1; ++i) {
            cout << "         ";
        }
        if (niv != 0) {
            cout << "|--------";
        }
        cout << c << "\n";
        right->printNode(niv + 1, nivMax);
    } else {
        for (int i = 0; i < niv-1; i++) {
            cout << "         ";
        }
        if (niv != 0) {
            cout << "|--------";
        }
        cout << c << "\n";
    }

}

//return depth of the node
int Node::depth() {
    int leftDepth = 0;
    int rightDepth = 0;

    if (left != nullptr) {
        leftDepth = left->depth();
    }

    if (right != nullptr) {
        rightDepth = right->depth();
    }

    return leftDepth>rightDepth ? leftDepth+1 : rightDepth+1;
}

void Node::visit(char *code, int size, string *codes) {

    if (left != nullptr) {
        code[size] = '0';
        left->visit(code, size + 1, codes);
    }
    if (right != nullptr) {
        code[size] = '1';
        right->visit(code, size + 1, codes);
    }
    if (left == nullptr && right == nullptr) {
        codes[(int)c] = string(code,size);
    }

}

void Node::saveNode(ofstream &file) {
    if (left != nullptr) {
        file << 'N';
        left->saveNode(file);
        if (right!= nullptr) {
            right->saveNode(file);
        }
    } else {
        file << 'S';
        file << c;
    }



}

//decompress

void Node::loadNode(unsigned char *cTab, int &index){

    if (cTab[index++] == 'N') {
        left = new Node(0);
        left->loadNode(cTab, index);
        right = new Node(0);
        right->loadNode(cTab, index);
    } else {
        c = cTab[index];
        index++;
    }
}