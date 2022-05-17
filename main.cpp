#include <iostream>
#include <fstream>
#include "Tree.h"

using namespace std;

bool is_readable(const std::string &file) {
    ifstream filee(file.c_str());
    return !filee.fail();
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

void compress(const string& fileIn, const string& fileOut, bool printer) {


    double compress;
    string coder;
    //int ln
    int size;
    char *code;
    //int ti

    ifstream f(fileIn);
    f.seekg(0, ios::end);
    size = (int) f.tellg();
    char *text = new char[size];
    f.seekg(0, ios::beg);
    f.read(text, size);
    f.close();


    Tree tree(fileIn,printer);

    tree.coding();
    if (printer) {
        tree.printCodes();
    }

    string myString = tree.coding(text, size, compress);
    if (printer) {
        cout << myString<<"\n";
        cout << compress;
    }

    char *compressed;
    int lenght;
    compressed = tree.endCoding(myString, lenght);


    ofstream fout(fileOut);
    tree.saveTree(fout);
    for (int i = 0; i <lenght; ++i) {
        fout << compressed[i];
    }
    fout.close();
}

void decompress(const string& fileIn, const string& fileOut, bool printer) {

    int size;
    int index=0;


    ifstream f(fileIn);
    f.seekg(0, ios::end);
    size = (int) f.tellg();
    char *text = new char[size];
    f.seekg(0, ios::beg);
    f.read(text, size);
    f.close();

    string s;

    Tree tree;

    tree.loadTree((unsigned char *)text, index);

    if (printer) {
        tree.r->printNode(0,tree.r->depth());

    }

    tree.decoding((unsigned char *) text, size, index, s);

    if (printer) {
        cout << "decompressed string : \n\n";
        cout << s;
    }

    ofstream out(fileOut);
    out << s;
    out.close();
}



int main(int argc, char *argv[]) {

    switch (str2int(argv[1])) {

        case str2int("-c"):
            compress(argv[2], argv[3], false);
            break;

        case str2int("-cv"):
            compress(argv[2], argv[3], true);
            break;

        case str2int("-d"):
            decompress(argv[2], argv[3], false);
            break;

        case str2int("-dv"):
            decompress(argv[2], argv[3], true);
            break;

        default:
            cerr << "invalid command";
            break;

    }


    return 0;
}
