#include "../include/List.h"

/* ================================================================ */

static Node* Node_create(void* data) {

    Node* node = NULL;
    /* ======== */

    if ((node = calloc(1, sizeof(struct node))) == NULL) {
        return NULL;
    }

    node->data = data;

    /* ======== */
    return node;
}

/* ================================================================ */

void List_init(List* list, void (*destroy)(void* data)) {

    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}

/* ================================================================ */

void List_destroy(List* list) {

    void* data = NULL;
    /* ======== */

    while (list->size > 0) {
        if ((List_remove_head(list, (void**) &data) == 0) && (list->destroy != NULL)) {
            list->destroy(data);
        }
    }

    memset(list, 0, sizeof(List));
}

/* ================================================================ */

int List_remove_head(List* list, void** data) {

    Node* node = NULL;
    /* ======== */

    /* === Do not allow removal from an empty list === */
    if (list->size == 0) {
        return -1;
    }
    else {

        *data = list->head->data;
        node = list->head;

        if (list->size == 1) {
            list->head = list->tail = NULL;
        }
        else {
            list->head = list->head->next;
            list->head->prev = NULL;
        }
    }

    free(node);
    list->size--;

    /* ======== */
    return 0;
}

/* ================================================================ */

int List_insert_head(List* list, const void* data) {

    Node* node = NULL;
    /* ======== */

    if ((node = Node_create((void*) data)) == NULL) {
        return -1;
    }

    node->list = list;

    if (list->size == 0) {
        list->head = list->tail = node;
    }
    else {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }

    list->size++;

    /* ======== */
    return 0;
}

/* ================================================================ */

void List_print(const List* list) {

    Node* node = NULL;
    /* ======== */

    /* === There is no point in traversing the list === */
    if (list->print == NULL) {
        return ;
    }

    if (list->size > 0) {

        node = list->head;

        for (size_t i = 0; i < list->size; i++) {

            list->print(node->data);
            node = node->next;

            if ((i + 1) != list->size) {
                printf(" -> ");
            }
        }

        printf("\n");
    }
}

/* ================================================================ */

void List_print_backward(const List* list) {

    Node* node = NULL;
    /* ======== */

    /* === There is no point in traversing the list === */
    if (list->print == NULL) {
        return ;
    }

    if (list->size > 0) {

        node = list->tail;

        for (size_t i = 0; i < list->size; i++) {

            list->print(node->data);
            node = node->prev;

            if ((i + 1) != list->size) {
                printf(" -> ");
            }
        }

        printf("\n");
    }
}

/* ================================================================ */

int List_insert_tail(List* list, void* data) {

    Node* node = NULL;
    /* ======== */

    if ((node = Node_create(data)) == NULL) {
        return -1;
    }

    node->list = list;

    if (list->size == 0) {
        list->head = list->tail = node;
    }
    else {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }

    list->size++;

    /* ======== */
    return 0;
}

/* ================================================================ */

int List_remove_tail(List* list, void** data) {

    Node* previous = NULL;
    Node* current = NULL;
    /* ======== */

    if (list->size > 0) {

        *data = list->tail->data;
        current = list->tail;

        if (list->size == 1) {
            list->head = list->tail = NULL;
        }
        else {
            for (previous = list->head, current = previous->next; current != list->tail; previous = current, current = current->next) ;

            list->tail = previous;
            list->tail->next = NULL;
        }

        free(current);
        list->size--;
    }

    /* ======== */
    return -1;
}

/* ================================================================ */

Node* List_find(const List* list, const void* data) {

    Node* current = NULL;
    /* ======= */

    if ((list->size == 0) || (list->match == NULL) || (data == NULL)) {
        return NULL;
    }

    for (current = list->head; current != NULL; current = current->next) {

        if (list->match(data, current->data) == 0) {
            return current;
        }
    }

    /* ======== */
    return NULL;
}

/* ================================================================ */

int List_insert_after(List* list, Node* _node, const void* data) {

    Node* node = NULL;
    /* =======*/

    if ((list == NULL) || (((List*)_node->list) != list) || (data == NULL)) {
        return -1;
    }

    if (_node == list->tail) {
        return List_insert_tail(list, (void*) data);
    }

    if ((node = Node_create((void*) data)) == NULL) {
        return -1;
    }

    node->list = list;

    node->next = _node->next;
    _node->next = node;
    node->prev = _node;

    list->size++;

    /* ======== */
    return 0;
}

/* ================================================================ */

int List_insert_before(List* list, Node* _node, const void* data) {

    Node* node = NULL;
    /* =======*/

    if ((list == NULL) || (((List*)_node->list) != list) || (data == NULL)) {
        return -1;
    }

    if (_node == list->head) {
        return List_insert_head(list, (void*) data);
    }

    if ((node = Node_create((void*) data)) == NULL) {
        return -1;
    }

    node->list = list;

    node->prev = _node->prev;
    _node->prev->next = node;
    _node->prev = node;
    node->next = _node;

    list->size++;

    /* ======== */
    return 0;
}

/* ================================================================ */
