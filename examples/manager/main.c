#include "../../include/Manager.h"

#include <stdio.h>

/* ================================================================ */

int main(int argc, char** argv) {

    char* s1 = "Orange";
    char* s2 = "Apple";
    char* s3 = "Grape";
    char* s4 = "Melon";

    Manager_insert("orange", s1);
    Manager_insert("apple", s2);
    Manager_insert("grape", s3);
    Manager_insert("melon", s4);

    if (Manager_lookup("peach") != NULL) {
        printf("Peach is known\n");
    }

    if (Manager_lookup("apple") != NULL) {
        printf("Apple's found!\n");
    }

    char* s = Manager_remove("orange");
    printf("%s\n", s != NULL ? s : "Not Found");

    Manager_debug();

    /* ======== */

    return 0;
}

/* ================================================================ */
