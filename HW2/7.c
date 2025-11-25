#include <stdio.h>

int main(){
    unsigned long long n;
    scanf("%llu", &n);
    unsigned long long badzeros = 18411139144890810879ULL & (n ^ 18411139144890810879ULL);
    n ^= badzeros;
    for(int i = 0; i < 64; i++){
        for(int j = 0; j < 64; j++){
            if(((n >> j) & 1) == 0){
                if(j < 56 && ((badzeros >> (j + 8)) & 1)){
                    badzeros |= 1ULL << j;
                }
                if(j > 7 && ((badzeros >> (j - 8)) & 1)){
                    badzeros |= 1ULL << j;
                }
                if((j & 7) != 7 && ((badzeros >> (j + 1)) & 1)){
                    badzeros |= 1ULL << j;
                }
                if((j & 7) != 0 && ((badzeros >> (j - 1)) & 1)){
                    badzeros |= 1ULL << j;
                }
            }
        }
    }
    n |= badzeros;
    int count = 0;
    while(~n != 0){
        unsigned long long zeros = (~n) & ((~n) - 1) ^ (~n);
        n ^= zeros;
        for(int i = 0; i < 64; i++){
            for(int j = 0; j < 64; j++){
                if(((n >> j) & 1) == 0){
                    if(j < 56 && ((zeros >> (j + 8)) & 1)){
                        zeros |= 1ULL << j ;
                        n |= 1ULL << j ;
                    }
                    if(j > 7 && ((zeros >> (j - 8)) & 1)){
                        zeros |= 1ULL << j ;
                        n |= 1ULL << j ;
                    }
                    if((j & 7) != 7 && ((zeros >> (j + 1)) & 1)){
                        zeros |= 1ULL << j ;
                        n |= 1ULL << j ;
                    }
                    if((j & 7) != 0 && ((zeros >> (j - 1)) & 1)){
                        zeros |= 1ULL << j ;
                        n |= 1ULL << j ;
                    }
                }
            }
        }
        count++;
    }
    printf("%d", count);
    return 0;
}
