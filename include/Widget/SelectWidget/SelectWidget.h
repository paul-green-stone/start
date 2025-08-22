#ifndef _START_SELECTWIDGET_INTERFACE_H
#define _START_SELECTWIDGET_INTERFACE_H

/* ================================================================ */

/**
 * 
 */
int SelectWidget_next(void* widget);

/**
 * 
 */
int SelectWidget_prev(void* widget);

/**
 * 
 */
const char* SelectWidget_get_value(const void* widget);

/**
 * 
 */
int SelectWidget_add(void* widget, const char* option);

/* ================================================================ */

#endif /* _START_SELECTWIDGET_INTERFACE_H */

