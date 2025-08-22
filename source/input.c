#include "../include/Input.h"
#include "../include/Error.h"

/* ================================================================ */
/* ======================= DEFINEs&TYPEDEFs ======================= */
/* ================================================================ */

struct input_manager {

    /* Arrays to hold the state of each key */
    Uint8 current_state[SDL_NUM_SCANCODES];
    Uint8 previous_state[SDL_NUM_SCANCODES];

    /* Left, Middle, and Right mouse buttons */
    Uint8 current_BTN_state[3];
    Uint8 previous_BTN_state[3];

    /* Mouse cursor position */
    int x;
    int y;
};

/* ======== */

typedef struct input_manager Input;

/* ================================================================ */
/* ======================== STATIC STORAGE ======================== */
/* ================================================================ */

static Input IO_Manager;

/* ================================================================ */
/* ==================== FUNCTIONS DEFENITIONS ===================== */
/* ================================================================ */

void Input_update(void) {

    const Uint8* current_state;

    /* Store current key states in the previous states */
    memcpy(IO_Manager.previous_state, IO_Manager.current_state, sizeof(IO_Manager.current_state));

    /* Update current key states */
    current_state = SDL_GetKeyboardState(NULL);
    memcpy(IO_Manager.current_state, current_state, sizeof(IO_Manager.current_state));

    memcpy(IO_Manager.previous_BTN_state, IO_Manager.current_BTN_state, sizeof(IO_Manager.current_BTN_state));

    /* Update mouse states */
    IO_Manager.current_BTN_state[0] = SDL_GetMouseState(&IO_Manager.x, &IO_Manager.y) & SDL_BUTTON(SDL_BUTTON_LEFT);
    IO_Manager.current_BTN_state[1] = SDL_GetMouseState(&IO_Manager.x, &IO_Manager.y) & SDL_BUTTON(SDL_BUTTON_MIDDLE);
    IO_Manager.current_BTN_state[2] = SDL_GetMouseState(&IO_Manager.x, &IO_Manager.y) & SDL_BUTTON(SDL_BUTTON_RIGHT);
}

/* ================================================================ */

int Input_isKey_pressed(SDL_Scancode key) {
    return IO_Manager.current_state[key];
}

/* ================================================================ */

int Input_wasKey_pressed(SDL_Scancode key) {
    return IO_Manager.current_state[key] && !IO_Manager.previous_state[key];
}

/* ================================================================ */

int Input_isBtn_pressed(MouseButton btn) {

    /* Prevent access to memory areas beyond the array */
    if ((btn < 0) || (btn > 2)) {
        
        Error_set(SERR_INVALID_RANGE);
        /* ======== */
        return SERR_INVALID_RANGE;
    }

    /* ======== */
    return IO_Manager.current_BTN_state[btn];
}

/* ================================================================ */

int Input_wasBtn_pressed(MouseButton btn) {

    /* Prevent access to memory areas beyond the array */
    if ((btn < 0) || (btn > 2)) {

        Error_set(SERR_INVALID_RANGE);
        /* ======== */
        return SERR_INVALID_RANGE;
    }

    /* ======== */
    return IO_Manager.current_BTN_state[btn] && !IO_Manager.previous_BTN_state[btn];
}

/* ================================================================ */

void Input_get_cursorPos(int* x, int* y) {

    *x = IO_Manager.x;
    *y = IO_Manager.y;
}

/* ================================================================ */
