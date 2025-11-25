#include <stdio.h>

int main(){
    unsigned long long m; scanf("%llu", &m);
    int first = 1;
    unsigned long long temp = m;    
    for(long long int i = 2; i * i <= temp; i++){
        if(temp == 1)break;
        int count = 0;
        while(temp % i == 0){
            temp /= i;
            count++;
        }
        if(count > 0){
            if(first == 0){
                printf(" * ");
            }
            if(count == 1){
                printf("%lld", i);
            }else{
                printf("%lld^%d", i, count);
            }
            first = 0;
        }
    }
    if(first != 1 && temp != 1){
        printf(" * ", m);
    }
    if(temp != 1){
        printf("%lld", temp);
    }
    return 0;
}