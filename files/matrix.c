#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, i, j, k;
    n=120;
    int arr1[n][n], arr2[n][n], res[n][n];
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            scanf("%d", &arr1[i][j]);
        }
    }
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){        
            scanf("%d", &arr2[i][j]);
        }
    }

    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            res[i][j] = 0;
            for(k=0; k<n; k++){
                res[i][j] += arr1[i][k] * arr2[k][j];
                printf("%lu\n", (long unsigned int)&res[i][j]);
            }
        }
    }
}