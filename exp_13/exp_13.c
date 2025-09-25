#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORD_MAX 100
#define MEANING_MAX 512

typedef struct Node {
    char *word;
    char *meaning;
    struct Node *left;
    struct Node *right;
} Node;
Node* createNode(const char *word, const char *meaning) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(EXIT_FAILURE); }
    n->word = (char*)malloc(strlen(word) + 1);
    n->meaning = (char*)malloc(strlen(meaning) + 1);
    if (!n->word || !n->meaning) { perror("malloc"); exit(EXIT_FAILURE); }
    strcpy(n->word, word);
    strcpy(n->meaning, meaning);
    n->left = n->right = NULL;
    return n;
}
int strCaseCmp(const char *a, const char *b) {
    while (*a && *b) {
        int ca = tolower((unsigned char)*a);
        int cb = tolower((unsigned char)*b);
        if (ca != cb) return ca - cb;
        a++; b++;
    }
    return (unsigned char)tolower((unsigned char)*a) - (unsigned char)tolower((unsigned char)*b);
}

Node* insertNode(Node *root, const char *word, const char *meaning) {
    if (root == NULL) {
        return createNode(word, meaning);
    }
    int cmp = strCaseCmp(word, root->word);
    if (cmp < 0) {
        root->left = insertNode(root->left, word, meaning);
    } else if (cmp > 0) {
        root->right = insertNode(root->right, word, meaning);
    } else {
        free(root->meaning);
        root->meaning = (char*)malloc(strlen(meaning) + 1);
        if (!root->meaning) { perror("malloc"); exit(EXIT_FAILURE); }
        strcpy(root->meaning, meaning);
    }
    return root;
}

void freeNode(Node *n) {
    if (!n) return;
    free(n->word);
    free(n->meaning);
    free(n);
}



Node* searchNode(Node *root, const char *word) {
    if (!root) return NULL;
    int cmp = strCaseCmp(word, root->word);
    if (cmp == 0) return root;
    if (cmp < 0) return searchNode(root->left, word);
    return searchNode(root->right, word);
}

Node* findMin(Node *root) {
    if (!root) return NULL;
    while (root->left) root = root->left;
    return root;
}



void inorderDisplay(Node *root) {
    if (!root) return;
    inorderDisplay(root->left);
    printf("  %s : %s\n", root->word, root->meaning);
    inorderDisplay(root->right);
}

void freeTree(Node *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    freeNode(root);
}

void readLine(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (!fgets(buffer, (int)size, stdin)) {
        buffer[0] = '\0';
        return;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
}
Node* deleteNode(Node *root, const char *word) {
    if (!root) return NULL;
    int cmp = strCaseCmp(word, root->word);
    if (cmp < 0) {
        root->left = deleteNode(root->left, word);
    } else if (cmp > 0) {
        root->right = deleteNode(root->right, word);
    } else {
        if (!root->left && !root->right) {
            freeNode(root);
            return NULL;
        } else if (!root->left) {
            Node *r = root->right;
            freeNode(root);
            return r;
        } else if (!root->right) {
            Node *l = root->left;
            freeNode(root);
            return l;
        } else {
            Node *succ = findMin(root->right);
            char *tmpWord = root->word;
            char *tmpMeaning = root->meaning;
            root->word = (char*)malloc(strlen(succ->word) + 1);
            root->meaning = (char*)malloc(strlen(succ->meaning) + 1);
            if (!root->word || !root->meaning) { perror("malloc"); exit(EXIT_FAILURE); }
            strcpy(root->word, succ->word);
            strcpy(root->meaning, succ->meaning);
            free(tmpWord);
            free(tmpMeaning);
            root->right = deleteNode(root->right, succ->word);
        }
    }
    return root;
}

int main(void) {
    Node *root = NULL;
    char word[WORD_MAX];
    char meaning[MEANING_MAX];
    char choiceStr[8];

    printf("=== Dictionary ===\n");
    while (1) {
        printf("\nMenu:\n");
        printf("  1. Find The meaning of a word\n");
        printf("  2. Add a word and meaning to dictionary\n");
        printf("  3. Remove a word from dictionary\n");
        printf("  4. Display all words with meaning \n");
        printf("  5. Exit\n");
        readLine("Enter choice : ", choiceStr, sizeof(choiceStr));
        int choice = atoi(choiceStr);

        switch (choice) {
            case 1:
                readLine("Enter the word : ", word, sizeof(word));
                if (strlen(word) == 0) { printf("No word entered.\n"); break; }
                {
                    Node *found = searchNode(root, word);
                    if (found) printf("Meaning of '%s': %s\n", found->word, found->meaning);
                    else printf("'%s' not found in dictionary.\n", word);
                }
                break;

            case 2:
                readLine("Enter word to add: ", word, sizeof(word));
                if (strlen(word) == 0) { printf("No word entered.\n"); break; }
                readLine("Enter meaning of the word: ", meaning, sizeof(meaning));
                root = insertNode(root, word, meaning);
                printf("Inserted '%s'.\n", word);
                break;

            case 3:
                readLine("Enter word to remove: ", word, sizeof(word));
                if (strlen(word) == 0) { printf("No word entered.\n"); break; }
                if (searchNode(root, word)) {
                    root = deleteNode(root, word);
                    printf("'%s' removed successfully\n", word);
                } else {
                    printf("'%s' not found  \n", word);
                }
                break;

            case 4:
                if (!root) printf("(Dictionary is empty)\n");
                else {
                    printf("Dictionary contents:\n");
                    inorderDisplay(root);
                }
                break;

            case 5:
                freeTree(root);
                printf("Exiting....\n");
                return 0;

            default:
                printf("Invalid choice...enter valid input!!\n");
        }
    }
    return 0;
}
