#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char doc[100][100];
    int i = 0, j = 0;
    char word;
    char old_word[100];
    char new_word[100];
    printf("Enter the document : \n\n");
    while(1){
        scanf("%c",&word);
        if(word == '\n')
            break;
        else if(word == ' ')
        {
            doc[i][j] = '\0';
            j = 0;
            i++;
            doc[i][j++] = ' ';
            doc[i][j] = '\0';
            j = 0;
            i++;
        }
        else if((word >= 'a' && word <= 'z') || (word >= 'A' && word <= 'Z') || (word >= '0' && word <= '9')){
            doc[i][j] = word;
            j++;
        }
        else{
            doc[i][j] = '\0';
            j = 0;
            i++;
            doc[i][j++] = word;
            doc[i][j] = '\0';
            j = 0;
            i++;
            doc[i][j++] = ' ';
            doc[i][j] = '\0';
            j = 0;
            i++;
        }

    }
    printf("\n\nEnter the word you want to replace : ");
    scanf(" %s",old_word);
    printf("Enter the new word you want to replace with : ");
    scanf(" %s", new_word);

    int occurences = 0;
    for(int k = 0 ;k <= i; k++){
        if(strcmp(doc[k], old_word) == 0){
            strcpy(doc[k], new_word);
            occurences++;
        }
    }
    printf("\n\nTotal Occurences : %d", occurences);
    printf("\n\nUpdated Document : \n\n");
    for(int k = 0 ;k < i; k++){
        printf("%s",doc[k]);
    }
    printf("\n\n");
}
