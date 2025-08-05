#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *doc_name;
    int waitingtime;
    struct Node* next;
};

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

int main() {
    struct Node* pfront = NULL;
    struct Node* prear = NULL;
    int size = 0;
    int n;

    printf("Enter the number of persons: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int no_of_pages;
        char name[30];

        printf("\nEnter the number of pages: ");
        scanf("%d", &no_of_pages);
        int waiting_time = no_of_pages * 2;
        printf("Enter the name of the doc: ");
        scanf(" %s", name);

        struct Node* pcurr = (struct Node*)malloc(sizeof(struct Node));
        pcurr->waitingtime = waiting_time;
        pcurr->doc_name = malloc(strlen(name) + 1);
        strcpy(pcurr->doc_name, name);
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
        printf("%s %d\n", pprint->doc_name, pprint->waitingtime);
        pprint = pprint->next;
    }
    printf("\n");
    printf("Currently Printed Document : %s   Pages : %d", pfront->doc_name, (pfront->waitingtime / 2));
    printf("\nDocument b : %d seconds to be waited",waiting_time(pfront, "doc3"));
    printf("\nLongest person to wait : %s   Pages : %d", prear->doc_name, (prear->waitingtime )/ 2);


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
