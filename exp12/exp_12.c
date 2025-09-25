#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100


struct Node {
    char data;
    struct Node* left;
    struct Node* right;
};


struct Stack {
    int top;
    struct Node* items[MAX];
};


void push(struct Stack* s, struct Node* node);
struct Node* pop(struct Stack* s);
int precedence(char op);
int isOperand(char c);
struct Node* createNode(char data);
struct Node* buildSubtree(struct Stack* operatorStack, struct Stack* nodeStack);
struct Node* constructExpressionTree(char* expression);
void preorder(struct Node* root);
void postorder(struct Node* root);


int main() {
    char expression[MAX];
    
    printf("Enter the expression: ");
    scanf("%s", expression);
    
    struct Node* root = constructExpressionTree(expression);
    
    printf("Prefix Expression: ");
    preorder(root);
    
    printf("\nPostfix Expression: ");
    postorder(root);
    
    return 0;
}


void push(struct Stack* s, struct Node* node) {
    s->items[++(s->top)] = node;
}


struct Node* pop(struct Stack* s) {
    return s->items[(s->top)--];
}


int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}


int isOperand(char c) {
    return isalpha(c) || isdigit(c);
}


struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}


struct Node* buildSubtree(struct Stack* operatorStack, struct Stack* nodeStack) {
    struct Node* root = pop(operatorStack);
    struct Node* rightChild = pop(nodeStack);
    struct Node* leftChild = pop(nodeStack);
    
    root->left = leftChild;
    root->right = rightChild;
    
    push(nodeStack, root);
    return root;
}


struct Node* constructExpressionTree(char* expression) {
    struct Stack operatorStack = {-1};  
    struct Stack nodeStack = {-1};      
    
    for (int i = 0; expression[i] != '\0'; i++) {
        char c = expression[i];
        
        if (isOperand(c)) {
            struct Node* newNode = createNode(c);
            push(&nodeStack, newNode);
        }
        else if (c == '(') {
            push(&operatorStack, createNode(c));
        }
        else if (c == ')') {
            while (operatorStack.top != -1 && operatorStack.items[operatorStack.top]->data != '(') {
                buildSubtree(&operatorStack, &nodeStack);
            }
            pop(&operatorStack);  
        }
        else {  
            while (operatorStack.top != -1 && operatorStack.items[operatorStack.top]->data != '(' &&
                   precedence(operatorStack.items[operatorStack.top]->data) >= precedence(c)) {
                buildSubtree(&operatorStack, &nodeStack);
            }
            struct Node* newNode = createNode(c);
            push(&operatorStack, newNode);
        }
    }
    
    while (operatorStack.top != -1) {
        buildSubtree(&operatorStack, &nodeStack);
    }
    
    return pop(&nodeStack); 
}


void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%c ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}


void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%c ", root->data);
    }
}
