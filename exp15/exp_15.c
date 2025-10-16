#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int data;
    struct Node* next;
} Node;
void swap(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}
void heapify(Node* heap[], int size, int i) {
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < size && heap[left]->data < heap[smallest]->data)
        smallest = left;
    if (right < size && heap[right]->data < heap[smallest]->data)
        smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapify(heap, size, smallest);
    }
}
void buildHeap(Node* heap[], int size) {
    for (int i = size/2 - 1; i >= 0; i--)
        heapify(heap, size, i);
}
Node* mergeKLists(Node* lists[], int K) {
    Node** heap = (Node**)malloc(K * sizeof(Node));
    int heapSize = 0;
    for (int i = 0; i < K; i++) {
        if (lists[i] != NULL) {
            heap[heapSize++] = lists[i];
        }
    }
    buildHeap(heap, heapSize);
    Node* head = NULL;
    Node* tail = NULL;
    while (heapSize > 0) {
        Node* smallest = heap[0];
        if (head == NULL) {
            head = tail = smallest;
        } else {
            tail->next = smallest;
            tail = smallest;
        }
        if (smallest->next != NULL) {
            heap[0] = smallest->next;
        } else {
            heap[0] = heap[--heapSize];
        }
        heapify(heap, heapSize, 0);
        tail->next = NULL;
    }
    free(heap);
    return head;
}
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}
void printList(Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}
int main() {
    int K;
    printf("sorted lists count : ");
    scanf("%d", &K);
    Node** lists = (Node**)malloc(K * sizeof(Node));
    for (int i = 0; i < K; i++) {
        int n;
        printf("elements count  in list %d: ", i+1);
        scanf("%d", &n);
        Node* head = NULL;
        Node* tail = NULL;
        printf("Enter %d elements(sorted) for list %d: ", n, i+1);
        for (int j = 0; j < n; j++) {
            int val;
            scanf("%d", &val);
            Node* node = newNode(val);
            if (head == NULL) {
                head = tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
        }
        lists[i] = head;
    }
    Node* merged = mergeKLists(lists, K);
    printf("Merged &  sorted list: ");
    printList(merged);
    free(lists);
    return 0;
}
