#include <stdio.h>
#include <stdlib.h>

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

void relocateMemory(char **text, char *newText) {
    size_t oldLen = 0;
    if (*text) {
        while ((*text)[oldLen] != '\0') {
            oldLen++;
        }
    }

    size_t addLen = 0;
    while (newText[addLen] != '\0') {
        addLen++;
    }

    char *tmp = realloc(*text, oldLen + addLen + 1);
    if (!tmp) {
        free(newText);
        return;
    }
    *text = tmp;

    for (size_t i = 0; i <= addLen; i++) {
        (*text)[oldLen + i] = newText[i];
    }

    free(newText);
}

void addText(char **text) {
    printf("Write a text: ");
    char *newText = readline();
    if (!newText) return;

    relocateMemory(text, newText);
}

void addNewLine(char **text) {
    char *newText = malloc(2);
    if (!newText) return;
    newText[0] = '\n';
    newText[1] = '\0';
    relocateMemory(text, newText);
}

void saveInFile(char **text) { /* … */ (void)text; }
void loadFromFile(char **text) { /* … */ (void)text; }
void showText(char **text) { printf("%s\n", *text); }
void insertTextOnPosition(char **text) { /* … */ (void)text; }
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
