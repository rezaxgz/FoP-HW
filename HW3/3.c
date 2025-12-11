#include <stdio.h>
int len(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}
void removeChar(char text[], int size, int index){
    for(int i = index + 1; i < size; i++){
        text[i - 1] = text[i];
    }
    text[size - 1] = '\0';
}
int gcd(int a, int b){
    if(b == 0) return a;
    return gcd(b, a % b);
}
int lcm(int a, int b){
    return a / gcd(a, b) * b;
}
void step(char arr[], int nums[], int exp, int n){
    int x = len(arr);
    int m = 0;
    while(--x){
        if(arr[x] == '@' || arr[x] == '&'){
            break;
        }
        m++;
    }
    int num1 = nums[n - m];
    int num2 = nums[n - m + 1];
    int res;
    if(arr[exp] == '@'){
        res = lcm(num1, num2);
    }else{
        res = gcd(num1, num2);
    }
    removeChar(arr, len(arr), exp + 1);
    removeChar(arr, len(arr), exp + 1);
    arr[exp] = 'X';
    nums[n - m] = res;
    for(int i = n - m + 1; i < n - 1; i++){
        nums[i] = nums[i + 1];
    };
    nums[n - 1] = -1;
}
int main(){
    int n; scanf("%d", &n);
    char arr[500];
    int nums[n];
    scanf("%s", &arr);
    for(int i = 0; i < n; i++){
        scanf("%d", &nums[i]);
    }
    while(arr[0] != 'X'){
        for(int i = len(arr) - 1; i >= 0; i--){
            if(arr[i] == '@' || arr[i] == '&'){
                step(arr, nums, i, n);
                n--;
                break;
            }
        }
    }
    printf("%d", nums[0]);
    return 0;
}