#ifndef FUNCTIONALITY_H
#define FUNCTIONALITY_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

class Functionality {
public:
    Functionality();
    ~Functionality();
    char* readline();
    int powerF(int power);
    void relocateMemory(char* newText, int x, int y);
    void saveInFile();
    void loadFromFile();
    void searchText();
    void showText();

    void undoText();
    void redoText();

private:
    char* text;
};

#endif
