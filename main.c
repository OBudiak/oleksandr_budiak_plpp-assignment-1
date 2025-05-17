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

void choosCommand(char command) {
    if (command == '1') {
        addText();
    }
    else if (command == '2') {
        addNewLine();
    }
    else if (command == '3') {
        saveInFile();
    }
    else if (command == '4') {
        loadFromFile();
    }
    else if (command == '5') {
        showText();
    }
    else if (command == '6') {
        insertTextOnPosition();
    }
    else if (command == '7') {
        searchText();
    }
    else {
        (void)printf("Invalid command, please try again\n");
    }
    return;
}

int main(void) {
    printf("Command - \n");
    char *s = readline();
    if (s) {
        printf("You wrote %s\n", s);
        free(s);
    }
    return 0;
}