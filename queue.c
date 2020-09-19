#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    /* ANS: Make the queue NULL */
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    } else {
        q = NULL;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    /* It consists queue_t, list_ele_t, and string in list_ele_t */
    list_ele_t *curr_ele_ptr;
    if (q) {
        curr_ele_ptr = q->head;
    } else
        curr_ele_ptr = NULL;
    while (curr_ele_ptr) {
        list_ele_t *past_ele_ptr = curr_ele_ptr;
        free(curr_ele_ptr->value);
        curr_ele_ptr = curr_ele_ptr->next;
        free(past_ele_ptr);
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_create_elem(queue_t *q, char *s, list_ele_t **newelem)
{
    if (!q)
        return false;

    /* TODO: What should you do if the q is NULL? */
    *newelem = malloc(sizeof(list_ele_t));

    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (*newelem) {
        size_t len = strlen(s) + 1;
        (*newelem)->value = malloc(sizeof(char) * len);
        if ((*newelem)->value) {
            strncpy((*newelem)->value, s, len);
        } else {
            free(*newelem);
            return false;
        }
        return true;
    } else
        return false;
}
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newelem;
    bool ret = q_create_elem(q, s, &newelem);
    if (ret) {
        // Update q when all data are ready
        if (q->head == NULL)
            q->tail = newelem;
        newelem->next = q->head;
        q->head = newelem;
        q->size++;
    }
    return ret;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newelem;
    bool ret = q_create_elem(q, s, &newelem);
    if (ret) {
        // Update q when all data are ready
        newelem->next = NULL;
        if (q->head == NULL) {
            q->head = newelem;
            q->tail = newelem;
        } else {
            q->tail->next = newelem;
            q->tail = newelem;
        }
        q->size++;
    }
    return ret;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q) {
        if (q->size > 0) {
            if (q->tail == q->head)
                q->tail = NULL;
            strncpy(sp, q->head->value, bufsize);
            sp[bufsize - 1] = 0;
            free(q->head->value);
            list_ele_t *pasthead = q->head;
            q->head = q->head->next;
            free(pasthead);
            q->size--;
            return true;
        } else
            return false;
    } else
        return false;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: Remove the above comment when you are about to implement. */
    if (q)
        return q->size;
    return 0;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: Remove the above comment when you are about to implement. */
    if (q) {
        list_ele_t *curr, *oldprev, *oldnext;
        curr = q->head;
        oldprev = NULL;
        while (curr) {
            oldnext = curr->next;
            curr->next = oldprev;
            oldprev = curr;
            curr = oldnext;
        }
        // Swapping
        oldprev = q->head;
        q->head = q->tail;
        q->tail = oldprev;
    }
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    // Use bubble sort
    if (q) {
        list_ele_t *curr;
        for (int remaining = q->size; remaining > 0; remaining--) {
            curr = q->head;
            list_ele_t **prev_indirect = &(q->head);
            int iter = 0;
            while (curr) {
                iter++;
                if (iter > remaining)
                    break;
                // compare and swap
                if (curr->next) {
                    int cmp = strcmp(curr->value, curr->next->value);
                    if (cmp > 0) {
                        list_ele_t *oldnextnext;
                        // *prev_indirect -> curr -> currnext
                        *prev_indirect = curr->next;
                        oldnextnext = curr->next->next;
                        curr->next->next = curr;
                        curr->next = oldnextnext;
                    }
                }
                prev_indirect = &(curr->next);
                curr = curr->next;
            }
        }
    }
}
