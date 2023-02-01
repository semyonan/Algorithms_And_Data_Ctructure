#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    char bracket;
    struct list *next;
}list;

void push(list **head, char data) {
    list *tmp = (list*)malloc(sizeof(list));
    tmp->bracket = data;
    tmp->next = (*head);
    (*head) = tmp;
}

char pop(list **head) {
    list* prev = NULL;
    char brack;
    if (head == NULL) {
        exit(-1);
    }
    prev = (*head);
    brack = prev->bracket;
    (*head) = (*head)->next;
    free(prev);
    return brack;
}

int main() {
    int flag;
    char c, c2;

    FILE *fin, *fout;
    fin = fopen("brackets.in", "r");
    fout = fopen("brackets.out", "w");

    list *head = NULL;

    c = fgetc(fin);
    while(c != EOF) {
        flag = 1;    
        while ((flag != 0) && (c != '\n') && (c != EOF)) {
            if ((c == '(') || (c == '[')) {
                push(&head, c);
            }
            else {
                if (head != NULL) {
                    c2 = pop(&head);
                    if (((c2 != '(') || (c != ')')) && ((c2 != '[') || (c != ']'))) {
                        flag = 0; 
                    }
                }
                else {
                    flag = 0;
                }
            }
            c = fgetc(fin);
        }
        if ((flag == 1) && (head == NULL)) {
            fprintf(fout, "YES\n"); 
        }
        else {
            while ((c != '\n') && (c != EOF)) {
                c = fgetc(fin);
            }
            fprintf(fout, "NO\n");
            head = NULL;
        }
        if (c == '\n') {
            c = fgetc(fin);
        }
    }

    fclose(fin);
    fclose(fout);

    return 0;
}