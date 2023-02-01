#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>
 
typedef struct hash_table {
    long memsize; 
    long nonnull;
    long size;    
    int rehashsize; 
    char **key;    
    char *del;   
    char **word;
    int *prev;
    int *next;
}hash_table;
 
void init(hash_table *table, long size){
    table->memsize = size;
    table->nonnull = 0;
    table->size = 0;
    table->rehashsize = 75;
    table->del = (char  * )malloc(sizeof(char) * table->memsize);
    memset(table->del, 0, sizeof(char)*table->memsize);
    table->key = (char**)malloc(sizeof(char*)*table->memsize);
    table->word = (char**)malloc(sizeof(char*)*table->memsize);
    table->key[0] = (char*)malloc(sizeof(char)*21*table->memsize);
    table->word[0] = (char*)malloc(sizeof(char)*21*table->memsize);
    table->prev = (int*)malloc(sizeof(int)*table->memsize);
    table->next = (int*)malloc(sizeof(int)*table->memsize);
    for (int i = 1, j = 21; i < table->memsize; i++, j+=21) {
        table->key[i] = table->key[0]+j;
        table->word[i] = table->word[0]+j;
    }
}
 
void free_table(hash_table* table) {
    free(table->key[0]);
    free(table->word[0]);
    free(table->key);
    free(table->word);
    free(table->del);
    free(table->prev);
    free(table->next);
    table->next = NULL;
    table->prev = NULL;
    table->word = NULL;
    table->key = NULL;
    table->del = NULL;
}
 
int hash1(hash_table *table, char x[]) {
    int hash_result = 0;
    char *pch = x;
    while (*pch != '\0') {
        hash_result = ((hash_result << 5) - hash_result) + *pch;
        pch++;
    }
    hash_result = (hash_result % table->memsize + table->memsize) % table->memsize;
    return hash_result;
}
 
int hash2(hash_table *table, char x[]) {
    int hash_result = 0;
    char *pch = x;
    while (*pch != '\0') {
        hash_result = ((hash_result << 5) + hash_result) + *pch;
        pch++;
    }
    hash_result = (hash_result << 1) + 1;
    hash_result = (hash_result % table->memsize + table->memsize) % table->memsize;
    return hash_result;
}
 
 
void put(hash_table* table, char x[], char y[], int *last, int *first);
 
void resize_table(hash_table* table, int *last, int *first) {
    hash_table newtable;
    init(&newtable, table->memsize * 2);
    int newlast = -1;
    int newfirst = -1;
    while ((*first) != -1) {
        put(&newtable, table->key[(*first)], table->word[(*first)], &newlast, &newfirst);
        (*first) = table->next[(*first)];
    }
    (*first) = newfirst;
    (*last) = newlast;
    free_table(table);
    *table = newtable;
}
 
void rehash_table(hash_table* table, int *last, int *first) {
    hash_table newtable;
    init(&newtable, table->memsize);
    int newlast = -1;
    int newfirst = -1;
    while ((*first) != -1) {
        put(&newtable, table->key[(*first)], table->word[(*first)], &newlast, &newfirst);
        (*first) = table->next[(*first)];
    }
    (*first) = newfirst;
    (*last) = newlast;
    free_table(table);
    *table = newtable;
}
 
