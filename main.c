#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iso646.h>
#include <string.h>

char *readline(void);
void addText(char **text);
void addNewLine(char **text);
void saveInFile(char **text);
void loadFromFile();
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
    (*text)[idx + addLen] = '\0';

    free(newText);
}

void addText(char **text) {
    printf("  -Add text-  \n");
    printf("Write a text: ");
    char *newText = readline();
    if (!newText) return;

    relocateMemory(text, newText, -1, -1);
}

void addNewLine(char **text) {
    printf("  -Add new line-  \n");
    char *newText = malloc(2);
    if (!newText) return;
    newText[0] = '\n';
    newText[1] = '\0';
    relocateMemory(text, newText, -1,  -1);
}

void saveInFile(char **text) {
    printf("  -Save in file-  \n");
    FILE* file;
    printf("Enter file name: ");
    char* fileName = readline();
    file = fopen(fileName, "w");
    if (file != NULL)
    {
        fputs(*text, file);
        fclose(file);
    }
}
void loadFromFile() {
    printf("  -Load from file-  \n");
    printf("Enter file name: ");
    char *fileName = readline();
    if (!fileName) return;

    FILE *file = fopen(fileName, "r");
    free(fileName);
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    size_t size = 128, len = 0;
    char *buf = malloc(size);
    if (!buf) {
        fclose(file);
        return;
    }

    int c;
    while ((c = fgetc(file)) != EOF) {
        if (len + 1 >= size) {
            size *= 2;
            char *tmp = realloc(buf, size);
            if (!tmp) {
                free(buf);
                fclose(file);
                return;
            }
            buf = tmp;
        }
        buf[len++] = (char)c;
    }
    buf[len] = '\0';

    fclose(file);
    printf("%s\n", buf);
    free(buf);
}
void showText(char **text) { printf("  -Show text-  \n"); printf("%s\n", *text); }

int powerF(int power) {
    int result = 10;
    if (power <= 0) { return 1; }
    for (int i = 0; i < power; i++) {
        result *= 10;
    }
    return result;
}
void insertTextOnPosition(char **text) {
    printf("  -Insert text by coordinate-  \n");
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

void searchText(char **text) {
    printf("  -Search in text-  \n");
    printf("Enter text: ");
    char *phrase = readline();
    if (!phrase || phrase[0] == '\0') {
        printf("Empty search string\n\n");
        free(phrase);
        return;
    }
    if (!*text) {
        printf("Text is empty\n\n");
        free(phrase);
        return;
    }

    char *t = *text;
    int line = 0, col = 0, found = 0;
    size_t len_text   = strlen(t);
    size_t len_phrase = strlen(phrase);

    for (size_t i = 0; i < len_text; i++) {
        if (t[i] == '\n') {
            line++;
            col = 0;
            continue;
        }
        if (i + len_phrase <= len_text &&
            strncmp(&t[i], phrase, len_phrase) == 0)
        {
            printf("\"%s\" - %d %d\n", phrase, line, col);
            found = 1;
        }
        col++;
    }

    if (!found) {
        printf("\"%s\" was not found\n", phrase);
    }
    printf("\n");
    free(phrase);
}


char chooseCommand(char command, char **text) {
    if (command == '1') {
        addText(text);
    } else if (command == '2') {
        addNewLine(text);
    } else if (command == '3') {
        saveInFile(text);
    } else if (command == '4') {
        loadFromFile();
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
    printf("Welcome to text Editor V0.1\n");
    printf("\nInstruction:\n");
    printf("Add text/new line - 1, 2\n");
    printf("Save in/load from file - 3, 4\n");
    printf("Show text - 5\n");
    printf("Insert text by coordinates - 6\n");
    printf("Search in text - 7\n");
    printf("Exit - 0\n\n");


    char *wholeText = NULL;
    while (1) {
        printf("Write a command - ");
        char *input = readline();
        if (!input) break;
        if (input[0] == '\0') { free(input); continue; }

        char command = input[0];
        // printf("Command - %c\n", command);

        chooseCommand(command, &wholeText);
        free(input);

        if (command == '0') break;
    }
    free(wholeText);
    return 0;
}
