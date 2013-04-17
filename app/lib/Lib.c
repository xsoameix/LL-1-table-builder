#include "Lib.h"

static int newMemoryCount = 0;

void* newMemory(int size) {
        return newMemoryLog(size, mNULL);
}

static MemoryLog memLog[] = {
        {"unknown()", "unknown()", "", 0, 0},
        {"IParser()", "newCatStr()", "Cat path and filename.", 0, 0},
        {"IParser()", "fileToStr()", "Read the .syntax file.", 0, 0},
        {"scan()", "newSubStr()", "", 0, 0},
        {"scan()", "newToken()", "", 0, 0},
        {"buildRoot()", "newTree()", "", 0, 0},
        {"addChild()", "newTree()", "", 0, 0},
        {"addChild()", "ArrayNew()x2", "", 0, 0},
        {"addChild()", "ArrayAdd()", "", 0, 0},
        {"addLeaf()", "newLeaf()", "", 0, 0},
        {"addLeaf()", "ArrayNew()x2", "", 0, 0},
        {"addLeaf()", "ArrayAdd()", "", 0, 0},
        {"storeInWhichP()", "newS_NT()", "", 0, 0},
        {"storeInWhichP()", "newS_T()", "", 0, 0},
        {"addInWhichP()", "newP()x3", "", 0, 0},
        {"addInWhichP()", "ArrayAdd()", "Put P into NT.", 0, 0},
        {"addInWhichP()", "ArrayAdd()", "Put S into P.", 0, 0},
        {"addNT()", "newNT()x3", "", 0, 0},
        {"addNT()", "ArrayNew()x2", "", 0, 0},
        {"addNT()", "ArrayAdd()", "", 0, 0},
        {"addT()", "newT()", "", 0, 0},
        {"addT()", "ArrayNew()x2", "", 0, 0},
        {"addT()", "ArrayAdd()", "", 0, 0}};

void* newMemoryLog(int size, int reason) {
        memLog[reason].newMemoryCount++;
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
        printf("+------------------------  checkMemory  -------------------------+\n");
        printf("| %37s%7s%18s |\n", "malloc", "free", "");
        printf("| %-31s%6d%7d%18s |\n", "Total", newMemoryCount, freeMemoryCount, "");
        printf("| %-17s%-29s%-16s |\n", "[Caller]", "[Callee]", "[Explanation]");
        int len = sizeof(memLog) / sizeof(memLog[0]);
        for(int i = 0; i < len; i++) {
                printf("| %-17s%-14s%6d%7d  %-16s |\n",
                                memLog[i].caller,
                                memLog[i].callee,
                                memLog[i].newMemoryCount,
                                memLog[i].freeMemoryCount,
                                memLog[i].explanation);
        }
        printf("|           x2 or x3 is the malloc times per function.           |\n");
        printf("+----------------------------------------------------------------+\n");
}

char* fileToStr(char *filename) {
        return mFileToStr(filename, mNULL);
}

char* mFileToStr(char *filename, int reason) {
        FILE *file = fopen(filename, "rb");
        assert(file != NULL);

        // obtain the size
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        rewind(file);

        // read into buffer
        char *buffer = (char *) newMemoryLog(size + 1, reason); // EOF = 1 char
        fread(buffer, 1, size, file);

        // add EOF
        buffer[(int) size] = '\0';

        fclose(file);
        return buffer;
}

char* newSubStr(char *str, int offset, int len) {
        return mNewSubStr(str, offset, len, mNULL);
}

char* mNewSubStr(char *str, int offset, int len, int reason) {
        char *newStr = newMemoryLog(len + 1, reason); // EOF = 1 char
        strncpy(newStr, &str[offset], len);
        newStr[len] = '\0';
        return newStr;
}

char* newCatStr(char *str_a, char *str_b) {
        return mNewCatStr(str_a, str_b, mNULL);
}

char* mNewCatStr(char *str_a, char *str_b, int reason) {
        size_t len_a = strlen(str_a),
               len_b = strlen(str_b);
        char *s = (char*) newMemoryLog(len_a + len_b + 1, reason); // EOF = 1 char
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
