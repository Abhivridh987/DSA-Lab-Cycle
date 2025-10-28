#include <stdio.h>
#include <stdlib.h>

struct Tree_Node{
    int data;
    struct Tree_Node* left;
    struct Tree_Node* right;
};
struct Tree_Node* new_Tree_Node(int data)
{
    struct Tree_Node* nd = (struct Tree_Node*)malloc(sizeof(struct Tree_Node));
    nd->data = data;
    nd->left = NULL;
    nd->right= NULL;
    return nd;
}


struct Node{
    struct Tree_Node* data;
    struct Node* next;
};
struct Queue{
    struct Node* head;
    struct Node* tail;
    int size;
};
struct Node* new_Node(struct Tree_Node* data)
{
    struct Node* nd = (struct Node*)malloc(sizeof(struct Node));
    nd->data = data;
    nd->next = NULL;
    return nd;
}
struct Queue* init_Queue()
{
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}
struct Queue* enqueue(struct Queue* q, struct Tree_Node* data)
{
    struct Node* nd = new_Node(data);
    if(q->tail == NULL)
    {
        q->head = q->tail = nd;
    }
    else{
        q->tail->next = nd;
        q->tail = nd;
    }
    q->size = q->size + 1;
    return q;
}
struct Queue* dequeue(struct Queue* q)
{
    if(q->head == NULL )
        return q;
    else if(q->head->next == NULL)
    {
        struct Node* temp = q->head;
        q->head = q->tail = NULL;
        free(temp);
        temp = NULL;
    }
    else
    {
        struct Node* temp = q->head;
        q->head = q->head->next;
        free(temp);
        temp = NULL;
    }
    q->size = q->size - 1;
    return q;
}

int isEmpty(struct Queue* q)
{
    if(q->head == NULL)
        return 1;
    else
        return 0;
}



void display_level_order(struct Tree_Node* root)
{
    int result[100];
    int size = 0;
    struct Queue* q = init_Queue();
    enqueue(q,root);
    while(!isEmpty(q))
    {
        struct Tree_Node* nd = q->head->data;
        if(nd == NULL) {
            result[size++] = 0;
        } else {
            result[size++] = nd->data;
            enqueue(q, nd->left);
            enqueue(q, nd->right);
        }
        dequeue(q);
    }
    printf("\n");
    int threshold = 1;
    for(int i = 0 ; i < size; i++)
    {
        if(i+1 ==  threshold)
        {
            threshold = threshold *2;
            printf("\n");
        }
        printf("%d ", result[i]);
        
    }
}
struct Tree_Node* level_order_insertion(int data, struct Queue* q, struct Tree_Node* root)
{
    struct Tree_Node* nd = new_Tree_Node(data);
    if(root == NULL)
    {
        enqueue(q,nd);
        return nd;
    }
    if(q->head == NULL)
    {
        enqueue(q,nd);
        return root;
    }
    if(q->head->data->left == NULL)
    {
        q->head->data->left = nd;
        enqueue(q, nd);
        return root;
    }
    if(q->head->data->right == NULL)
    {
        q->head->data->right = nd;
        enqueue(q, nd);
        dequeue(q);
        return root;
    }
    
}
void display_level_order_without_zeros(struct Tree_Node* root)
{
    int result[100];
    int size = 0;
    struct Queue* q = init_Queue();
    enqueue(q,root);
    while(!isEmpty(q))
    {
        struct Tree_Node* nd = q->head->data;
        if(nd == NULL) {
            dequeue(q);
            continue;
        } else {
            result[size++] = nd->data;
            enqueue(q, nd->left);
            enqueue(q, nd->right);
        }
        dequeue(q);
    }
    printf("\n");
    int threshold = 1;
    for(int i = 0 ; i < size; i++)
    {
        if(i+1 ==  threshold)
        {
            threshold = threshold *2;
            printf("\n");
        }
        printf("%d ", result[i]);
        
    }
}
int main()
{
   struct Tree_Node* root = NULL;
   struct Queue* q = init_Queue();
   
   while(1)
   {
       printf("1. Add \n2. Display \n3. Exit \nEnter Choice : ");
       int ch;
       scanf("%d", &ch);
       if(ch == 1)
       {
           int num;
           printf("Enter number : ");
           scanf("%d", &num);
           if(root == NULL)
                root = level_order_insertion(num, q, root);
           else
                level_order_insertion(num, q, root);
            
      }
        else if(ch == 2)
        {
            printf("\n\n");
            display_level_order_without_zeros(root);
            printf("\n\n");
        }
        else if(ch == 3)
            return 0;
        else
            continue;
   }
   

   
  
   
   
   
   
}
