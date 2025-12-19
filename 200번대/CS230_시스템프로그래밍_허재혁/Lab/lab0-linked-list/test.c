#include <assert.h>
#include "list.h"

void setup_head_tail(struct list_node **head, struct list_node **tail)
{
    *head = allocate_node_with_key(0);
    *tail = allocate_node_with_key(0);
    initialize_list_head_tail(*head, *tail);
}

void test_allocate_head_tail() {
    struct list_node *head, *tail;

    setup_head_tail(&head, &tail);

    //Empty Check
    assert (head->next == tail);
    assert (tail->prev == head);

    // Doubly linked list invariant
    assert (head->prev == tail);
    assert (tail->next == head);
}

void test_is_initally_empty() {
    struct list_node *head, *tail;

    setup_head_tail(&head, &tail);

    assert(is_list_empty(head));
}

void test_insert_node_after_test() {
    struct list_node *head, *tail;

    setup_head_tail(&head, &tail);

    struct list_node *new_node;
    struct list_node *insertion_point = head;
    for (int i = 0; i < 10; i++) {
        new_node = allocate_node_with_key(i+1);
        insert_node_after(insertion_point, new_node);

        assert(insertion_point->next == new_node);
        insertion_point = insertion_point->next;
    }

    struct list_node *node = head->next;
    int idx = 1;
    // Check forward
    while (node != tail) {
        assert(idx == node->key);
        idx++;
        node = node->next;
    }

    // Check backward
    idx = 10;
    node = tail->prev;
    while (node != head) {
        assert(idx == node->key);
        idx--;
        node = node->prev;
    }

    // Doubly linked list invariant
    assert (head->prev == tail);
    assert (tail->next == head);
}

void test_insert_front() {
    struct list_node *head, *tail;

    setup_head_tail(&head, &tail);

    struct list_node *new_node;
    struct list_node *insertion_point = head;
    for (int i = 0; i < 10; i++) {
        new_node = allocate_node_with_key(i+1);
        insert_node_after(insertion_point, new_node);

        assert(insertion_point->next == new_node);
    }

    struct list_node *node = head->next;
    int idx = 10;
    // Check forward
    while (node != tail) {
        assert(idx == node->key);
        idx--;
        node = node->next;
    }

    // Check backward
    idx = 1;
    node = tail->prev;
    while (node != head) {
        assert(idx == node->key);
        idx++;
        node = node->prev;
    }

    // Doubly linked list invariant
    assert (head->prev == tail);
    assert (tail->next == head);
}

void test_insert_then_search() {
    struct list_node *head, *tail;

    setup_head_tail(&head, &tail);

    struct list_node *new_node;
    struct list_node *insertion_point = head;
    for (int i = 0; i < 10; i++) {
        new_node = allocate_node_with_key(i+1);
        insert_node_after(insertion_point, new_node);

        assert(insertion_point->next == new_node);
        insertion_point = insertion_point->next;
    }

    struct list_node *node = NULL;

    // Check Search functionality
    for (int i = 0; i < 10; i++) {
        node = search_list(head, i+1);
        assert(node);
        assert(node->key == i+1);
    }

    // Doubly linked list invariant
    assert (head->prev == tail);
    assert (tail->next == head);
}

void test_insert_then_search_delete() {
    struct list_node *head, *tail;

    setup_head_tail(&head, &tail);

    struct list_node *new_node;
    struct list_node *insertion_point = head;
    for (int i = 0; i < 10; i++) {
        new_node = allocate_node_with_key(i+1);
        insert_node_after(insertion_point, new_node);

        assert(insertion_point->next == new_node);
        insertion_point = insertion_point->next;
    }

    struct list_node *node = NULL;

    // Check Search functionality
    for (int i = 10; i > 0; i--) {
        node = search_list(head, i);
        assert(node); // Checks search_list does not return NULL
        assert(node->key == i);
        del_node(node);
    }

    // Doubly linked list invariant
    assert (head->prev == tail);
    assert (tail->next == head);
}

void test_insert_delete_and_count() {
    struct list_node *head, *tail;

    setup_head_tail(&head, &tail);

    struct list_node *new_node;
    struct list_node *insertion_point = head;
    for (int i = 0; i < 10; i++) {
        new_node = allocate_node_with_key(i+1);
        insert_node_after(insertion_point, new_node);

        assert(insertion_point->next == new_node);
        insertion_point = insertion_point->next;
    }

    assert(count_list_length(head) == 10);

    struct list_node *node = NULL;

    // Check Search functionality
    for (int i = 10; i > 0; i--) {
        node = search_list(head, i);
        assert(node); // Checks search_list does not return NULL
        assert(node->key == i);
        del_node(node);

        assert(count_list_length(head) == i-1);
    }
    assert(count_list_length(head) == 0);
    assert(is_list_empty(head));

    // Doubly linked list invariant
    assert (head->prev == tail);
    assert (tail->next == head);
}

void test_insert_random_sorted_check_sorted () {
    int random_vals[] = {17, 20, 8, 3, 11, 2, 5, 14, 7, 9, 13, 1, 16, 15, 4, 6, 10, 12, 19, 18};
    int num_random_vals = 20;
    int sum_of_inserted = 0;

    struct list_node *head, *tail;

    setup_head_tail(&head, &tail);

    for (int i = 0; i < num_random_vals; i++) {
        struct list_node *new_node = allocate_node_with_key(random_vals[i]);
        insert_sorted_by_key(head, new_node);
        sum_of_inserted += new_node->key;
    }

    assert(count_list_length(head) == 20);

    struct list_node *node = head->next;
    int prev_key = head->key;
    int sum_inserted_keys = 0;

    while (node != tail) {
        assert(prev_key < node->key);

        sum_inserted_keys += node->key;

        prev_key = node->key;
        node = node->next;
    }

    assert(sum_of_inserted == sum_inserted_keys);

    // Doubly linked list invariant
    assert (head->prev == tail);
    assert (tail->next == head);
}

int main()
{
    test_allocate_head_tail();
    test_is_initally_empty();
    test_insert_node_after_test();
    test_insert_front();
    test_insert_then_search();
    test_insert_then_search_delete();
    test_insert_delete_and_count();
    test_insert_random_sorted_check_sorted ();
    return 0;
}
