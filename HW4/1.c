#include <stdio.h>
int main(){
    int m, n, p, k;

    scanf("%d", &m);
    scanf("%d", &n);
    int matrix[m][n];
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    scanf("%d", &p);
    scanf("%d", &k);
    int kernel[p][k];
    for(int i = 0; i < p; i++){
        for(int j = 0; j < k; j++){
            scanf("%d", &kernel[i][j]);
        }
    }

    int padding; scanf("%d", &padding);
    int stride; scanf("%d", &stride);

    int row = m + (2 * padding);
    int col = n + (2 * padding);
    int out_row = 1 + (row - p) / stride;
    int out_col = 1 + (col - k) / stride;

    int pad_matrix[row][col];
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){  
            if(i < padding || j < padding || i >= (row - padding) || j >= (col - padding)){
                pad_matrix[i][j] = 0;
            }else{
                pad_matrix[i][j] = matrix[i - padding][j - padding];
            }
        }
    }
    int result[out_row][out_col];

    for(int k_row = 0; k_row + p <= row; k_row += stride){
        for(int k_col = 0; k_col + k <= col; k_col += stride){
            int sum = 0;
            for(int i = k_row; i < k_row + p; i++){
                for(int j = k_col; j < k_col + k; j++){
                    sum += pad_matrix[i][j] * kernel[i - k_row][j - k_col];
                }
            }
            result[k_row / stride][k_col / stride] = sum;
        }
    }
    for(int i = 0; i < out_row; i++) {
        for(int j = 0; j < out_col; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    return 0;
}