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
 * Initializes a doubly linked list structure for use.
 *
 * This function sets the initial state of the list by zeroing its size and 
 * setting the head and tail pointers to `NULL`. It also assigns a user-provided
 * `destroy` callback function that is used to free the data within nodes when 
 * they are removed or the list is destroyed.
 *
 * @param list     Pointer to the doubly linked list structure to initialize.
 * @param destroy  Optional pointer to a function that takes a void pointer (`void*`)
 *                 and deallocates or cleans up the node's data. Can be `NULL` if no
 *                 special destruction is needed.
 *
 * @note The list structure itself must be allocated before calling this function.
 */
void List_init(List* list, void (*destroy)(void* data));

/**
 * Destroys the list by removing all nodes and freeing associated data.
 *
 * This function repeatedly removes the nodes from the list until it is empty.
 * For each removed node, if a destroy callback is set, it is called to handle
 * deallocating or cleaning up the node's data. After all nodes are removed, 
 * the list structure is zeroed out with memset, resetting size and pointers.
 *
 * @param list  Pointer to the list to be destroyed.
 *
 * @return None.
 *
 * @note The list's destroy callback, if provided, must be capable of properly freeing
 *       or cleaning up node data. Without this, memory leaks may occur.
 */
void List_destroy(List* list);

/**
 * Inserts a new node containing the provided data at the head of the doubly linked list.
 *
 * This function creates a new node initialized with the given data and inserts it at the front of the list.
 * If the list is empty, the new node becomes both the head and tail. Otherwise, the current head's previous
 * pointer is updated to point to the new node, the new node's next pointer is set to the old head, and the
 * list's head pointer is updated to the new node. The list size is incremented to reflect the new node.
 *
 * @param list  Pointer to the doubly linked list.
 * @param data  Pointer to the data to be stored in the new node.
 *
 * @return 0 on successful insertion, -1 if node creation fails.
 */
int List_insert_head(List* list, const void* data);

/**
 * Removes the head node of the doubly linked list and optionally retrieves its data.
 *
 * This function deletes the first node (head) of the list. If the list has only one node,
 * both the head and tail pointers are set to `NULL`. For longer lists, the head pointer
 * is updated to the next node, and the new head's previous pointer is set to `NULL`.
 * The node's memory is freed, and the list's size is decremented. If the `data` argument
 * is non-`NULL`, it receives the data pointer from the removed node.
 *
 * @param list  Pointer to the doubly linked list.
 * @param data  Optional pointer to store the data of the removed node.
 *
 * @return 0 on success, -1 if the list is empty.
 *
 * @note The function does not free the data content pointed to by the node; cleanup of data
 *       must be handled by the caller if necessary.
 */
int List_remove_head(List* list, void** data);

/**
 * Inserts a new node containing the given data at the tail of the doubly linked list.
 *
 * This function creates a new node with the provided data and appends it to the end of the list.
 * If the list is empty, the new node becomes both the head and tail. Otherwise, it updates the current
 * tail node's next pointer to point to the new node, and the new node's previous pointer to the current tail.
 * The list's tail pointer is then updated to the new node. The list size is incremented accordingly.
 *
 * @param list  Pointer to the doubly linked list to modify.
 * @param data  Pointer to the data to store in the new node.
 *
 * @return 0 on success, -1 if node creation fails.
 */
int List_insert_tail(List* list, void* data);

/**
 * Prints the contents of the doubly linked list from head to tail.
 *
 * This function traverses the list starting from the head node, calling the list's
 * print callback on each node's data. Nodes are printed in order, separated by " -> ".
 * If the list's print function pointer is `NULL`, the function returns without doing anything.
 * A newline is printed after all nodes have been output.
 *
 * @param list  Pointer to the doubly linked list to print.
 *
 * @note The list's print callback should accept a void pointer to the node's data
 *       and handle printing it appropriately.
 */
void List_print(const List* list);

