//
// Created by notoverflow on 12/04/2022.
//

#include "List.h"
#include "iostream"
#include "fstream"
using namespace std;

List::List() : head(nullptr), numberNode(0) {

}

void List::readFile(const string &fileName){

    ifstream f(fileName);
    f.seekg(0, ios::end);
    int size =(int) f.tellg() ;  // -1 pour enlever le \n
    char *buffer = new char[size];
    f.seekg(0, ios::beg);
    f.read(buffer, size);
    f.close();

    insertCharHead1(( char *)buffer, size);
}


//delete the lower value of the list and return it
Node *List::deleteMin(){
    Node *min = head;
    Node *previous = nullptr;
    Node *current = head;
    while (current != nullptr){
        if (current->number < min->number){
            min = current;
            previous = current->next;
        }
        current = current->next;
    }
    if (previous == nullptr){
        head = min->next;
    }
    else{
        previous=min->next;
    }
    return min;
}



//insert node head of list
void List:: insertHead(Node *value) {
    if(value == nullptr){
        return;
    }
    value->next = head;
    head = value;
    numberNode++;
}


//insert node with char and occurrence to head
void List::insertHead(char value, int occurrence) {
    Node *newNode = new Node(value, occurrence);
    newNode->next = head;
    head = newNode;
    numberNode++;
}

//insert tab of char and size
void List::insertCharHead1(char *tab, int size) {
    int occ[256] = {0};

    for (int i = 0; i < size; i++) {
        occ[(unsigned char) tab[i]]++;
    }

    for (int i = 0; i <= 255; i++) {
        if (occ[i] > 0) {
            insertHead((char)i, occ[i]);
        }
    }
}


//plus utilisé
void List::insertCharHead(unsigned char *tab, int size) {
    Node *ptr;
    bool find;
    for (int i = 0; i < size; i++) {
        ptr = head;
        find = false;
        while (!find and (ptr != nullptr) )  {
            if (ptr->c == tab[i]) {
                ptr->number++;
                find=true;
            } else {
                ptr = ptr->next;
            }
        }
        if (ptr == nullptr) {
            insertHead(tab[i],1);
        }
    }
}

//delete occurrence lower without arguments and return a ptr to this node
Node *List::deleteOccurrenceLower() {
    Node *tmp = head;
    Node *lowerNode = head;
    if (head == nullptr) {
        return head;
    }

    //search the lower node
    while (tmp != nullptr) {
        if (tmp->number < lowerNode->number) {
            lowerNode = tmp;
        }
        tmp = tmp->next;
    }

    if (head == lowerNode) {
        head = head->next;
    }else {
        tmp = head;

        while (tmp->next != lowerNode) {
            tmp = tmp -> next;

        }
        tmp->next = lowerNode->next;
    }

    numberNode--;


    return lowerNode;

}

//print list of char
void List::printList() {
    Node *tmp = head;
    while (tmp != nullptr) {
        cout << tmp->c << "("<< tmp->number << ") ";
        tmp = tmp->next;
    }
}