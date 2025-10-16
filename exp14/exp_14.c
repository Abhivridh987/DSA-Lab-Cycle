#include <stdio.h>
#include <stdlib.h>

// Define categories
#define DIFF_ABLED 1
#define SENIOR_CITIZEN 2
#define DEFENCE_PERSONNEL 3
#define NORMAL_PERSON 4

// Customer node structure
typedef struct Customer {
    int token_number;          // Token number for the customer
    int category;              // Customers category
    struct Customer* next;     // Pointer to the next customer in the list
} Customer;

// Function to create a new customer node
Customer* createCustomer(int token_number, int category) {
    Customer* newCustomer = (Customer*)malloc(sizeof(Customer));
    newCustomer->token_number = token_number;
    newCustomer->category = category;
    newCustomer->next = NULL;
    return newCustomer;
}

// Function to add a customer to the end of the list
void enqueue(Customer** head, int token_number, int category) {
    Customer* newCustomer = createCustomer(token_number, category);
    if (*head == NULL) {
        *head = newCustomer;  // If list is empty, make the new customer the head
    } else {
        Customer* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;  // Traverse to the last node
        }
        temp->next = newCustomer;  // Add the new customer at the end
    }
}

// Function to serve the first customer from the list (FIFO)
void serveCustomer(Customer** head) {
    if (*head == NULL) {
        printf("No customers to serve.\n");
        return;
    }
    Customer* temp = *head;
    printf("Serving customer with token %d (Category %d)\n", temp->token_number, temp->category);
    *head = (*head)->next;  // Move head to the next customer
    free(temp);  // Free the memory of the served customer
}

// Function to serve all customers in priority order
void serveAllCustomers(Customer* diffAbled, Customer* seniorCitizens, Customer* defencePersonnel, Customer* normalPersons) {
    // Serve customers in priority order (Differently abled > Senior citizens > Defence personnel > Normal persons)
    while (diffAbled != NULL || seniorCitizens != NULL || defencePersonnel != NULL || normalPersons != NULL) {
        if (diffAbled != NULL) {
            serveCustomer(&diffAbled);
        }
        else if (seniorCitizens != NULL) {
            serveCustomer(&seniorCitizens);
        }
        else if (defencePersonnel != NULL) {
            serveCustomer(&defencePersonnel);
        }
        else if (normalPersons != NULL) {
            serveCustomer(&normalPersons);
        }
    }
}

int main() {
    // Initialize linked lists for each category
    Customer* diffAbled = NULL;
    Customer* seniorCitizens = NULL;
    Customer* defencePersonnel = NULL;
    Customer* normalPersons = NULL;

    int N, category, i;
    printf("Enter the number of customers: ");
    scanf("%d", &N);

    // For each customer, get their category and assign a token number
    for (i = 0; i < N; i++) {
        printf("Enter category for customer %d (1: Differently abled, 2: Senior citizen, 3: Defence personnel, 4: Normal person): ", i + 1);
        scanf("%d", &category);

        // Add the customer to the appropriate category list
        if (category == DIFF_ABLED) {
            enqueue(&diffAbled, i + 1, category);
        } else if (category == SENIOR_CITIZEN) {
            enqueue(&seniorCitizens, i + 1, category);
        } else if (category == DEFENCE_PERSONNEL) {
            enqueue(&defencePersonnel, i + 1, category);
        } else if (category == NORMAL_PERSON) {
            enqueue(&normalPersons, i + 1, category);
        } else {
            printf("Invalid category.\n");
        }
    }

    // Serve all customers in priority order
    printf("\nServing customers in order of priority:\n");
    serveAllCustomers(diffAbled, seniorCitizens, defencePersonnel, normalPersons);

    return 0;
}


