#include <stdio.h>
const int isPrime[] = {
    0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 
    0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0,
};
int place(int *arr, int pos, int n, int used[]){
    if(pos == n)return 1;
    int count = 0;
    for(int num = 1; num <= n; num++){
        if(used[num - 1])continue;
        if(isPrime[arr[pos - 1] + num]){
            if(pos == (n - 1) && isPrime[num + arr[0]] == 0){
                continue;
            }
            used[num - 1] = 1;
            arr[pos] = num;
            count += place(arr, pos + 1, n, used);
            used[num - 1] = 0;
            arr[pos] = 0;
        }
    }
    return count;
}
int main(){
    int n; scanf("%d", &n);
    int arr[n];
    int used[n];
    for(int i = 0; i < n; i++)used[i] = 0;
    used[0] = 1;
    arr[0] = 1;
    int res = place(arr, 1, n, used);
    printf("%d\n", res);
    return 0;
}