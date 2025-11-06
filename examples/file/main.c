#include "../../include/Start.h"

/* ================================================================ */

int main(int argc, char** argv) {

    config_t config;
    char* version;
    int w, h;
    double price;

    /* ======== */

    config_init(&config);

    if (Conf_parse_file(&config, "example.conf") != SSUCCESS) {
        
        error(stderr, "%s\n", Error_string());
        /* ======== */
        return EXIT_FAILURE;
    }

    /**
     * The following function calls should return `SSUCCESS`
     * if the libconfig library is installed
     */

    if (Conf_extract(&config, "version", STRING, &version) == SSUCCESS) {
        printf("Version: %s\n", version);
    }

    if (Conf_extract(&config, "application.window.size.w", INT, &w) == SSUCCESS) {
        printf("Width: %d\n", w);
    }
    if (Conf_extract(&config, "application.window.size.h", INT, &h) == SSUCCESS) {
        printf("Height: %d\n", h);
    }

    if (Conf_extract(&config, "application.window.title", STRING, &version) == SSUCCESS) {
        printf("Title: %s\n", version);
    }

    if (Conf_extract(&config, "application.books.[0].price", FLOAT, &price) == SSUCCESS) {
        printf("Price: %.2f\n", price);
    }

    config_destroy(&config);

    /* ======== */
    return EXIT_SUCCESS;
}

/* ================================================================ */
