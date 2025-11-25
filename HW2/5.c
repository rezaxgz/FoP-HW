#include <stdio.h>

int main(){
    while(1){
        int n; scanf("%d", &n);
        if(n == -1)break;
        unsigned long long k; scanf("%llu", &k);
        unsigned long long nk = ~k;
        int found = 0;
        for(int i = 0; i < (n * n); i++){
            if(nk & (1ULL << i))continue;
            if((i / n) < (n - 2)){
                if((k & (1ULL << (i + n))) && (k & (1ULL << (i + n + n))))found = 1;
                if((i % n) < (n - 2)){
                    if((k & (1ULL << (i + n + 1))) && (k & (1ULL << (i + n + n + 2))))found = 1;
                }
            }
            if((i % n) < (n - 2)){
                if((k & (1ULL << (i + 1))) && (k & (1ULL << (i + 2))))found = 1;
                if((i / n) > 1){
                    if((k & (1ULL << (i - n + 1))) && (k & (1ULL << (i - n - n + 2))))found = 1;
                }
            }
            // printf("%d %d\n", i, found);
        }
        if(found){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }
    printf("Congrats, Dory is home.\n");
    return 0;
}