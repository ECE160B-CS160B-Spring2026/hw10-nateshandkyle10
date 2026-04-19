#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct nlist {
    struct nlist *next;
    int value; 
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE];

unsigned hash(int value) {
    unsigned hashval = value;
    if (value < 0) hashval = -value;
    return hashval % HASHSIZE;
}

struct nlist *lookup(int value) {
    struct nlist *np;
    for (np = hashtab[hash(value)]; np != NULL; np = np->next) {
        if (np->value == value) {
            return np;
        }
    }
    return NULL;
}

struct nlist *install(int value) {
    struct nlist *np;
    if ((np = lookup(value)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL) return NULL;
        np->value = value;
        unsigned hashval = hash(value);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    return np;
}

void intersection(int output[], int array1[], int lenArr1, int array2[], int lenArr2) {
    int outIdx = 0;
    
    for (int i = 0; i < HASHSIZE; i++) {
        hashtab[i] = NULL;
    }

    for (int i = 0; i < lenArr1; i++) {
        install(array1[i]);
    }

    for (int i = 0; i < lenArr2; i++) {
        struct nlist* node = lookup(array2[i]);
        
        if (node != NULL && node->value != INT_MIN) {
            output[outIdx++] = array2[i];
            node->value = INT_MIN; 
        }
    }
    
    output[outIdx] = INT_MIN;
}

int main() {
    int lenArr1, lenArr2;

    scanf("%d", &lenArr1);
    int *array1 = (int *)malloc(lenArr1 * sizeof(int));
    for (int i = 0; i < lenArr1; i++) {
        scanf("%d", &array1[i]);
    }

    scanf("%d", &lenArr2);
    int *array2 = (int *)malloc(lenArr2 * sizeof(int));
    for (int i = 0; i < lenArr2; i++) {
        scanf("%d", &array2[i]);
    }

    int minLen = (lenArr1 < lenArr2) ? lenArr1 : lenArr2;
    int *output = (int *)malloc((minLen + 1) * sizeof(int));

    intersection(output, array1, lenArr1, array2, lenArr2);

    int first = 1;
    for (int i = 0; output[i] != INT_MIN; i++) {
        if (!first) {
            printf(" ");
        }
        printf("%d", output[i]);
        first = 0;
    }
    printf("\n");

    free(array1);
    free(array2);
    free(output);

    return 0;
}
