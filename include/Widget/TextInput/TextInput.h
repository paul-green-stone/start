#ifndef _START_TEXTINPUT_INTERFACE_H
#define _START_TEXTINPUT_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

/* ================================================================ */

/**
 * This function processes events related to text input and key presses,
 * updating the content of the text input widget accordingly.
 * 
 * @param input pointer to the text input widget instance
 * @param e pointer to the `SDL_Event` to process
 * 
 * @return Returns `SSUCCESS` (0) on success or a negative error code on failure; call `Error_string()` for more information.
 */
int TextInput_update(void* input, SDL_Event* e);

/**
 * This function copies the contents of the input field into the buffer.
 * 
 * @param input widget whose input is to be retrieved
 * @param buffer buffer in which to store the result
 * 
 * @return Returns `SSUCCESS` (0) on success or a negative error code on failure; call `Error_string()` for more information.
 */
int TextInput_get_input(const void* input, char* buffer);

/**
 * 
 */
int TextInput_clear(void* widget);

/* ================================================================ */

#ifdef __cplusplus
}
#endif

#endif /* _START_TEXTINPUT_INTERFACE_H */
