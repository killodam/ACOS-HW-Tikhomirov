#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *append(Node *head, int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) { fprintf(stderr, "malloc failed\n"); exit(1); }
    node->value = val;
    node->next  = NULL;

    if (!head) return node;

    Node *cur = head;
    while (cur->next) cur = cur->next;
    cur->next = node;
    return head;
}

Node *reverse(Node *head) {
    Node *prev = NULL, *curr = head;
    while (curr) {
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

void print_list(Node *head) {
    for (Node *n = head; n; n = n->next)
        printf("%d ", n->value);
    printf("\n");
}

void free_list(Node *head) {
    while (head) {
        Node *tmp = head->next;
        free(head);
        head = tmp;
    }
}

int main(void) {
    Node *head = NULL;
    int val;
    printf("Enter integers (0 to stop):\n");
    while (scanf("%d", &val) == 1 && val != 0)
        head = append(head, val);

    head = reverse(head);

    printf("Reversed list: ");
    print_list(head);

    free_list(head);
    return 0;
}
