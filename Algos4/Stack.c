#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int value;
    struct list *next;
}list;

void push(list **head, int data) {
    list *tmp = (list*)malloc(sizeof(list));
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
}

int pop(list **head) {
    list* prev = NULL;
    int val;
    if (head == NULL) {
        exit(-1);
    }
    prev = (*head);
    val = prev->value;
    (*head) = (*head)->next;
    free(prev);
    return val;
}

int main() {
    int n, val;
    char c[2];

    FILE *fin, *fout;
    fin = fopen("stack.in", "r");
    fout = fopen("stack.out", "w");

    list *head = NULL;
        
    fscanf (fin, "%d\n", &n);
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%s", &c);
        if (strcmp(c, "+") == 0) {
            fscanf(fin, "%d", &val);
            push(&head, val);
        }
        else {
            fprintf(fout, "%d\n", pop(&head));
        }

    }

    fclose(fin);
    fclose(fout);


    return 0;
}