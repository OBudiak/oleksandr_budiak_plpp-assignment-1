#include "functionality.h"

using namespace std;

Functionality::Functionality() {
    text = NULL;
}

Functionality::~Functionality() {
    free(text);
}

char* Functionality::readline() {
    size_t size = 64;
    size_t len = 0;
    char* buf = (char*)malloc(size);
    if (!buf) return NULL;

    int c;
    while ((c = fgetc(stdin)) != EOF && c != '\n') {
        if (len + 1 >= size) {
            size += 64;
            char* newbuf = (char*)realloc(buf, size);
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

int Functionality::powerF(int power) {
    return (int)pow(10, power);
}

void Functionality::relocateMemory(char* newText, int x, int y) {
    size_t oldLen = 0;
    if (text) {
        while (text[oldLen]) oldLen++;
    }

    size_t addLen = 0;
    while (newText[addLen]) addLen++;

    char* tmp = (char*)realloc(text, oldLen + addLen + 1);
    if (!tmp) {
        free(newText);
        return;
    }
    text = tmp;

    size_t idx = 0, curX = 0, curY = 0;
    if (x >= 0 && y >= 0) {
        while (idx < oldLen && (curY < (size_t)y || curX < (size_t)x)) {
            if (text[idx] == '\n') {
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

    char* src = text + idx;
    char* dest = text + idx + addLen;
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
        text[idx + i] = newText[i];
    }
    text[oldLen + addLen] = '\0';
    free(newText);
}

void Functionality::saveInFile() {
    cout << "  -Save in file-  " << endl;
    cout << "Enter file name: ";
    char* fileName = readline();
    if (!fileName) return;
    FILE* file = fopen(fileName, "w");
    if (file != NULL) {
        fputs(text, file);
        fclose(file);
    }
    free(fileName);
}

void Functionality::loadFromFile() {
    cout << "  -Load from file-  " << endl;
    cout << "Enter file name: ";
    char* fileName = readline();
    if (!fileName) return;

    FILE* file = fopen(fileName, "r");
    free(fileName);
    if (!file) {
        cout << "Error opening file" << endl;
        return;
    }

    size_t size = 128, len = 0;
    char* buf = (char*)malloc(size);
    if (!buf) {
        fclose(file);
        return;
    }

    int c;
    while ((c = fgetc(file)) != EOF) {
        if (len + 1 >= size) {
            size *= 2;
            char* tmpBuf = (char*)realloc(buf, size);
            if (!tmpBuf) {
                free(buf);
                fclose(file);
                return;
            }
            buf = tmpBuf;
        }
        buf[len++] = (char)c;
    }
    buf[len] = '\0';
    fclose(file);
    free(text);
    text = buf;
}

void Functionality::searchText() {
    cout << "  -Search in text-  " << endl;
    cout << "Enter text: ";
    char* phrase = readline();
    if (!phrase || phrase[0] == '\0') {
        cout << "Empty search string" << endl << endl;
        free(phrase);
        return;
    }
    if (!text) {
        cout << "Text is empty" << endl << endl;
        free(phrase);
        return;
    }

    char* t = text;
    int line = 0, col = 0, found = 0;
    size_t len_text = strlen(t);
    size_t len_phrase = strlen(phrase);

    for (size_t i = 0; i < len_text; i++) {
        if (t[i] == '\n') {
            line++;
            col = 0;
            continue;
        }
        if (i + len_phrase <= len_text && strncmp(&t[i], phrase, len_phrase) == 0) {
            cout << "\"" << phrase << "\" - " << line << " " << col << endl;
            found = 1;
        }
        col++;
    }

    if (!found) {
        cout << "\"" << phrase << "\" was not found" << endl;
    }
    cout << endl;
    free(phrase);
}

void Functionality::showText() {
    cout << "  -Show text-  " << endl;
    if (text == NULL) {
        cout << "[Текст порожній]" << endl << endl;
    } else {
        cout << text << endl;
    }
}
