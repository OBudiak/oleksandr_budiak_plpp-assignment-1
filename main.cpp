#include <iostream>
#include <cstring>
#include "src/functionality.cpp"
#include "src/editing_text.cpp"

using namespace std;

void instruction() {
    cout << endl << "Instruction:" << endl;
    cout << "Add text/new line - 1, 2" << endl;
    cout << "Save in/load from file - 3, 4" << endl;
    cout << "Show text - 5" << endl;
    cout << "Insert text by coordinates - 6" << endl;
    cout << "Search in text - 7" << endl;
    cout << "Delete text - 8" << endl;
    cout << "Cut/Paste/Copy text - 11, 12, 13" << endl;
    cout << "Insert with replacement - 14" << endl;
    cout << "Instruction - i" << endl;
    cout << "Exit - 0" << endl << endl;
}

int chooseCommand(int command, EditingText& editor, Functionality& func) {
    switch (command) {
        case 1:
            editor.addText();
            break;
        case 2:
            editor.addNewLine();
            break;
        case 3:
            func.saveInFile();
            break;
        case 4:
            func.loadFromFile();
            break;
        case 5:
            func.showText();
            break;
        case 6:
            editor.insertTextOnPosition();
            break;
        case 7:
            func.searchText();
            break;
        case 8:
            editor.deleteText();
            break;
        case 11:
            editor.cutText();
            break;
        case 12:
            editor.pasteText();
            break;
        case 13:
            editor.copyText();
            break;
        case 14:
            editor.insertWithReplacement();
            break;
        case 32759:
            instruction();
            break;
        case 0:
            return 0;
        default:
            cout << (int)'i';
            cout << "Invalid command, please try again" << endl;
            return -1;
    }
    return command;
}

int main() {
    cout << "Welcome to text Editor V0.1" << endl;
    instruction();

    Functionality func;
    EditingText editor(func);

    while (true) {
        cout << "Write a command - ";
        int count;
        char* input = func.readline();
        (void)sscanf(input, "%d", &count);
        if (!input) break;
        if (input[0] == '\0') {
            free(input);
            continue;
        }

        // char command = input[0];
        (void)chooseCommand(count, editor, func);
        free(input);

        if (count == 0) break;
    }
    return 0;
}
