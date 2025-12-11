#include <stdio.h> 

int nCr(int n, int r) {
    int res = 1;
    for (int i = 1; i <= r; i++) {
        res = res * (n - r + i) / i;
    }
    return res;
}
int choose(int rel[], int n, int last, int from_index, int remain, int count, int target){
    if(remain == 0){
        if(count >= target)return 1;
        return 0;
    }
    if(remain > (n - from_index))return 0;
    if(count >= target)return nCr(n - from_index, remain);
    if(last == -1) return choose(rel, n, from_index ,from_index + 1, remain - 1, count, target)
    + choose(rel, n, last, from_index + 1, remain, count, target);
    return choose(rel, n, from_index ,from_index + 1, remain - 1, count + rel[last + n * from_index], target)
    + choose(rel, n, last, from_index + 1, remain, count, target);
}
int main(){
    int n; scanf("%d", &n);
    int k; scanf("%d", &k);
    int arr[n * n];
    for(int i = 0; i < n * n; i++){
        scanf("%d", &arr[i]);
    }
    printf("%d", choose(arr, n, -1, 0, k, 0, k / 2));
    return 0;
}