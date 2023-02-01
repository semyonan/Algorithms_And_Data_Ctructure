#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    long value;
    struct list *next;
}list;

void push(list **head, long data) {
    list *tmp = (list*)malloc(sizeof(list));
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
}

int pop(list **head) {
    list* prev = NULL;
    long val;
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
    int n, val, el1, el2;
    val = 0;
    n = 0;
    char c[2]; 
    

    FILE *fin, *fout;
    fin = fopen("postfix.in", "r");
    fout = fopen("postfix.out", "w");

    list *head = NULL;

    while (fscanf(fin, "%s ", &c) != EOF) {
        if (strcmp(c,"+") == 0) {
            val = pop(&head) + pop(&head);
            push(&head, val);
        }
        else if (strcmp(c,"-") == 0) {
            el1 = pop(&head);
            el2 = pop(&head);
            val = el2 - el1;
            push(&head, val);
        }
        else if (strcmp(c,"*") == 0) {
            val = pop(&head)*pop(&head);
            push(&head, val);
        }
        else {
            val = atoi(c);
            push(&head, val);
        }
        
    }
    
    fprintf(fout, "%d\n", head->value);

    fclose(fin);
    fclose(fout);

    return 0;
}