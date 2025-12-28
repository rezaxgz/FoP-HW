#include <stdio.h>
char shift(char a, int n){
    if(a >= 'A' && a <= 'Z')
        return 'A' + ((a - 'A' + n + 26) % 26);
    if(a >= 'a' && a <= 'z')
        return 'a' + ((a - 'a' + n + 26) % 26);

    return a;
}
int main(){
    char str[5000];
    fgets(str, sizeof(str), stdin);
    int freq[26] = {0};
    int count = 0;
    int len;
    for(int i = 0; i < 5000; i++){
        if(str[i] == '\0' || str[i] == '\n'){
           len = i;
           break;
        }
        char a = str[i];
        if(a >= 'A' && a <= 'Z'){
            freq[a - 'A']++;
            count++;
        }
        if(a >= 'a' && a <= 'z'){
            freq[a - 'a']++;
            count++;
        }
    }
    int max = 0;
    int max_i = 0;
    for(int i = 0; i < 26; i++){
        if(freq[i] > max){
            max = freq[i];
            max_i = i;
        }
    }

    if(((count * 10) <= (max * 100)) && ((max * 100) <= (14 * count))){
        int n = (max_i - 4 + 26) % 26;
        printf("%d\n", n);
        for(int i = 0; i < len; i++){
            str[i] = shift(str[i], -n);
        }
        printf("%s", str);
    }else{
        printf("Ciphertext is either too short or not a Caesar cipher!\n");
    }
    return 0;
}