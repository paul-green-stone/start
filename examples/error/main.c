#include "../../include/Start.h"

/* ================================================================ */

int main(int argc, char** argv) {

    int status;
    char* filename = "test.conf";
    config_t config;
    config_setting_t* setting;

    char* name;
    /* ======== */

    config_init(&config);

    if ((status = Conf_parse_file(&config, filename)) != SSUCCESS) {

        config_destroy(&config);
        error(stderr, "%s\n", Error_string());

        /* ======== */
        return status;
    }
    else {
        printf("OK\n");
    }

    // if (Conf_extract(&config, "name", 8, &name) == SSUCCESS) {
    //     printf("Name = %s\n", name);
    // }
    // else {
    //     error(stderr, "%s\n", Error_get_msg());
    // }

    // if (Conf_lookup(&config, "what", &setting) == SERR_ITEM_NOT_FOUND) {
    //     error(stderr, "%s\n", Error_get_msg());
    // }

    // if (file_exists(NULL)) {
    //     printf("Exists!\n");
    // }

    // status = directory_new("us");
    // if (status == 1) {
    //     printf("directory exists\n");
    // }
    // else if (status == SSUCCESS) {
    //     printf("directory created\n");
    // }
    // else {
    //     error(stderr, "%s\n", Error_get_msg());
    // }
    
    // if (Start() != SSUCCESS) {
    //     error(stderr, "%s\n", Error_get_msg(), "");
    // }

    // Stop();

    //config_destroy(&config);

    /* ======== */
    return EXIT_SUCCESS;
}

/* ================================================================ */