/**
 * Prints the contents of the doubly linked list from tail to head.
 *
 * This function traverses the list starting from the tail node, calling the list's
 * print callback on each node's data in reverse order. Nodes are printed separated by
 * " -> ". The function returns immediately if the list's print function pointer is `NULL`.
 * A newline is printed after all nodes have been output.
 *
 * @param list  Pointer to the doubly linked list to print in reverse.
 *
 * @note The list's print callback must accept a void pointer to node data and print it correctly.
 */
void List_print_backward(const List* list);

/**
 * Inserts a new node with the specified data at the tail of the doubly linked list.
 *
 * This function creates a new node initialized with the provided data and appends it 
 * to the end of the list. If the list is empty, the new node becomes both the head 
 * and tail of the list. Otherwise, it links the new node after the current tail, 
 * updating pointers accordingly.
 *
 * @param list  Pointer to the doubly linked list.
 * @param data  Pointer to the data to store in the new node.
 *
 * @return 0 on success, -1 if node creation fails.
 */
int List_insert_tail(List* list, void* data);

/**
 * Searches the doubly linked list for the first node matching the given data.
 *
 * This function traverses the list starting from the head, comparing each node's data 
 * with the provided data pointer using the list's match function. It returns a pointer 
 * to the first node where the match function returns 0, indicating equality.
 * If the list is empty, the match callback is `NULL`, or data is `NULL`, it returns `NULL`.
 *
 * @param list  Pointer to the doubly linked list to search.
 * @param data  Pointer to the data to match against nodes in the list.
 *
 * @return Pointer to the matching node if found, or `NULL` if no match or invalid input.
 *
 * @note The match function should accept two data pointers and return 0 if they are considered equal.
 */
Node* List_find(const List* list, const void* data);

/**
 * Inserts a new node with the specified data immediately after the given node in the list.
 *
 * The function first verifies that the specified node belongs to the provided list and that
 * the data pointer is not `NULL`. If the node is the tail of the list, the insertion delegates
 * to `List_insert_tail`. Otherwise, a new node is created and inserted after the specified node,
 * with pointers updated accordingly. The list size is incremented on success.
 *
 * @param list   Pointer to the doubly linked list.
 * @param node  Pointer to the node after which the new node will be inserted.
 * @param data   Pointer to the data to store in the new node.
 *
 * @return 0 on success, -1 if `node` does not belong to `list`, `data` is `NULL`,
 *         or node creation fails.
 */
int List_insert_after(List* list, Node* node, const void* data);

/**
 * Inserts a new node containing the given data immediately before the specified node in the list.
 *
 * The function first verifies that the specified node belongs to the provided list and that the 
 * data pointer is not `NULL`. If the node is the head of the list, the insertion delegates to 
 * `List_insert_head`. Otherwise, a new node is created and inserted before the specified node, 
 * with appropriate pointers updated to maintain list integrity. The list size is incremented.
 *
 * @param list   Pointer to the doubly linked list.
 * @param node  Pointer to the node before which the new node will be inserted.
 * @param data   Pointer to the data to store in the new node.
 *
 * @return 0 on success, -1 if `node` does not belong to `list`, `data` is `NULL`,
 *         or node creation fails.
 */
int List_insert_before(List* list, Node* node, const void* data);

/**
 * Deletes the specified node from the doubly linked list and optionally retrieves its data.
 *
 * This function verifies that the node belongs to the list. If the node is the head or
 * tail of the list, it delegates deletion to the `List_remove_head` or `List_remove_tail`
 * functions respectively. For a node in the middle, it updates the adjacent nodes to bypass
 * the target node, extracts the node's data if requested, frees the node memory, and decrements
 * the list size.
 *
 * @param list  Pointer to the doubly linked list.
 * @param node  Pointer to the node to be deleted.
 * @param data  Optional pointer to store the data of the deleted node.
 *
 * @return 0 on success, -1 if the node does not belong to the list.
 *
 * @note This function does not free the data stored within the node; the caller must manage that.
 */
int List_delete_node(List* list, Node* node, void** data);

/* ================================================================ */

#endif /* _LIST_H */