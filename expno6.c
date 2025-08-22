#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *doc_name;
    char *teacher_name;
    int waitingtime;
    struct Node* next;
};

struct Node* pfront = NULL;
struct Node* prear = NULL;

int waiting_time(struct Node* pfront , char doc_name[]){
    struct Node* ppfront = pfront;
    int time = 0;

    while(ppfront != NULL && strcmp(doc_name, ppfront->doc_name) != 0){
        time = time + (ppfront->waitingtime);
        ppfront = ppfront->next;
    }
    if(ppfront == NULL)
        return -1;
    else{
        return time + (ppfront->waitingtime);
    }
}

struct Node* person_at_front(int time){
    struct Node* pppfront = pfront;
    int limit_time = 0;
    while(pppfront != NULL)
    {
        limit_time = limit_time + pppfront->waitingtime;
        if(limit_time > time)
        {
            return pppfront;
        }
        pppfront = pppfront->next;
    }
    return NULL;

}
int main() {

    int size = 0;
    int n;

    printf("Enter the number of persons: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int no_of_pages;
        char name[30];
        char doc_teacher_name[30];
        printf("\nEnter the name of the teacher : ");
        scanf(" %[^\n]",doc_teacher_name);
        printf("Enter the name of the doc: ");
        scanf(" %[^\n]", name);
        printf("Enter the number of pages: ");
        scanf("%d", &no_of_pages);
        int waiting_time = no_of_pages * 2;
        

        struct Node* pcurr = (struct Node*)malloc(sizeof(struct Node));
        pcurr->waitingtime = waiting_time;
        pcurr->doc_name = malloc(strlen(name) + 1);
        pcurr->teacher_name = malloc(strlen(doc_teacher_name) + 1);
        strcpy(pcurr->doc_name, name);
        strcpy(pcurr->teacher_name, doc_teacher_name);
        pcurr->next = NULL;

        if (size == 0) {
            pfront = prear = pcurr;
        } else {
            prear->next = pcurr;
            prear = pcurr;
        }
        size++;
    }

    printf("\nQueue Content : \n");
    struct Node* pprint = pfront;
    while (pprint != NULL) {
        printf("%s %d seconds\n", pprint->doc_name, pprint->waitingtime);
        pprint = pprint->next;
    }
    printf("\n");
    int person_at_time;
    printf("\nEnter the time : ");
    scanf("%d", &person_at_time);
    if(person_at_front(person_at_time) == NULL){
        printf("All documents are printed\n");
    }
    else{
        printf("Teacher currently printing front at %d seconds: %s\n",person_at_time, (person_at_front(person_at_time))->teacher_name);
    }
    
    printf("\nDocument PCCSL 307 Lab Cycle : %d seconds to be waited",waiting_time(pfront, "PCCSL 307 Lab Cycle"));
    printf("\nLongest Teacher to wait : %s       Pages : %d      Doc name : %s\n", prear->teacher_name, (prear->waitingtime )/ 2, prear->doc_name);

    

    // Free memory
    pprint = pfront;
    while (pprint != NULL) {
        struct Node* temp = pprint;
        pprint = pprint->next;
        free(temp->doc_name);  // free string
        free(temp);            // free node
    }

    return 0;
}
