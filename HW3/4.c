#include <stdio.h>
int zeros(unsigned long long x){
    int count = 0;
    while((x & 1) == 0){
        count++;
        x >>= 1;
    }
    return count;
}
unsigned long long push(unsigned long long bb, int i, int n){
    unsigned long long x = 1ULL << i;
    if(i % n < (n - 1))x |= (1ULL << (i + 1));
    if(i % n > 0)x |= (1ULL << (i - 1));
    if(i - n >= 0)x |= (1ULL << (i - n));
    if(i + n < (n * n))x |= (1ULL << (i + n));
    return bb ^ x;
}
unsigned long long pushAll(unsigned long long bb, unsigned long long i, int n){
    while(i){
        bb = push(bb, zeros(i), n);
        i &= (i - 1);
    }
    return bb;
}
int main(){
    int n; scanf("%d", &n);
    unsigned long long bb = 0;
    unsigned long long rowB = (1ULL << n) - 1;
    for(int i = 0; i < n * n; i ++){
        char c; scanf(" %c", &c);
        if(c == '+' || c == '*' || c == '#')bb |= (1ULL << i);
    }
    for(int first = 0; first < (1ULL << n); first++){
        unsigned long long temp = pushAll(bb, first, n);
        for(int row = 0; row < n - 1; row++){
            unsigned long long lights = temp & (rowB << (n * row));
            temp = pushAll(temp, lights << n, n);
        }
        if(temp == 0){
            printf("Finally, Micheal can escape from Iran :)");
            return 0;
        }
    }

    printf("Micheal can't escape today, he has at most 26 days left!");
    return 0;
}