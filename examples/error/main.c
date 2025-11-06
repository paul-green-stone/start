#include "../../include/Start.h"

/* ================================================================ */

int main(int argc, char** argv) {

    int status;
    char* filename = "test.conf";
    config_t config;
    config_setting_t* setting;

    char* name = NULL;
    /* ======== */

    config_init(&config);

    /* ================================================================ */
    /* ================ Parsing the configuration file ================ */
    /* ================================================================ */
    if ((status = Conf_parse_file(&config, filename)) != SSUCCESS) {

        config_destroy(&config);
        error(stderr, "%s\n", Error_string());

        /* ======== */
        return status;
    }
    else {
        printf("OK\n");
    }

    /* ================================================================ */
    /* ================= Extracting a string "name" =================== */
    /* ================================================================ */

    /**
     * If a configuration file contains a string member,
     * specifying it as a BOOLEAN causes a segmentation fault.
     * 
     * hmmm...
     */

    if (Conf_extract(&config, "name", STRING, &name) == SSUCCESS) {
        printf("Name = %s\n", name);
    }
    else {
        error(stderr, "%s\n", Error_string());
    }

    /* ================================================================ */
    /* ============= Trying to extract an entity "what", ============== */
    /* ============ further processing is usually required ============ */
    /* ================================================================ */

    /**
     * This one results in a libconfig error 'cause there is no such member
     */

    if (Conf_lookup(&config, "what", &setting) != SSUCCESS) {
        error(stderr, "%s\n", Error_string());
    }

    /* ================================================================ */
    /* ================= Trying to create a directory ================= */
    /* ================================================================ */

    if ((status = directory_new("us")) == 1) {
        printf("directory exists\n");
    }
    else if (status == SSUCCESS) {
        printf("directory created\n");
    }
    else {
        error(stderr, "%s\n", Error_string());
    }

    /* ================================================================ */
    /* ============ Trying to create a configuration file ============= */
    /* ================================================================ */

    if (Start() != SSUCCESS) {
        error(stderr, "%s\n", Error_string());
    }

    Stop();

    /* ================================================================ */

    config_destroy(&config);

    /* ======== */
    return EXIT_SUCCESS;
}

/* ================================================================ */
