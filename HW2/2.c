#include <stdio.h>

int main(){
    int m; scanf("%d", &m);
    while(m--){
        long long n; scanf("%lld", &n);
        int kh = 0;
        while(n != 0){
            if(n % 3 == 0)kh = 1;
            n /= 10;
        }
        if(kh){
            printf("Oooh that’s good!\n");
        }else{
            printf("Oooh delom shikast!\n");
        }
    }


    return 0;
}