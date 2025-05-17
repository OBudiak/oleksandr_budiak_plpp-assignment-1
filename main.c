#include <stdio.h>
#include <stdlib.h>

char *readline(int basicSize = 128) {
    size_t size = basicSize;
    size_t len = 0;
    char *buf = malloc(size);
    if (!buf) return NULL;

    int c;
    while ((c = fgetc(stdin)) != EOF && c != '\n') {
        if (len + 1 >= size) {
            size += basicSize;
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

void addText(char *text, char* input) {
    char *newText = readline(input);
    *input = newText;
    *text += input;
}

char chooseCommand(char command, char* text, char* input) {
    if (command == '1') {
        addText(text, input);
    }
    else if (command == '2') {
        addNewLine(text);
    }
    else if (command == '3') {
        saveInFile(text);
    }
    else if (command == '4') {
        loadFromFile(text);
    }
    else if (command == '5') {
        showText(text);
    }
    else if (command == '6') {
        insertTextOnPosition(text);
    }
    else if (command == '7') {
        searchText(text);
    }
    else if (command == '0') {
        return "0";
    }
    else {
        (void)printf("Invalid command, please try again\n");
        return "-1";
    }
    return command;
}

int main(void) {
    char input;
    char *command;
    char wholeText;
/*
    char addText();
    void addNewLine();
    void saveInFile();
    void loadFromFile();
    void showText();
    void insertTextOnPosition();
    void searchText();
*/
    while (1) {
        //*command = &readline();
        command = chooseCommand(&readline(), &wholeText, &input);
        if (command != '-1') {(void)printf("Command - %s\n", command);}
        if (command == '0') { break;}

        /*
        if (s) {
            (void)printf("You wrote %s\n", s);
            free(s);
        }
        */
    }
    return 0;
}