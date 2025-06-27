#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================================================================ */
/* ========================= Definitions ========================== */
/* ================================================================ */

/* === Define a structure for linked list elements === */
typedef struct node {

    void* data;

    void* list;
    struct node* next;
    struct node* prev;
} Node;

/* ======== */

typedef struct list {

    size_t size;

    int (*match)(const void* key1, const void* key2);
    void (*destroy)(void* data);
    void (*print)(void* data);

    Node* head;
    Node* tail;
} List;

/* ================================================================ */
/* ======================= Public Interface ======================= */
/* ================================================================ */

/**
 * Initializes the linked list specified by `list`. This operation must
 * be called for a linked list before the list can be used with any other operation.
 * The `destroy` argument provides a way to free dynamically allocated data when
 * `List_destroy` is called. For example, if the list contains data dynamically allocated
 * using `malloc`, destroy should be set to `free` to free the data as the linked list is
 * destroyed. For structured data containing several dynamically allocated members,
 * `destroy` should be set to a user-defined function that calls free for each dynamically
 * allocated member as well as for the structure itself. For a linked list containing
 * data that should not be freed, `destroy` should be set to `NULL`.
 * 
 * @return None.
 */
void List_init(List* list, void (*destroy)(void* data));

/* ======== */

/**
 * Destroys the linked list specified by `list`. No other operations
 * are permitted after calling `List_destroy` unless `List_init` is called again. The `List_destroy`
 * operation removes all elements from a linked list and calls the function
 * passed as `destroy` to `List_init` once for each element as it is removed, provided
 * `destroy` was not set to `NULL`.
 * 
 * @return None.
 */
void List_destroy(List* list);

/* ======== */

/**
 * Inserts a new element containing `data` at the head of the linked list specified by `list`.
 * The `data` pointer is stored as-is; the function does not copy or manage the data itself.
 * It is the caller's responsibility to ensure that the data remains valid for the lifetime
 * of the list node.
 * 
 * @param list Pointer to the linked list in which to insert the new element.
 * @param data Pointer to the data to be stored in the new list node.
 * 
 * @return 0 on success, or -1 if memory allocation for the new node fails.
 */
int List_insert_head(List* list, const void* data);

/* ======== */

/**
 * Removes the head (first element) from the linked list specified by `list`.
 * The caller is responsible for managing the memory of the data returned through `data`.
 * This function does not free the data itself; it only removes the node from the list.
 * 
 * @return 0 on success, or -1 if the list is empty and no node can be removed.
 */
int List_remove_head(List* list, void** data);

/* ======== */

/**
 * Inserts a new element containing `data` at the head of the linked list specified by `list`.
 * The `data` pointer is stored directly in the new node; the list does not make a copy of the data.
 * It is the caller's responsibility to ensure the data remains valid for the lifetime of the list node.
 * 
 * @param list A pointer to the linked list where the new element will be inserted.
 * @param data A pointer to the data to be stored in the new list element.
 * 
 * @return 0 on success, or -1 if memory allocation for the new node fails.
 */
int List_insert_tail(List* list, void* data);

/* ======== */

/**
 * Prints the contents of the linked list specified by `list` to the standard output.
 * The list must have a valid print function pointer assigned to its `print` member
 * to properly display each element's data. If the `print` function pointer is `NULL`,
 * this function will return immediately without printing anything.
 * 
 * @param list A pointer to the linked list whose contents are to be printed.
 * 
 * @return None.
 */
void List_print(const List* list);

/* ======== */

/**
 * Prints the contents of the linked list specified by `list` to the standard output.
 * The list must have a valid print function pointer assigned to its `print` member
 * to properly display each element's data. If the `print` function pointer is `NULL`,
 * this function will return immediately without printing anything.
 * 
 * @param list A pointer to the linked list whose contents are to be printed.
 * 
 * @return None.
 */
void List_print_backward(const List* list);

/* ======== */

/**
 * Removes the tail (last element) from the linked list specified by `list`.
 * If the list is not empty, the data stored in the tail node is returned via
 * the `data` pointer.abort.
 * The caller is responsible for handling the data pointed to by `*data` after
 * removal. Note that this function does not free the data itself; it only frees
 * the node structure.
 * 
 * @param list  Pointer to the linked list from which the tail node will be removed.
 * @param data  Pointer to a void pointer where the data of the removed tail node.
 * 
 * @return 0 if the tail node was successfully removed, or -1 if the list was empty.
 */
int List_remove_tail(List* list, void** data);

/* ======== */

/**
 * Searches the linked list specified by `list` for an element matching `data`.
 * The comparison is performed using the list's `match` function, which should
 * return 0 when the elements are considered equal.
 * If a matching node is found, a pointer to that node is returned.
 * If no match is found, or if the list is empty, or if `match` or
 * `data` is `NULL`, the function returns `NULL`.
 * 
 * @param list  Pointer to the linked list to search.
 * @param data  Pointer to the data to match against elements in the list.
 * 
 * @return A pointer to the matching node in the list if found; otherwise, `NULL`.
 */
Node* List_find(const List* list, const void* data);

/* ================================================================ */

/**
 * Inserts a new node containing `data` immediately after the specified node `_node`
 * in the linked list `list`. If `_node` is the tail node of the list, the new data is appended to the end
 * of the list.
 * 
 * @param list Pointer to the linked list where the new node will be inserted.
 * @param _node Pointer to the node after which the new node will be inserted.
 * Must be a node in `list`.
 * @param data Pointer to the data to be stored in the new node.
 * 
 * @return 0 on success; -1 on failure.
 */
int List_insert_after(List* list, Node* node, const void* data);

/**
 * Inserts a new node containing `data` immediately before the specified node `_node`
 * in the linked list `list`. If `_node` is the head node of the list, the new data is inserted at the beginning
 * of the list.
 * 
 * @param list Pointer to the linked list where the new node will be inserted.
 * @param _node Pointer to the node after which the new node will be inserted.
 * Must be a node in `list`.
 * @param data Pointer to the data to be stored in the new node.
 * 
 * @return 0 on success; -1 on failure.
 */
int List_insert_before(List* list, Node* node, const void* data);

/* ================================================================ */

#endif /* _LIST_H */
