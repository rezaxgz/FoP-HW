#include <stdio.h>

int main(){
    int n; 
    scanf("%d", &n);

    while(n--){
        unsigned long long x; 
        scanf("%llu", &x);

        int isCol = 1;
        for(int c = 0; c < 4; c++){
            unsigned long long a = ((x >> (c)) & 0x101010101010101ULL);
            unsigned long long b = ((x >> (7 - c)) & 0x101010101010101ULL);
            if(a != b) isCol = 0;
        }

        int isRow = 1;
        for(int r = 0; r < 4; r++){
            unsigned long long a = ((x >> ((r) << 3)) & 0xFF);
            unsigned long long b = ((x >> ((7 - r) << 3)) & 0xFF);
            if(a != b) isRow = 0;
        }

        int isPosD = 1;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                unsigned long long sq1 = ((i << 3) | j);
                unsigned long long sq2 = ((j << 3) | i);
                unsigned long long bit1 = ((x >> (sq1)) & 1ULL);
                unsigned long long bit2 = ((x >> (sq2)) & 1ULL);
                if(bit1 != bit2) isPosD = 0;
            }
        }

        int isNegD = 1;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                unsigned long long sq1 = ((i << 3) | j);
                unsigned long long sq2 = (((7 - j) << 3) | (7 - i));
                unsigned long long bit1 = ((x >> (sq1)) & 1ULL);
                unsigned long long bit2 = ((x >> (sq2)) & 1ULL);
                if(bit1 != bit2) isNegD = 0;
            }
        }

        printf("%d ", isCol + isNegD + isPosD + isRow);

        if(isCol) printf("V");
        if(isRow) printf("H");
        if(isPosD) printf("A");
        if(isNegD) printf("B");

        if((isCol + isNegD + isPosD + isRow) == 0){
            printf("-");
        }

        printf("\n");
    }

    return 0;
}
