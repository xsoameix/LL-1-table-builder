#include "Array.h"

static char* UArrayNew();
static char* UArrayEach();
static void setItem(void *item);
static void freeItem(void *item);

char* UArray() {
        mu_run_test(UArrayNew);
        mu_run_test(UArrayEach);
        return 0;
}

static
char* UArrayNew() {
        Array *a = ArrayNew(5);
        mu_assert("error, Array size != 5", a->size == 5);
        mu_assert("error, Array count != 0", a->count == 0);
        return 0;
}

static
char* UArrayEach() {
        Array *a = ArrayNew(5);
        int *item;
        for(int i = 0; i < a->size; i++) {
                item = (int*) newMemory(sizeof(int));
                *item = i;
                ArrayAdd(a, item);
        }
        ArrayEach(a, &setItem);
        for(int i = 0; i < a->count; i++) {
                static char buf[50];
                sprintf(buf, "error, a->item[%d] != %d", i, i + 1);
                mu_assert(buf, *((int*) a->item[i]) == i + 1);
        }
        ArrayFree(a, &freeItem);
        return 0;
}

static
void setItem(void *item) {
        *((int*) item) += 1;
}

static
void freeItem(void *item) {
        freeMemory(item);
}
