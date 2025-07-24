#include <stdio.h>
#include <stdlib.h>

void display_transpose(int rows, int cols, int mat[rows][cols]){
    for(int i = 1 ;i < rows - 1; i++){
        for(int j = 1 ; j < rows - 1 - i; j++){
            if(mat[j][1] > mat[j+1][1]){
                int temp1 = mat[j][0];
                int temp2 = mat[j][1];
                int temp3 = mat[j][2];
                mat[j][0] = mat[j+1][0];
                mat[j][1] = mat[j+1][1];
                mat[j][2] = mat[j+1][2];
                mat[j+1][0] = temp1;
                mat[j+1][1] = temp2;
                mat[j+1][2] = temp3;
            }
        }
    }
    for(int i = 0 ;i < rows; i++){
        int temp = mat[i][0];
        mat[i][0] = mat[i][1];
        mat[i][1] = temp;
    }
    for(int i = 0 ;i < rows; i++){
        for(int j = 0; j < 3; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

}
int main()
{
    int n, m, o;

    // First Matrix Input
    printf("Enter the number of non zero entries in first sparse matrix : ");
    scanf("%d", &n);
    int firstLayer[n+1][3];
    for(int i = 0; i < n+1; i++) {
        scanf("%d %d %d", &firstLayer[i][0], &firstLayer[i][1], &firstLayer[i][2]);
    }

    // Second Matrix Input
    printf("\nEnter the number of non zero entries in second sparse matrix : ");
    scanf("%d", &m);
    int secondLayer[m+1][3];
    for(int i = 0; i < m+1; i++) {
        scanf("%d %d %d", &secondLayer[i][0], &secondLayer[i][1], &secondLayer[i][2]);
    }

    // Addition of first and second matrix
    if(firstLayer[0][0] == secondLayer[0][0] && firstLayer[0][1] == secondLayer[0][1]) {
        int i = 1, j = 1, k = 1;
        int result_of_two[n + m + 1][3];
        result_of_two[0][0] = firstLayer[0][0];
        result_of_two[0][1] = firstLayer[0][1];

        while(i < n+1 && j < m+1) {
            if(firstLayer[i][0] < secondLayer[j][0] ||
              (firstLayer[i][0] == secondLayer[j][0] && firstLayer[i][1] < secondLayer[j][1])) {
                result_of_two[k][0] = firstLayer[i][0];
                result_of_two[k][1] = firstLayer[i][1];
                result_of_two[k][2] = firstLayer[i][2];
                i++;
            }
            else if(secondLayer[j][0] < firstLayer[i][0] ||
                   (secondLayer[j][0] == firstLayer[i][0] && secondLayer[j][1] < firstLayer[i][1])) {
                result_of_two[k][0] = secondLayer[j][0];
                result_of_two[k][1] = secondLayer[j][1];
                result_of_two[k][2] = secondLayer[j][2];
                j++;
            }
            else {
                result_of_two[k][0] = firstLayer[i][0];
                result_of_two[k][1] = firstLayer[i][1];
                result_of_two[k][2] = firstLayer[i][2] + secondLayer[j][2];
                i++;
                j++;
            }
            k++;
        }

        while(i < n+1) {
            result_of_two[k][0] = firstLayer[i][0];
            result_of_two[k][1] = firstLayer[i][1];
            result_of_two[k][2] = firstLayer[i][2];
            i++;
            k++;
        }

        while(j < m+1) {
            result_of_two[k][0] = secondLayer[j][0];
            result_of_two[k][1] = secondLayer[j][1];
            result_of_two[k][2] = secondLayer[j][2];
            j++;
            k++;
        }

        result_of_two[0][2] = k - 1;

        // Third Matrix Input
        printf("\nEnter the number of non zero entries in third sparse matrix : ");
        scanf("%d", &o);
        int thirdLayer[o+1][3];
        for(int i = 0; i < o+1; i++) {
            scanf("%d %d %d", &thirdLayer[i][0], &thirdLayer[i][1], &thirdLayer[i][2]);
        }

        // Add result_of_two and thirdLayer
        if(thirdLayer[0][0] == result_of_two[0][0] && thirdLayer[0][1] == result_of_two[0][1]) {
            int ii = 1, jj = 1, kk = 1;
            int result_of_three[o + result_of_two[0][2] + 1][3];
            result_of_three[0][0] = thirdLayer[0][0];
            result_of_three[0][1] = thirdLayer[0][1];

            while(ii < o+1 && jj < result_of_two[0][2]+1) {
                if(thirdLayer[ii][0] < result_of_two[jj][0] ||
                  (thirdLayer[ii][0] == result_of_two[jj][0] && thirdLayer[ii][1] < result_of_two[jj][1])) {
                    result_of_three[kk][0] = thirdLayer[ii][0];
                    result_of_three[kk][1] = thirdLayer[ii][1];
                    result_of_three[kk][2] = thirdLayer[ii][2];
                    ii++;
                }
                else if(result_of_two[jj][0] < thirdLayer[ii][0] ||
                        (result_of_two[jj][0] == thirdLayer[ii][0] && result_of_two[jj][1] < thirdLayer[ii][1])) {
                    result_of_three[kk][0] = result_of_two[jj][0];
                    result_of_three[kk][1] = result_of_two[jj][1];
                    result_of_three[kk][2] = result_of_two[jj][2];
                    jj++;
                }
                else {
                    result_of_three[kk][0] = thirdLayer[ii][0];
                    result_of_three[kk][1] = thirdLayer[ii][1];
                    result_of_three[kk][2] = thirdLayer[ii][2] + result_of_two[jj][2];
                    ii++;
                    jj++;
                }
                kk++;
            }

            while(ii < o+1) {
                result_of_three[kk][0] = thirdLayer[ii][0];
                result_of_three[kk][1] = thirdLayer[ii][1];
                result_of_three[kk][2] = thirdLayer[ii][2];
                ii++;
                kk++;
            }

            while(jj < result_of_two[0][2]+1) {
                result_of_three[kk][0] = result_of_two[jj][0];
                result_of_three[kk][1] = result_of_two[jj][1];
                result_of_three[kk][2] = result_of_two[jj][2];
                jj++;
                kk++;
            }

            result_of_three[0][2] = kk - 1;

            // Print final result
            printf("\nFinal Result (All three matrices added):\n");
            for(int i = 0; i < kk; i++) {
                printf("%d %d %d\n", result_of_three[i][0], result_of_three[i][1], result_of_three[i][2]);
            }
            printf("\n\nTranspose : \n\n");
            display_transpose(result_of_three[0][2] + 1,3,result_of_three);


        } else {
            printf("\nCannot be Added (Third matrix dimensions mismatch)\n");
        }

    } else {
        printf("\nCannot be Added (First and Second matrix dimensions mismatch)\n");
    }

    return 0;
}
