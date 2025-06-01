//
// Created by Fujitsu-H770 on 26.05.2025.
//

#ifndef EDITING_TEXT_H
#define EDITING_TEXT_H

#include <stddef.h>

// буфер тексту
void addText(char **text);
void addNewLine(char **text);
void insertTextOnPosition(char **text);
void insertWithReplacement(char **text);

void deleteText(char **text);
void copyText(char **text);
void pasteText(char **text);
void cutText(char **text);

#endif