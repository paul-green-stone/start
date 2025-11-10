#ifndef _START_SELECTWIDGET_INTERFACE_H
#define _START_SELECTWIDGET_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

/* ================================================================ */

/**
 * Advances the currently selected option in a SelectWidget to the next option and updates the displayed text accordingly. If the selection reaches the end of the options list, it wraps around to the first option.
 * 
 * @param widget pointer to the instance of the `select_widget` structure. This should point to a valid object of type `SelectWidget`
 * 
 * @return Returns `SSUCCESS` on successful advancement and update of the selection or a negative error code on failure; call `Error_string()` for more information.
 */
int SelectWidget_next(void* widget);

/**
 * Moves the selection in the SelectWidget to the previous option and updates the displayed text. If the selection is at the start of the list, it wraps around to the last option.
 * 
 * @param widget pointer to an instance of the `select_widget` structure, expected to be of type `SelectWidget`
 * 
 * @return Returns `SSUCCESS` on successful advancement and update of the selection or a negative error code on failure; call `Error_string()` for more information.
 */
int SelectWidget_prev(void* widget);

/**
 * Retrieves the currently selected option string from the `SelectWidget`.
 * 
 * @param widget pointer to a constant instance of the `select_widget` structure, expected to be of type `SelectWidget`
 * 
 * @return Returns A pointer to the string representing the currently selected option, or NULL; call `Error_string()` for more information.
 */
const char* SelectWidget_get_value(const void* widget);

/**
 * Adds a new option string to the `SelectWidget`.
 * 
 * @param widget pointer to the instance of the `select_widget` structure, expected to be of type `SelectWidget`
 * @param option a null-terminated string representing the option to be added
 * 
 * @return Returns `SSUCCESS` on success or a negative error code on failure; call `Error_string()` for more information.
 */
int SelectWidget_add(void* widget, const char* option);

/* ================================================================ */

#ifdef __cplusplus
}
#endif

#endif /* _START_SELECTWIDGET_INTERFACE_H */

