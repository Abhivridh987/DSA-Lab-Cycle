#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
	struct Node* left;
	char* word;
	char* meaning;
	struct Node* right;
};
struct Node* createNode(char* word, char* meaning)
{
	struct Node* nd = (struct Node*)malloc(sizeof(struct Node));
	nd->word = (char*)malloc(strlen(word) * sizeof(char));
	nd->meaning = (char*)malloc(strlen(meaning) * sizeof(char));
	strcpy(nd->word, word);
	strcpy(nd->meaning, meaning);
	nd->left = NULL;
	nd->right = NULL;
	return nd;
}
char* word()
{
	char* word_str = (char*)malloc(20*sizeof(char));
	printf("Enter a word :");
	scanf(" %[^\n]", word_str);
	return word_str;
}

char* meaning()
{
	char* meaning_str = (char*)malloc(50*sizeof(char));
	printf("Enter meaning : ");
	scanf(" %[^\n]", meaning_str);
	return meaning_str;
}
struct Node* insertword(struct Node* root, struct Node* word)
{
	if(root == NULL)
	{
		return word;
	}
	else{
		if(strcmp(word->word,root->word)>0)
			root->right = insertword(root->right, word);
		else if(strcmp(word->word, root->word)<0)
			root->left = insertword(root->left,word);
		else
			printf("Word Already Present");
		return root;
	}
}
void display(struct Node* root)
{
	if(root ==NULL)
		return;
	else
	{
		display(root->left);
		printf("%s : %s\n", root->word, root->meaning);
		display(root->right);
	}
}
struct Node* search(struct Node* root, char* target)
{
	if(root == NULL)
	{
		printf("\nTarget Not Found\n------------\n\n");
		return NULL;
	}
	else if(strcmp(target, root->word) == 0)
	{
		return root;
	}
	else if(strcmp(target, root->word) < 0)
	{
		return search(root->left, target);
	}
	else{
		return search(root->right, target);
	}
}

struct Node* delete_Node(struct Node* root, char* word)
{
	struct Node* main_root = root;
	struct Node* target = search(root,word);

	if(parent == NULL)
		return NULL;
	else if(parent->right == NULL && parent->left == NULL)
	{
		free(target);
		target = NULL;
		return main_root;
	}
	else if()

}


int main()
{
	struct Node* root = NULL;
	while(1)
	{
		printf("\n1. Enter a new word\n2.Search word\nEnter Choice  : ");
		int ch;
		scanf(" %d", &ch);
		if(ch == 1)
		{
			char* word_str = word();
			char* meaning_str = meaning();
			struct Node* word = createNode(word_str,meaning_str);
			root = insertword(root, word);
		}
		else if(ch == 2)
		{
			char* search_word_str = word();
			struct Node* res = search(root,search_word_str);
			printf("%s : %s", res->word,res->meaning);
		}
		else if(ch == 3)
			display(root);
		else if(ch == 4)
		{
			char* word_str = word();
			delete_Node(root,word_str);
		}
	}
}
