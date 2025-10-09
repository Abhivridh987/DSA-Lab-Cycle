#include <stdio.h>
#include <stdlib.h>

struct Node{
	int data;
	struct Node* next;
};

struct Node* new_node(int data)
{
	struct Node* nd = (struct Node*)malloc(sizeof(struct Node));
	nd->next = NULL;
	nd->data = data;
	return nd;
}
struct Node* add(struct Node* head, int data)
{
	struct Node* nd = new_node(data);
	if(head == NULL)
	{
		head = nd;
	}
	else{
		struct Node* curr = head;
		while(curr->next != NULL)
		{
			curr = curr->next;
		}
		curr->next = nd;
	}
	return head;
}

void display(struct Node* head)
{
	struct Node* nd = head;
	printf("\n");
	while(nd != NULL)
	{
		printf("%d ", nd->data);
		nd = nd->next;
	}
	printf("\n");
}
int main()
{
	int n;
	printf("Enter the number of lists : ");
	scanf("%d", &n);
	struct Node* lk[n];
	int total_elements = 0;
	struct Node* heap[n];
	for(int i = 0 ;i < n; i++)
	{
		lk[i] = NULL;
	}
	for(int i = 0; i < n; i++)
	{
		int m;
		printf("ENter the number of elements in the list : ");
		scanf("%d", &m);
		total_elements+=m;
		for(int j = 0 ; j < m; j++)
		{
			int data;
			printf("ENter the data : ");
			scanf("%d", &data);
			lk[i] = add(lk[i], data);
		}

	}
	for(int i = 0; i< n; i++)
	{
		display(lk[i]);
	}
	int result[total_elements];

	//Appending all nodes in heap
	for(int i = 0 ;i < n; i++)
	{
		heap[i] = lk[i];
	}

	//smallest
	struct Node* smallest =	lk[0]; 
	for(int i = 0 ;i < n; i++)
	{
		if(heap
	}



}