void put(hash_table *table, char x[], char y[], int *last, int *first){
 
    if (table->nonnull + 1 > (table->rehashsize * table->memsize)/100) {
        if (table->nonnull > 2 * table->size) {
            rehash_table(table, last, first);
        } else {
            resize_table(table, last, first);
        }
    }
 
    int h1 = hash1(table, x);
    int step = hash2(table, x);
 
    int i = 0;
    int free = -1;
     
    while ((table->del[h1] != 0) && (i < table->memsize)) {
        if ((strcmp(table->key[h1],x) == 0) && (table->del[h1] == 2)) {
            strcpy(table->word[h1], y);
            return;
        }
        if ((table->del[h1] == 1) && (free == -1)) {
            free = h1;
        }
        i++;
        h1 = (h1 + step) % table->memsize;
    }
 
    if (free == -1) {
        strcpy(table->key[h1], x);
        strcpy(table->word[h1], y);
        table->del[h1] = 2;
        table->nonnull++;
        if ((*last) != -1) {
            table->next[(*last)] = h1;
        } else {
            (*first) = h1;
        }
        table->next[h1] = -1;
        table->prev[h1] = (*last);
        (*last) = h1;
    } else {
        strcpy(table->key[free], x);
        strcpy(table->word[free], y);
        table->del[free] = 2;
        if ((*last) != -1) {
            table->next[(*last)] = free;
        } else {
            (*first) = free;
        }
        table->next[free] = -1;
        table->prev[free] = (*last);
        (*last) = free;
    }
    table->size++;
}
 
void delete(hash_table *table, char x[], int *last, int *first) {
    int h1 = hash1(table, x);
    int step = hash2(table, x);
 
    int i = 0;
    while ((table->del[h1] != 0) && (i < table->memsize)) {
        if ((strcmp(table->key[h1],x) == 0) && (table->del[h1] == 2)) {
            table->del[h1] = 1;
            table->size--;
            if (table->next[h1] != -1) {
                table->prev[table->next[h1]] = table->prev[h1];
            } else {
                (*last) = table->prev[h1];
            }
            if (table->prev[h1] != -1) {
                table->next[table->prev[h1]] = table->next[h1];
            } else {
                (*first) = table->next[h1];
            }
            return;
        }
        h1 = (h1 + step) % table->memsize;
        i++;
    }
}
 
int get(hash_table *table, char x[]){
    int h1 = hash1(table, x);
    int step = hash2(table, x);
 
    int i = 0;
    while  ((table->del[h1] != 0) && (i < table->memsize))  {
        if ((strcmp(table->key[h1],x) == 0) && (table->del[h1] == 2)) {
            return h1;
        }
        h1 = (h1 + step) % table->memsize;
        i++;
    }
    return -1;
}
 
int main() {
    hash_table table;
    init(&table, 1024);
 
    FILE *fin, *fout;
    fin = fopen("linkedmap.in", "r");
    fout = fopen("linkedmap.out", "w");
 
    char str[100];
    char *key;
    char *word;
    int last = -1;
    int first = -1;
    int ind = -1;
 
    char *command;
     
    while (!feof(fin)) {
        str[0] = '\0';
        fgets(str, 100, fin);
        command = strtok(str, " \n\t");
        if (command != NULL) {
            if (strcmp(command, "put") == 0) {
                key = strtok(NULL, " \n\t");
                word = strtok(NULL, " \n\t");
                put(&table, key, word, &last, &first);
            } else if (strcmp(command, "delete") == 0) {
                key = strtok(NULL, " \n\t");
                delete(&table, key, &last, &first);
            } else if (strcmp(command, "get") == 0) {
                key = strtok(NULL, " \n\t");
                ind = get(&table, key);
                if (ind != -1) {
                    fprintf(fout, "%s\n", table.word[ind]);
                } else {
                    fprintf(fout, "none\n");
                }
            } else if (strcmp(command, "prev") == 0) {
                key = strtok(NULL, " \n\t");
                ind = get(&table, key);
                if ((ind != -1) && (table.prev[ind] != -1)) {
                    fprintf(fout, "%s\n", table.word[table.prev[ind]]);
                } else {
                    fprintf(fout, "none\n");
                }
            } else if (strcmp(command, "next") == 0) {
                key = strtok(NULL, " \n\t");
                ind = get(&table, key);
                if ((ind != -1) && (table.next[ind] != -1))  {
                    fprintf(fout, "%s\n", table.word[table.next[ind]]);
                } else {
                    fprintf(fout, "none\n");
                }
            }
        }
    }
 
    free_table(&table);
     
    fclose(fin);
    fclose(fout);
 
    return 0;
}