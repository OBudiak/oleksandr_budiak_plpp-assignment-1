#ifndef EDITINGTEXT_H
#define EDITINGTEXT_H

#include "functionality.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

class EditingText {
public:
    EditingText(Functionality& func);
    void addText();
    void addNewLine();
    void insertTextOnPosition();

private:
    Functionality& functionality;
};

#endif