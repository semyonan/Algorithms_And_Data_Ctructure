#include <stdio.h>
#include <stdlib.h>
 
typedef struct list {
    int value;
    struct list *next;
}list;
 
void push(list **head, int data) {
    list *tmp = (list*)malloc(sizeof(list));
    tmp->value = data;
    tmp->next = NULL;
    if ((*head) != NULL) {
        (*head)->next = tmp;
    }
    (*head) = tmp;
}
 
int pop(list **tail) {
    list* Nextel = NULL;
    int val;
    if (tail == NULL) {
        exit(-1);
    }
    Nextel = (*tail);
    val = Nextel->value;
    (*tail) = Nextel->next;
    free(Nextel);
    return val;
}  
 
 int main(){
    int n, val;
    char c[2];
 
    FILE *fin, *fout;
    fin = fopen("queue.in", "r");
    fout = fopen("queue.out", "w");
 
    list *head = NULL;
    list *tail = NULL;
         
    fscanf (fin, "%d\n", &n);
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%s", &c);
        if (strcmp(c, "+") == 0) {
            fscanf(fin, "%d", &val);
            push(&head, val);
            if (tail == NULL) {
                tail = head;
            }
        }
        else {
            fprintf(fout, "%d\n", pop(&tail));
            if(tail == NULL) {
                head = tail;
            }
        }
 
    }
 
    fclose(fin);
    fclose(fout);
 
 
    return 0;
}