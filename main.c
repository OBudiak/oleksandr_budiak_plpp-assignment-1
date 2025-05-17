#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iso646.h>
#include <string.h>

char *readline(void);
void addText(char **text);
void addNewLine(char **text);
void saveInFile(char **text);
void loadFromFile(char **text);
void showText(char **text);
void insertTextOnPosition(char **text);
void searchText(char **text);
char chooseCommand(char command, char **text);

char *readline(void) {
    size_t size = 64;
    size_t len  = 0;
    char* buf = malloc(size);
    if (!buf) return NULL;

    int c;
    while ((c = fgetc(stdin)) != EOF && c != '\n') {
        if (len + 1 >= size) {
            size += 64;
            char *newbuf = realloc(buf, size);
            if (!newbuf) {
                free(buf);
                return NULL;
            }
            buf = newbuf;
        }
        buf[len++] = c;
    }
    buf[len] = '\0';
    return buf;
}
void relocateMemory(char **text, char *newText, int x, int y) {
    size_t oldLen = 0;
    if (*text) {
        while ((*text)[oldLen]) oldLen++;
    }

    size_t addLen = 0;
    while (newText[addLen]) addLen++;

    char *tmp = realloc(*text, oldLen + addLen + 1);
    if (!tmp) {
        free(newText);
        return;
    }
    *text = tmp;

    size_t idx = 0, curX = 0, curY = 0;
    if (x >= 0 && y >= 0) {
        while (idx < oldLen && (curY < (size_t)y || curX < (size_t)x)) {
            if ((*text)[idx] == '\n') {
                curY++;
                curX = 0;
            } else {
                curX++;
            }
            idx++;
        }
        if (idx > oldLen) idx = oldLen;
    } else {
        idx = oldLen;
    }

    char *src  = *text + idx;
    char *dest = *text + idx + addLen;
    size_t moveLen = oldLen - idx + 1;

    if (dest > src) {
        size_t i = moveLen;
        while (i--) {
            dest[i] = src[i];
        }
    } else {
        for (size_t i = 0; i < moveLen; i++) {
            dest[i] = src[i];
        }
    }

    for (size_t i = 0; i < addLen; i++) {
        (*text)[idx + i] = newText[i];
    }

    free(newText);
}

void addText(char **text) {
    printf("Write a text: ");
    char *newText = readline();
    if (!newText) return;

    relocateMemory(text, newText, -1, -1);
}

void addNewLine(char **text) {
    char *newText = malloc(2);
    if (!newText) return;
    newText[0] = '\n';
    newText[1] = '\0';
    relocateMemory(text, newText, -1,  -1);
}

void saveInFile(char **text) { /* … */ (void)text; }
void loadFromFile(char **text) { /* … */ (void)text; }
void showText(char **text) { printf("%s\n", *text); }

int powerF(int power) {
    int result = 10;
    if (power <= 0) { return 1; }
    for (int i = 0; i < power; i++) {
        result *= 10;
    }
    return result;
}
void insertTextOnPosition(char **text) {

    printf("Write a position (x y) - ");
    char *newText = readline();
    if (!newText) return;
    int x = 0, y = 0, counter = 0, power = 0;
    char let;
    for (int i = 0; i < strlen(newText); i++) {
        let = newText[i];
        if (isdigit((unsigned char)let)) {
            if (counter == 0) {
                x += (let - '0')*powerF(power);
            } else if (counter == 1) {
                y += (let - '0')*powerF(power);
            } else if (counter == 2) {
                break;
            }
            power++;
            continue;
        }
        if (let == ' ') {
            power = 0;
            counter++;
        }
    }

    printf("Write a text: ");
    newText = readline();
    if (!newText) return;

    relocateMemory(text, newText, x, y);
}

void searchText(char **text){ /* … */ (void)text; }

char chooseCommand(char command, char **text) {
    if (command == '1') {
        addText(text);
    } else if (command == '2') {
        addNewLine(text);
    } else if (command == '3') {
        saveInFile(text);
    } else if (command == '4') {
        loadFromFile(text);
    } else if (command == '5') {
        showText(text);
    } else if (command == '6') {
        insertTextOnPosition(text);
    } else if (command == '7') {
        searchText(text);
    } else if (command == '0') {
        return '0';
    } else {
        printf("Invalid command, please try again\n");
        return (char)-1;
    }
    return command;
}

int main(void) {
    char *wholeText = NULL;
    while (1) {
        printf("Write a command - ");
        char *input = readline();
        if (!input) break;
        if (input[0] == '\0') { free(input); continue; }

        char command = input[0];
        printf("Command - %c\n", command);

        chooseCommand(command, &wholeText);
        free(input);

        if (command == '0') break;
    }
    free(wholeText);
    return 0;
}
