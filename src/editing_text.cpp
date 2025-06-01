#include "editing_text.h"
#include "functionality.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

