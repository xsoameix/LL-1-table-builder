#include "HashTable.h"

static char* UHPut();

char* UHashTable() {
        mu_run_test(UHPut);
        return 0;
}

static
char* UHPut() {
        HTab *h = newHashTable(13, mNULL);
        HPut(h, "dff", "data1");
        HPut(h, "asu", "data2");
        HPut(h, "boe", "data3");
        HPut(h, "ono", "data4");
        HPut(h, "s/z", "data5");
        HPut(h, "xoo", "data6");
        HPut(h, "woy", "data7");
        HPut(h, "mj.", "data8");
        HPut(h, "hnr", "data9");
        HPut(h, "289", "data10");
        HPut(h, "2n3", "data11");
        HPut(h, "2j2", "data12");
        HPut(h, "sok", "data13");
        mu_assert("HGet(\"xoo\") != \"data6\"", strcmp(HGet(h, "xoo"), "data6") == 0);
        mu_assert("h->size != 29", h->size == 29);
        mu_assert("h->filled != 13", h->filled == 13);
        return 0;
}
