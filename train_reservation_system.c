#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    char name[20];
    int no_of_tickets;
    struct Node* next;
};

struct Node* head = NULL;
struct Node* tail = NULL;

void serve_customer(){
    if(head == NULL)
    {
        printf("\n\nNo customer to serve\n\n");
    }
    else if(head == tail){
        free(head);
        free(tail);
        head = NULL;
        tail = NULL;
        printf("\n\nCustomer Served Successfully\n\n");
    }
    else if(head->no_of_tickets <= 1){
        struct Node* temp_head = head;
        head = head->next;
        free(temp_head);
        printf("\n\nCustomer Served Successfully\n\n");

    }
    else{
        struct Node* temp_head = head;
        head = head->next;
        enter_customer(temp_head->name, (temp_head->no_of_tickets - 1));
        free(temp_head);
        printf("\n\nCustomer Served Successfully\n\n");
    }
}

void enter_customer(char name[], int tickets){

    if(tail == NULL){
        struct Node* nd = (struct Node*)malloc(sizeof(struct Node));
        strcpy(nd->name, name);
        nd->no_of_tickets = tickets;
        nd->next = NULL;
        head = tail = nd;

    }
    else{
        struct Node* nd = (struct Node*)malloc(sizeof(struct Node));
        strcpy(nd->name, name);
        nd->no_of_tickets = tickets;
        nd->next = NULL;
        tail->next = nd;
        tail = nd;

    }


}
void display_current_ticket()
{
    if(head != NULL)
    {
        printf("\n\nName : %s    Tickets : %d\n\n", head->name, head->no_of_tickets);
    }
    else{
        printf("\n\nNo customers\n\n");
    }
}
void display_tickets(){
    if(head == NULL ){
        printf("\n\nNo customers\n\n");
        return;
    }
    struct Node* temp = head;
    printf("\n\n");
    while(temp!=NULL){
        printf("Name : %s    No of tickets : %d\n",temp->name, temp->no_of_tickets);
        temp = temp->next;
    }
    printf("\n\n");
}

int main()
{
    int choice;
    int loop = 1;
    while(loop == 1){

        printf("1. Enter new customer\n2. Serve Ticket to customer\n3. Display tickets\n4. Display Current Ticket\n5. Exit");
        printf("\n\nEnter choice : " );
        scanf(" %d", &choice);
        if(choice == 1)
        {
            char name[20];
            int tickets;
            printf("\n\nEnter the name of customer : ");
            scanf(" %[^\n]", name);
            printf("Enter the number of tickets : ");
            scanf("%d", &tickets);
            enter_customer(name, tickets);

            printf("Customer Entered Successfully\n\n");
        }
        else if(choice == 2){
            serve_customer();

        }
        else if(choice == 3)
            display_tickets();
        else if(choice == 4)
            display_current_ticket();
        else if(choice == 5)
            return 0;


    }


}
