#include "Lib.h"

static int newMemoryCount = 0;

void* newMemory(int size) {
        void* ptr = malloc(size);
        assert(ptr != NULL);
        memset(ptr, 0, size);
        newMemoryCount++;
        return ptr;
}

static MemoryLog memLog[] = {
        {"scan_newSubStr", 0, 0},
        {"scan_newToken", 0, 0},
        {"buildRoot_newTree", 0, 0},
        {"addChild_newTree", 0, 0},
        {"addChild_ArrayNew(x2)", 0, 0},
        {"addChild_ArrayAdd", 0, 0},
        {"addLeaf_newLeaf", 0, 0},
        {"addLeaf_ArrayNew(x2)", 0, 0},
        {"addLeaf_ArrayAdd", 0, 0},
        {"storeInWhichP_newS_NT", 0, 0},
        {"storeInWhichP_newS_T", 0, 0},
        {"addInWhichP_newP(x3)", 0, 0},
        {"addInWhichP_ArrayAdd_P", 0, 0},
        {"addInWhichP_ArrayAdd_S", 0, 0},
        {"addNT_newNT(x3)", 0, 0},
        {"addNT_ArrayNew(x2)", 0, 0},
        {"addNT_ArrayAdd", 0, 0},
        {"addT_newT", 0, 0},
        {"addT_ArrayNew(x2)", 0, 0},
        {"addT_ArrayAdd", 0, 0}};

void* newMemoryLog(int size, int reason) {
        memLog[reason].newMemoryCount++;
        //return newMemory(size);
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

void freeMemoryLog(void *ptr, int reason) {
        memLog[reason].freeMemoryCount++;
        freeMemory(ptr);
}

void checkMemory() {
        printf("%-25s%s: %-10d%s: %d\n",
                        "Total",
                        "newMemoryCount", newMemoryCount,
                        "freeMemoryCount", freeMemoryCount);
        int len = sizeof(memLog) / sizeof(memLog[0]);
        for(int i = 0; i < len; i++) {
                printf("%-25s%s: %-10d%s: %d\n",
                                memLog[i].reason,
                                "newMemoryCount", memLog[i].newMemoryCount,
                                "freeMemoryCount", memLog[i].freeMemoryCount);
        }
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

char* newSubStr_memLog(char *str, int offset, int len, int reason) {
        char *newStr = newMemoryLog(len + 1, reason); // EOF = 1 char
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
