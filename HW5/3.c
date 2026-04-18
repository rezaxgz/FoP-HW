#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void input(int n, int *arr){
    int *full = malloc(n * n * sizeof(int));
    memset(full, 0, n * n * sizeof(int));
    int i = 0;
    int j = 0;
    int dir = 0;
    int count = 0;
    while(count < (n * n)){
        scanf("%d", &arr[i * n + j]);
        full[i * n + j] = 1;
        count++;
        if(dir % 4 == 0 && j < n - 1 && full[i * n + j + 1] == 0){
            j++;
            continue;
        }
        if(dir % 4 == 2 && j > 0 && full[i * n + j - 1] == 0){
            j--;
            continue;
        }
        if(dir % 4 == 1 && i < n - 1 && full[(i + 1) * n + j] == 0){
            i++;
            continue;
        }
        if(dir % 4 == 3 && i > 0 && full[(i - 1) * n + j] == 0){
            i--;
            continue;
        }
        dir += 1;
        if(dir % 4 == 0){
            j++;
            continue;
        }
        if(dir % 4 == 2){
            j--;
            continue;
        }
        if(dir % 4 == 1){
            i++;
            continue;
        }
        if(dir % 4 == 3){
            i--;
            continue;
        }
    }
    free(full);
}
void transpose(int n, int *arr){
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            swap(&arr[i * n + j], &arr[j * n + i]);
        }
    }
}
void rotate_clockwise(int n, int *arr){
    transpose(n, arr);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n / 2; j++){
            swap(&arr[i * n + j], &arr[i * n + (n - 1 - j)]);
        }
    }
}
void swap_rows(int n, int *arr, int row1, int row2){
    for(int j = 0; j < n; j++){
        swap(&arr[row1 * n + j], &arr[row2 * n + j]);
    }
}   
void swap_columns(int n, int *arr, int col1, int col2){
    for(int i = 0; i < n; i++){
        swap(&arr[i * n + col1], &arr[i * n + col2]);
    }
}
void swap_cmd(int n, int *arr){
    char c[500];
    scanf("%s", c);
    if(strcmp(c, "rows") == 0){
        int row1, row2; scanf("%d and %d", &row1, &row2);
        if(row1 > n || row2 > n || row1 <= 0 || row2 <= 0){
            printf("invalid numbers for swapping.\n");
            return;
        }
        swap_rows(n, arr, row1 - 1, row2 - 1);
    } else if(strcmp(c, "columns") == 0){
        int col1, col2; scanf("%d and %d", &col1, &col2);
        if(col1 > n || col2 > n || col1 <= 0 || col2 <= 0){
            printf("invalid numbers for swapping.\n");
            return;
        }
        swap_columns(n, arr, col1 - 1, col2 - 1);
    }
}
void print(int n, int *arr){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", arr[i * n + j]);
        }
        printf("\n");
    }
}
void saddle(int n, int *arr){
    for(int i = 0; i < n; i++){
        int min = arr[i * n + 0];
        for(int j = 1; j < n; j++){
            if(arr[i * n + j] < min){
                min = arr[i * n + j];
            }
        }
        for(int col = 0; col < n; col++){
            if(arr[i * n + col] == min){
                int is_saddle = 1;
                for(int row = 0; row < n; row++){
                    if(arr[row * n + col] > min){
                        is_saddle = 0;
                        break;
                    }
                }
                if(is_saddle){
                    printf("(%d, %d)", i + 1, col + 1);
                }
            }
        }
    }
    printf("\n");
}
int main(){
    int n; scanf("%d", &n);
    int *arr = malloc(n * n * sizeof(int));
    input(n, arr);
    char cmd[500];
    scanf("%s", cmd);
    while(1){
        if(strcmp(cmd, "transpose") == 0){
            transpose(n, arr);
        } else if(strcmp(cmd, "saddle") == 0){
            saddle(n, arr);
        } else if(strcmp(cmd, "swap") == 0){
            swap_cmd(n, arr);
        } else if(strcmp(cmd, "rotate") == 0){
            char dir[500];
            scanf("%s", dir);
            if(strcmp(dir, "clockwise") == 0){
                rotate_clockwise(n, arr);
            }else{
                scanf("%s", &cmd);
                rotate_clockwise(n, arr);rotate_clockwise(n, arr);rotate_clockwise(n, arr);
            }
        }if(strcmp(cmd, "end") == 0){
            break;
        }
        scanf("%s", &cmd);
    }
    print(n, arr);
    return 0;
}