#include <stdio.h>

int main(){
    int m; scanf("%d", &m);
    while(m--){
        long long n; scanf("%lld", &n);
        int digits = 0;
        long long temp = n;
        while(temp){
            digits++;
            temp /= 10;
        }
        int mir = 1;
        for(int i = 0; i < digits; i++){
            temp = n;
            for(int j = 0; j < i; j++){
                temp /= 10;
            }
            int a = temp % 10;

            temp = n;
            for(int j = 0; j < digits - i - 1; j++){
                temp /= 10;
            }
            int b = temp % 10;

            if(a != b)mir = 0;
        }

        if(mir){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }




    return 0;
}