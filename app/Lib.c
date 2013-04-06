#include "Lib.h"

void* newMemory(int size) {
        void* ptr = malloc(size);
        assert(ptr != NULL);
        memset(ptr, 0, size);
        return ptr;
}

char* fileToStr(char *filename) {
        FILE *file = fopen(filename, "rb");
        assert(file != NULL);

        // obtain the size
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        rewind(file);

        // read into buffer
        char *buffer = (char *) newMemory(size + 1); // EOF = 1 char
        fread(buffer, 1, size, file);

        // add EOF
        buffer[(int) size] = '\0';

        fclose(file);
        return buffer;
}

char* newSubStr(char *str, int offset, int len) {
        char *newStr = newMemory(len + 1); // EOF = 1 char
        strncpy(newStr, &str[offset], len);
        newStr[len] = '\0';
        return newStr;
}

char spaces[MAX_LEN];

char* newSpaces(int len) {
        assert(len < MAX_LEN);
        memset(spaces, ' ', MAX_LEN);
        spaces[len] = '\0';
        return spaces;
}
