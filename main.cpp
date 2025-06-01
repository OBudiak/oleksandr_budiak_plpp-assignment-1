#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "src/functionality.cpp"
#include "src/editing_text.cpp"

using namespace std;

void instruction() {
    cout << "Welcome to text Editor V0.1\n";
    cout <<("\nInstruction:\n");
    cout <<("Add text/new line - 1, 2\n");
    cout <<("Save in/load from file - 3, 4\n");
    cout <<("Show text - 5\n");
    cout <<("Insert text by coordinates - 6\n");
    cout <<("Search in text - 7\n");
    cout <<("Exit - 0\n\n");
}


int chooseCommand(char command, char **text) {
    switch (command) {
        case '1':
            addText(text);
            break;
        case '2':
            addNewLine(text);
            break;
        case '3':
            saveInFile(text);
            break;
        case '4':
            loadFromFile(text);
            break;
        case '5':
            showText(text);
            break;
        case '6':
            insertTextOnPosition(text);
            break;
        case '7':
            searchText(text);
            break;
        case '0':
            return 0;
        default:
            cout << "Invalid command, please try again\n" << endl;
            return -1;
    }
    return command;
}


int main(void) {
    instruction();

    char *wholeText = NULL;
    while (1) {
        printf("Write a command - ");
        char *input = readline();
        if (!input) break;
        if (input[0] == '\0') { free(input); continue; }

        char command = input[0];
        // printf("Command - %c\n", command);

        (void)chooseCommand(command, &wholeText);
        free(input);

        if (command == '0') break;
    }
    free(wholeText);
    return 0;
}
