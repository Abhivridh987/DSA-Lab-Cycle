#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LEN 50

// Node structure
typedef struct Node {
    char word[WORD_LEN];
    struct Node *next;
} Node;

Node* createNode(char *w) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->word, w);
    newNode->next = NULL;
    return newNode;
}

void insertEnd(Node **head, char *w) {
    Node *newNode = createNode(w);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
}

int findAndReplace(Node *head, char *key, char *replacement) {
    int count = 0;
    Node *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->word, key) == 0) {
            strcpy(temp->word, replacement);
            count++;
        }
        temp = temp->next;
    }
    return count;
}

void display(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%s ", temp->word);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node *doc = NULL;
    char text[500], key[WORD_LEN], replacement[WORD_LEN];

    printf("Enter the text document (end with newline):\n");
    fgets(text, sizeof(text), stdin);

    // Split text into words and insert into linked list
    char *token = strtok(text, " \n");
    while (token != NULL) {
        insertEnd(&doc, token);
        token = strtok(NULL, " \n");
    }

    printf("Enter the word to find: ");
    scanf("%s", key);

    printf("Enter the replacement word: ");
    scanf("%s", replacement);

    int changes = findAndReplace(doc, key, replacement);

    printf("\nNumber of replacements: %d\n", changes);
    printf("Updated Document: ");
    display(doc);

    return 0;
}

