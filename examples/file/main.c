#include "../../include/Start.h"

/* ================================================================ */

int main(int argc, char** argv) {

    config_t config;
    char* version;
    int w, h;
    double price;

    config_init(&config);

    int status = Conf_parse_file(&config, "example.conf");

    Start();

    App_init();
    App_quit();

    if (status != 0) {

        printf("Bad things happened\n");

        /* ======== */

        return -1;        
    }

    if (Conf_extract(&config, "version", STRING, &version) == 0) {
        printf("Version: %s\n", version);
    }

    if (Conf_extract(&config, "application.window.size.w", INT, &w) == 0) {
        printf("Width: %d\n", w);
    }
    if (Conf_extract(&config, "application.window.size.h", INT, &h) == 0) {
        printf("Height: %d\n", h);
    }

    if (Conf_extract(&config, "application.window.title", STRING, &version) == 0) {
        printf("Title: %s\n", version);
    }

    if (Conf_extract(&config, "application.books.[0].price", FLOAT, &price) == 0) {
        printf("Price: %.2f\n", price);
    }

    config_destroy(&config);

    /* ======== */

    return 0;
}

/* ================================================================ */
