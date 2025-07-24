#include <stdio.h>
#include <stdlib.h>



void display_mat(int rows, int cols, int mat[rows][cols])
{
    for(int i = 0; i < rows; i++){
        for(int j = 0 ; j < cols; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    char eqn[20],eqn2[20];
    int mat1[8][2],mat2[8][2], k=0;
    for(int i = 0; i < 8; i++){
        for(int j = 0 ; j < 2; j++){
            mat1[i][j] = 0;
        }
    }
    for(int i = 0; i < 8; i++){
        for(int j = 0 ; j < 2; j++){
            mat2[i][j] = 0;
        }
    }
    printf("Enter equation 1 : ");
    scanf("%[^\n]",eqn);
    int isCoeff = 1;
    int isExp = 0;
    int isNegative = 0;
    for(int i = 0 ;eqn[i] != '\0';i++)
    {
        if(i==0 && eqn[i] == '-'){
            isNegative = 1;
        }
        else if(eqn[i] == '-' || eqn[i] == '+' || eqn[i] == 'x'){
            if(isCoeff == 1)
            {
                isCoeff = 0;
                isExp = 1;
                if(isNegative)
                {
                    mat1[k][0] = -mat1[k][0];
                    isNegative = 0;
                }
            }
            else{
                isCoeff = 1;
                isExp = 0;
                if(isNegative)
                {
                    mat1[k][1] = -mat1[k][1];
                    isNegative = 0;
                }

                k++;
            }
            if(eqn[i] == '-')
                isNegative = 1;
        }
        else if(isCoeff == 1 && eqn[i] >= '0' && eqn[i] <= '9'){
            mat1[k][0] = mat1[k][0]*10 + (eqn[i] - '0');

        }
        else if(isExp == 1 && eqn[i] >= '0' && eqn[i] <= '9'){
            mat1[k][1] = mat1[k][1]*10 + (eqn[i] - '0');


        }


    }
    for(int i = 0 ; i < 8; i++){
        if(mat1[i][0] == 0 && mat1[i][1] != 0)
            mat1[i][0] = 1;
    }
    int eqn1_no_of_terms = k+1;
    printf("\n");

    printf("Enter equation 2 : ");
    scanf(" %[^\n]",eqn2);
    isCoeff = 1;
    isExp = 0;
    isNegative = 0;
    k=0;
    for(int i = 0 ;eqn2[i] != '\0';i++)
    {
        if(i==0 && eqn2[i] == '-'){
            isNegative = 1;
        }
        else if(eqn2[i] == '-' || eqn2[i] == '+' || eqn2[i] == 'x'){
            if(isCoeff == 1)
            {
                isCoeff = 0;
                isExp = 1;
                if(isNegative)
                {
                    mat2[k][0] = -mat2[k][0];
                    isNegative = 0;
                }
            }
            else{
                isCoeff = 1;
                isExp = 0;
                if(isNegative)
                {
                    mat2[k][1] = -mat2[k][1];
                    isNegative = 0;
                }

                k++;
            }
            if(eqn2[i] == '-')
                isNegative = 1;
        }
        else if(isCoeff == 1 && eqn2[i] >= '0' && eqn2[i] <= '9'){
            mat2[k][0] = mat2[k][0]*10 + (eqn2[i] - '0');

        }
        else if(isExp == 1 && eqn2[i] >= '0' && eqn2[i] <= '9'){
            mat2[k][1] = mat2[k][1]*10 + (eqn2[i] - '0');


        }


    }
    for(int i = 0 ; i < 8; i++){
        if(mat2[i][0] == 0 && mat2[i][1] != 0)
            mat2[i][0] = 1;
    }
    int eqn2_no_of_terms = k+1;
    int result_mat[8][2];
    for(int i = 0; i < 8; i++){
        for(int j = 0 ; j < 2; j++){
            result_mat[i][j] = 0;
        }
    }
    int i =0,j=0;
    k =0;

    while(i< eqn1_no_of_terms && j< eqn2_no_of_terms){
        if(mat1[i][1] > mat2[j][1]){
            result_mat[k][0] = mat1[i][0] % 3;
            result_mat[k][1] = mat1[i][1];
            i++;
            k++;
        }
        else if(mat2[j][1] > mat1[i][1]){
            result_mat[k][0] = mat2[j][0] % 3;
            result_mat[k][1] = mat2[j][1];
            j++;
            k++;
        }
        else{

            result_mat[k][0] = (mat1[i][0] + mat2[j][0])%3;
            result_mat[k][1] = mat1[i][1];
            k++;
            i++;
            j++;

        }

    }
    if(i == eqn1_no_of_terms){
        for(int x = j; x < eqn2_no_of_terms; x++){
            result_mat[k][0] = mat2[x][0];
            result_mat[k][1] = mat2[x][1];
            k++;
        }
    }
    if(j == eqn2_no_of_terms){
        for(int x = i; x < eqn1_no_of_terms; x++){
            result_mat[k][0] = mat1[x][0];
            result_mat[k][1] = mat1[x][1];
            k++;
        }
    }
    printf("\nResult : ");
    char result_eqn[40];
    int result_no_of_terms = k + 1;
    for(int x = 0; x < result_no_of_terms - 1; x++){
        if(result_mat[x][0] < 0 && x == 0){
            printf("-%d",result_mat[x][0]);
        }
        else if(result_mat[x][0] < 0){
            printf(" - %d",result_mat[x][0]);
        }
        else if(result_mat[x][0] > 0 && x == 0){
            printf("%d",result_mat[x][0]);
        }
        else if(result_mat[x][0] > 0){
            printf(" + %d",result_mat[x][0]);
        }
        if(result_mat[x][1] > 0)
            printf("x^%d", result_mat[x][1]);




    }
    printf("\n\n");
    return 0;
}
