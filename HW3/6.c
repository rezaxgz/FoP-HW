#include <stdio.h>

int solve(int *arr, int pos, int n){
    if(pos == (n * n))return 1;
    if(arr[pos] != 0)return solve(arr, pos + 1, n);
    int col = pos % n;
    int row = pos / n;
    for(int num = 1; num <= n; num++){
        int flag = 1;
        for(int c = 0; c < n; c++){
            if(c == col)continue;
            if(arr[n * row + c] == num){
                flag = 0;
                break;
            };
        }
        if(flag == 0)continue;
        for(int r = 0; r < n; r++){
            if(r == row)continue;
            if(arr[n * r + col] == num){
                flag = 0;
                break;
            };
        }
        if(flag == 0)continue;
        arr[pos] = num;
        int res = solve(arr, pos + 1, n);
        if(res == 1)return 1;
        arr[pos] = 0;
    }
    return -1;
}
int main(){
    int n; scanf("%d", &n);
    int arr[n*n];
    for(int i = 0; i < n * n; i ++){
        scanf("%d", &arr[i]);
    }
    int res = solve(arr, 0, n);
    if(res == -1){
        printf("Escape is impossible!!");
        return 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", arr[i*n + j]);
        }
        printf("\n");
    }
    return 0;
}