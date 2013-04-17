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
        {"scan(): newSubStr()", 0, 0},
        {"scan(): newToken()", 0, 0},
        {"buildRoot(): newTree()", 0, 0},
        {"addChild(): newTree()", 0, 0},
        {"addChild(): ArrayNew()x2", 0, 0},
        {"addChild(): ArrayAdd()", 0, 0},
        {"addLeaf(): newLeaf()", 0, 0},
        {"addLeaf(): ArrayNew()x2", 0, 0},
        {"addLeaf(): ArrayAdd()", 0, 0},
        {"storeInWhichP(): newS_NT()", 0, 0},
        {"storeInWhichP(): newS_T()", 0, 0},
        {"addInWhichP(): newP()x3", 0, 0},
        {"addInWhichP(): ArrayAdd(): P", 0, 0},
        {"addInWhichP(): ArrayAdd(): S", 0, 0},
        {"addNT(): newNT()x3", 0, 0},
        {"addNT(): ArrayNew()x2", 0, 0},
        {"addNT(): ArrayAdd()", 0, 0},
        {"addT(): newT()", 0, 0},
        {"addT(): ArrayNew()x2", 0, 0},
        {"addT(): ArrayAdd()", 0, 0}};

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
        printf("============  checkMemory  ============\n");
        printf("x2 or x3 is this function malloc times.\n");
        printf("%-30s%-20s%s\n", "", "newMemoryCount", "freeMemoryCount");
        printf("%-30s%-20d%d\n", "Total", newMemoryCount, freeMemoryCount);
        int len = sizeof(memLog) / sizeof(memLog[0]);
        for(int i = 0; i < len; i++) {
                printf("%-30s%-20d%d\n",
                                memLog[i].reason,
                                memLog[i].newMemoryCount,
                                memLog[i].freeMemoryCount);
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

char* mNewSubStr(char *str, int offset, int len, int reason) {
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
