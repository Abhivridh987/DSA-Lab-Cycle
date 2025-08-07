#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Node{
    struct Node* previous;
    char url[20];
    struct Node* next;
};

struct Node* head = NULL;
struct Node* tail = NULL;

void add_tab(char tab_name[])
{
    if(tail == NULL){
        struct Node* nd = (struct Node*)malloc(sizeof(struct Node));
        nd->previous = NULL;
        strcpy(nd->url, tab_name);
        nd->next = NULL;
        head = tail = nd;
    }
    else{
        struct Node* nd = (struct Node*)malloc(sizeof(struct Node));
        tail->next = nd;
        nd->previous = tail;
        strcpy(nd->url, tab_name);
        nd->next = NULL;
        tail = nd;
    }
}
int main()
{
    if(tail == NULL)
    {
        char name[20];
        printf("Enter a new tab : ");
        scanf(" %[^\n]", name);
        add_tab(name);
    }
    struct Node* temp_head = head;
    while(1 == 1){
       printf("\n\nCurrent Tab Name : %s \n\n", (temp_head->url));
       printf("1. Back    2. Front   3. Create New    4. Display     5. Exit\n\nEnter a index : ");
       int choice;
       scanf(" %d",&choice);
       if(choice == 1){
            if(temp_head->previous == NULL){
                printf("\n\nNo Previous URL\n\n");
            }
            else{
                temp_head = temp_head->previous;
            }
       }
       else if(choice == 2){
            if(temp_head->next == NULL){
                printf("\n\nNo Forward URL\n\n");
            }
            else{
                temp_head = temp_head->next;
            }
       }
       else if(choice == 3){
            char name[20];
            printf("Enter a new tab : ");
            scanf(" %[^\n]", name);
            add_tab(name);
       }
       else if(choice == 4){
            struct Node* temp = head;
            if(temp != NULL){
                printf("\n\n");
                printf("%s ", temp->url);
                temp = temp->next;
            }
            else{
                printf("\n\nNo valid URL\n\n");
                continue;
            }
            while(temp != NULL){
                printf("-> %s ",temp->url);
                temp = temp->next;
            }
            printf("\n\n");
       }
       else if(choice == 5){
            struct Node* current = head;
            struct Node* temp;
            while(current != NULL){
                temp = current;
                current = current->next;
                free(temp);
            }
            head = tail = temp_head = NULL;
            return 0;
       }
    }





}
