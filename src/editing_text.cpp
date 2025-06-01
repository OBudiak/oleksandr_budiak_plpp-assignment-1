#include "editing_text.h"

using namespace std;

EditingText::EditingText(Functionality& func) : functionality(func) {}

void EditingText::addText() {
    cout << "  -Add text-  " << endl;
    cout << "Write a text: ";
    char* newText = functionality.readline();
    if (!newText) return;
    functionality.relocateMemory(newText, -1, -1);
}

void EditingText::addNewLine() {
    cout << "  -Add new line-  " << endl;
    char* newText = (char*)malloc(2);
    if (!newText) return;
    newText[0] = '\n';
    newText[1] = '\0';
    functionality.relocateMemory(newText, -1, -1);
}

void EditingText::insertTextOnPosition() {
    cout << "  -Insert text by coordinate-  " << endl;
    cout << "Write a position (x y) - ";
    char* tmpInput = functionality.readline();
    if (!tmpInput) return;
    int x = 0, y = 0;
    if (sscanf(tmpInput, "%d %d", &x, &y) != 2) {
        cout << "Uncorrect coordinates" << endl;
        free(tmpInput);
        return;
    }
    free(tmpInput);

    cout << "Write a text: ";
    char* newText = functionality.readline();
    if (!newText) return;
    functionality.relocateMemory(newText, x, y);
}
