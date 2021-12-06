#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
 
#define MAX_LEVEL 6
 
typedef struct node {
    int key;
    int value;
    struct node **forward;
} node;
 
typedef struct skiplist {
    int level;
    int size;
    struct node *header;
} skiplist;
 
skiplist *skiplist_init(skiplist *list) {
    int i;
    node *header = (node *) malloc(sizeof(node));
    list->header = header;
    header->key = INT_MAX;
    header->forward = (node **) malloc(
            sizeof(node*) * (MAX_LEVEL + 1));
    for (i = 0; i <= MAX_LEVEL; i++) {
        header->forward[i] = list->header;
    }
 
    list->level = 1;
    list->size = 0;
 
    return list;
}
 
static int rand_level() {
    int level = 1;
    while (rand() < RAND_MAX / 2 && level < MAX_LEVEL)
        level++;
    return level;
}
 
int skiplist_insert(skiplist *list, int key, int value) {
    node *update[MAX_LEVEL + 1];
    node *x = list->header;
    int i, level;
    for (i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key)
            x = x->forward[i];
        update[i] = x;
    }
    x = x->forward[1];
 
    if (key == x->key) {
        x->value = value;
        return 0;
    } 
    else {
        level = rand_level();
        if (level > list->level) {
            for (i = list->level + 1; i <= level; i++) {
                update[i] = list->header;
            }
            list->level = level;
        }
 
        x = (node *) malloc(sizeof(node));
        x->key = key;
        x->value = value;
        x->forward = (node **) malloc(sizeof(node*) * (level + 1));
        for (i = 1; i <= level; i++) {
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
    }
    return 0;
}
 
node *skiplist_search(skiplist *list, int key) {
    node *x = list->header;
    int i;
    for (i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key)
            x = x->forward[i];
    }
    if (x->forward[1]->key == key)
        return x->forward[1]; 
    else
        return NULL;
}
 
static void skiplist_node_free(node *x) {
    if (x) {
        free(x->forward);
        free(x);
    }
}
 
int skiplist_delete(skiplist *list, int key) {
    int i;
    node *update[MAX_LEVEL + 1];
    node *x = list->header;
    for (i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key)
            x = x->forward[i];
        update[i] = x;
    }
 
    x = x->forward[1];
    if (x->key == key) {
        for (i = 1; i <= list->level; i++) {
            if (update[i]->forward[i] != x)
                break;
            update[i]->forward[1] = x->forward[i];
        }
        skiplist_node_free(x);
 
        while (list->level > 1 && list->header->forward[list->level]
                == list->header)
            list->level--;
        return 0;
    }
    return 1;
}
 
static void skiplist_dump(skiplist *list) {
    node *x = list->header;
    while (x && x->forward[1] != list->header) {
        printf("%d[%d]->", x->forward[1]->key, x->forward[1]->value);
        x = x->forward[1];
    }
    printf("NIL\n");
}
 
int main() {
    skiplist list;
    skiplist_init(&list);
    int choice = 0, data;
    printf("Enter 1 for insertion\n");
    printf("Enter 2 for deletion\n");
    printf("Enter 3 to search the list\n");
    printf("Enter 4 for printing the list\n");
    while(choice!=-1) {
        printf("Enter your choice : ");
        scanf("%d", &choice);
        if(choice == -1)
            break;
        switch(choice) {
            case 1: printf("Enter the data : ");
                    scanf("%d", &data);
                    skiplist_insert(&list, data, data);
                    printf("Inserted\n");
                    break;
            case 2: printf("Enter the key to delete :");
                    scanf("%d", &data);
                    skiplist_delete(&list, data);
                    break;
            case 3: printf("Enter the key to be searched : ");
                    scanf("%d", &data);
                    if( skiplist_search(&list, data) == NULL)
                        printf("%d not found in the list\n", data);
                    else
                        printf("%d found in the list\n", data);
                    break;
            case 4: skiplist_dump(&list);
                    break;
            default: printf("Invalid Selection\n");
        }
    }
    return 0;
}
