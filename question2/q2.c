#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    char *word;
    int count;
    struct Node *left;
    struct Node *right;
} Node; //creates the Node struct

Node *insert(Node *root, char *word, int count) {
    if (root == NULL) {
        Node *n = malloc(sizeof(Node));
        n->word = strdup(word);
        n->count = count;
        n->left = n->right = NULL;
        return n;
    }
    if (count < root->count)
        root->left = insert(root->left, word, count);
    else
        root->right = insert(root->right, word, count);

    return root;
} //function to insert a node

void inorder(Node *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%s: %d\n", root->word, root->count);
    inorder(root->right);
}// inorder traversal prints least to greatest


int finder(char **words, int *counts, char *word, int *unique) {
    for (int i = 0; i < *unique; i++) {
        if (strcmp(words[i], word) == 0) {
            counts[i]++;
            return 0;
        }
    }

    words[*unique] = strdup(word);
    counts[(*unique)++] = 1;
    return 1;
} //This function was intialloy intended to just find the number of unique words but now it also finds how many of the word is in the function

int main() {
    FILE *fptr = stdin;
    char line[256];
    int wordCount = 0;

    while (fgets(line, sizeof(line), fptr) != NULL) {
        char *word = strtok(line, " \t\n");
        while (word != NULL) {
            wordCount++;
            word = strtok(NULL, " \t\n");
        }
    } //Finds the number of words

    rewind(fptr);  // go back to start

    char* uniWords[wordCount];
    int uniCount[wordCount];
    memset(uniCount, 0, wordCount); //set uniCount all to zero 

    int unique = 0;

    while (fgets(line, sizeof(line), fptr) != NULL) {
        char *word = strtok(line, " \t\n");
        while (word != NULL) {
            finder(uniWords, uniCount, word, &unique);
            word = strtok(NULL, " \t\n");
        }
    } //Checks every word and finds the total counts

    Node *root = NULL;

    for (int i = 0; i < unique; i++)
        root = insert(root, uniWords[i], uniCount[i]); //insert every element into the tree

    inorder(root); //print the tree in order


}