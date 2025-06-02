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

    void deleteText(int line, int index, int count);
    void insertWithReplacement(int line, int index, const char* newText);
    void copyText(int line, int index, int count);
    void cutText(int line, int index, int count);
    void pasteText(int line, int index);

    void undoText();
    void redoText();

private:
    char* text;
    char* clipboard;

    size_t getGlobalIndex(int line, int index);
};

#endif
