#include "Lib.h"

static int newMemoryCount = 0;

void* newMemory(int size) {
        void* ptr = malloc(size);
        assert(ptr != NULL);
        memset(ptr, 0, size);
        newMemoryCount++;
        return ptr;
}

static int freeMemoryCount = 0;

void freeMemory(void *ptr) {
        assert(ptr != NULL);
        free(ptr);
        freeMemoryCount++;
}

void checkMemory() {
        printf("newMemoryCount: %d, freeMemoryCount: %d\n",
                        newMemoryCount, freeMemoryCount);
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

char* newCatStr(char *str_a, char *str_b) {
        size_t len_a = strlen(str_a),
               len_b = strlen(str_b);
        char *s = (char*) newMemory(len_a + len_b + 1); // EOF = 1 char
        memcpy(s, str_a, len_a);
        memcpy(s + len_a, str_b, len_b);
        return s;
}

static char spaces[MAX_LEN];

char* newSpaces(int len) {
        assert(len < MAX_LEN);
        memset(spaces, ' ', MAX_LEN);
        spaces[len] = '\0';
        return spaces;
}
