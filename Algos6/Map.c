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
}hash_table;
 
void init(hash_table *table, long size){
    table->memsize = size;
    table->nonnull = 0;
    table->size = 0;
    table->rehashsize = 75;
    table->del = (char*)malloc(sizeof(char)*table->memsize);
    memset(table->del, 0, sizeof(char)*table->memsize);
    table->key = (char**)malloc(sizeof(char*)*table->memsize);
    table->word = (char**)malloc(sizeof(char*)*table->memsize);
    table->key[0] = (char*)malloc(sizeof(char)*21*table->memsize);
    table->word[0] = (char*)malloc(sizeof(char)*21*table->memsize);
    for (int i = 1; i < table->memsize; i++) {
        table->key[i] = table->key[0]+ i * 21;
        table->word[i] = table->word[0] + i * 21;
    }
}
 
void free_table(hash_table* table) {
    free(table->key[0]);
    free(table->word[0]);
    free(table->key);
    free(table->word);
    free(table->del);
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
 
 
void put(hash_table* table, char x[], char y[]);
 
void resize_table(hash_table* table) {
    hash_table newtable;
    init(&newtable, table->memsize * 2);
    for (int i = 0; i < table->memsize; i++) {
        if (table->del[i] == 2) {
            put(&newtable, table->key[i], table->word[i]);
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
            put(&newtable, table->key[i], table->word[i]);
        }
    }
    free_table(table);
    *table = newtable;
}
 
void put(hash_table *table, char x[], char y[]){
 
    if (table->size + 1 > (table->rehashsize * table->memsize)/100) {
        resize_table(table);
    } else if (table->nonnull > 2 * table->size) {
        rehash_table(table);
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
    } else {
        strcpy(table->key[free], x);
        strcpy(table->word[free], y);
        table->del[free] = 2;
    }
    table->size++;
}
 
void delete(hash_table *table, char x[]){
    int h1 = hash1(table, x);
    int step = hash2(table, x);
 
    int i = 0;
    while ((table->del[h1] != 0) && (i < table->memsize)) {
        if ((strcmp(table->key[h1],x) == 0) && (table->del[h1] == 2)) {
            table->del[h1] = 1;
            table->size--;
            return;
        }
        h1 = (h1 + step) % table->memsize;
        i++;
    }
}
 
char* get(hash_table *table, char x[]){
    int h1 = hash1(table, x);
    int step = hash2(table, x);
 
    int i = 0;
    while  ((table->del[h1] != 0) && (i < table->memsize))  {
        if ((strcmp(table->key[h1],x) == 0) && (table->del[h1] == 2)) {
            return table->word[h1];
        }
        h1 = (h1 + step) % table->memsize;
        i++;
    }
    return "none";
}
 
int main() {
    hash_table table;
    init(&table, 1024);
 
    FILE *fin, *fout;
    fin = fopen("map.in", "r");
    fout = fopen("map.out", "w");
 
    char str[100];
    char *key;
    char *word;
 
    char *command;
     
    while (!feof(fin)) {
        str[0] = '\0';
        fgets(str, 100, fin);
        command = strtok(str, " \n\t");
        if (command != NULL) {
            if (strcmp(command, "put") == 0) {
                key = strtok(NULL, " \n\t");
                word = strtok(NULL, " \n\t");
                put(&table, key, word);
            } else if (strcmp(command, "delete") == 0) {
                key = strtok(NULL, " \n\t");
                delete(&table, key);
            } else if (strcmp(command, "get") == 0) {
                key = strtok(NULL, " \n\t");
                fprintf(fout, "%s\n", get(&table, key));
            }
        }
    }
 
    free_table(&table);
     
    fclose(fin);
    fclose(fout);
 
    return 0;
}