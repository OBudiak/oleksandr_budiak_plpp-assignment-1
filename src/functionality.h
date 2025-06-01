//
// Created by Fujitsu-H770 on 26.05.2025.
//

#ifndef FUNCTIONALITY_H
#define FUNCTIONALITY_H

int powerF(int power);
void relocateMemory(char **text, char *newText, int x, int y);
char *readline(void);
void searchText(char **text);
void saveInFile(char **text);
void loadFromFile(char **text);
void undoText(char **text);
void redoText(char **text);
void showText(char **text);


#endif //FUNCTIONALITY_H
