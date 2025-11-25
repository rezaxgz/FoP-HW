#include <stdio.h>

int main(){
    int m; scanf("%d", &m);
    int res = 0;
    for(int k = m - 1; k >= 0; k--){
        long long n; scanf("%lld", &n);
        long long temp = n;
        if(n < 0){
            temp = -temp;
        }
        long long sum = 0;
        while (temp){
            sum += temp % 10;
            temp /= 10;
        }
        long long mul = sum;
        int t = 0;
        for(int i = 0; i < 5; i++){
            if(mul == n) t = 1;
            mul *= sum;
        }

        res |= (t << k);
    }


    printf("%d", res);


    return 0;
}