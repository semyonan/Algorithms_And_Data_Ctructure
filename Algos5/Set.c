#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
typedef struct hash_table {
    long memsize; 
    long nonnull;
    long size;   
    int rehashsize; 
    int *val;    
    char *del;   
}hash_table;
 
void init(hash_table *table, long size){
    table->memsize = size;
    table->nonnull = 0;
    table->size = 0;
    table->rehashsize = 75;
    table->val = (int*)malloc(sizeof(int)*table->memsize);
    memset(table->val, 0, sizeof(int)*table->memsize);
    table->del = (char*)malloc(sizeof(char)*table->memsize);
    memset(table->del, 0, sizeof(char)*table->memsize);
}
 
void free_table(hash_table* table) {
    free(table->val);
    free(table->del);
    table->val = NULL;
    table->del = NULL;
}
 
int hash1(hash_table *table, int x) {
    return abs(x) % table->memsize;
}
 
int hash2(hash_table *table, int x) {
    return ((abs(x) % table->memsize)/2)*2 + 1;
}
 
void insert(hash_table* table, int x);
 
void resize_table(hash_table* table) {
    hash_table newtable;
    init(&newtable, table->memsize * 2);
    for (int i = 0; i < table->memsize; i++) {
        if (table->del[i] == 2) {
            insert(&newtable, table->val[i]);
        }
    }
    free_table(table);
    *table = newtable;
}
 
void rehash_table(hash_table* table) {
    hash_table newtable;
    init(&newtable, table->memsize);
    for (int i = 0; i < table->memsize; i++) {
        if (table->del[i] == 2) {
            insert(&newtable, table->val[i]);
        }
    }
    free_table(table);
    *table = newtable;
}
 
void insert(hash_table *table, int x){
 
    if (table->size +1 > (table->rehashsize * table->memsize)/100) {
        resize_table(table);
    } else if (table->nonnull > 2*table->size) {
        rehash_table(table);
    }
 
    int key = hash1(table, x);
    int step = hash2(table, x);
 
    int i = 0;
    int free = -1;
     
    while ((table->del[key] != 0) && (i<table->memsize)) {
        if ((table->val[key] == x) && (table->del[key] == 2)) {
            return;
        }
        if ((table->del[key] == 1) && (free == -1)) {
            free = key;
        }
        i++;
        key = (key + step) % table->memsize;
    }
 
    if (free == -1) {
        table->val[key] = x;
        table->del[key] = 2;
        table->nonnull++;
    } else {
        table->val[free] = x;
        table->del[free] = 2;
    }
    table->size++;
}
 
void delete(hash_table *table, int x){
    int key = hash1(table, x);
    int step = hash2(table, x);
 
    int i = 0;
    while ((table->del[key] != 0) && (i<table->memsize)) {
        if ((table->val[key] == x) && (table->del[key]==2)) {
            table->del[key] = 1;
            table->size--;
            return;
        }
        key = (key + step) % table->memsize;
        i++;
    }
}
 
int exists(hash_table *table, int x){
    int key = hash1(table, x);
    int step = hash2(table, x);
 
    int i = 0;
    while  ((table->del[key] != 0) && (i<table->memsize))  {
        if ((table->val[key] == x) && (table->del[key]==2)) {
            return 1;
        }
        key = (key + step) % table->memsize;
        i++;
    }
    return 0;
}
 
int main() {
    int val;
    hash_table table;
    init(&table, 8);
 
    FILE *fin, *fout;
    fin = fopen("set.in", "r");
    fout = fopen("set.out", "w");
 
    char str[100];
    char *comand;
     
    while (!feof(fin)) {
        str[0] = '\0';
        fgets(str, 100, fin);
        comand = strtok(str, " \n\t");
        if (comand != NULL) {
            if (strcmp(comand, "insert") == 0) {
                val = atoi(strtok(NULL, " \n\t"));
                insert(&table, val);
            } else if (strcmp(comand, "delete") == 0) {
                val = atoi(strtok(NULL, " \n\t"));
                delete(&table, val);
            } else if (strcmp(comand, "exists") == 0) {
                val = atoi(strtok(NULL, " \n\t"));
                if (exists(&table, val) == 1) {
                    fprintf(fout, "true\n");
                } else {
                    fprintf(fout, "false\n");
                }
            }
        }
    }
 
    free_table(&table);
     
    fclose(fin);
    fclose(fout);
 
    return 0;
}