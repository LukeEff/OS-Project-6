#include "myalloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_data(struct block* head) {
    struct block* b = head;

    if (b == NULL) {
        printf("[empty]\n");
        return;
    }

    while (b != NULL) {
        // Uncomment the following line if you want to see the pointer values
        // printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
        printf("[%d,%s]", b->size, b->in_use ? "used" : "free");
        if (b->next != NULL) {
            printf(" -> ");
        }

        b = b->next;
    }

    printf("\n");
}

void* myalloc(struct block** head, int amount) {
    if (*head == NULL) {
        *head = sbrk(1024);
        (*head)->next = NULL;
        (*head)->size = 1024 - PADDED_SIZE(sizeof(struct block));
        (*head)->in_use = 0;
    }
    struct block* pointer = *head;
    while (pointer != NULL) {
        if (pointer->in_use == 0 && pointer->size >= amount) {
            pointer->in_use = 1;
            int padded_block_size = PADDED_SIZE(sizeof(struct block));

            return PTR_OFFSET(pointer, padded_block_size);
        }
        pointer = pointer->next;
    }
    return NULL;
}

int main() {
    struct block* head = NULL;
    void* p;

    print_data(head);
    p = myalloc(&head, 64);
    print_data(head);

    return 0;
}
