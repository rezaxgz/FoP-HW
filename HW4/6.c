#include <stdio.h>
#include <string.h>
int is_pal(char str[], int start, int len){
    int end = start + len - 1;
    while(start < end){
        if(str[start] != str[end])return 0;
        start++;
        end--;
    }
    return 1;
}
int main(){
    int n; scanf("%d", &n);
    char nnnn[505];
    fgets(nnnn, sizeof(nnnn), stdin);
    while(n--){
        char str[505];
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = 0;
        int length = 1;
        for(int i = 1; i <= 500; i++){
            if(str[i] == '\0' || str[i] == '\n'){
                length = i;
                break;
            }
        }
        int wl[length][length];
        for(int len = 1; len <= length; len++){
            for(int start = 0; (start + len - 1) < length; start++){
                if(is_pal(str, start, len) == 1){
                    wl[start][len] = 1;
                }else{
                    if(wl[start][len - 1] == 1)wl[start][len] = -1;
                    else if(wl[start + 1][len - 1] == 1)wl[start][len] = -1;
                    else wl[start][len] = 1;
                }
            }
        }
        if(is_pal(str, 0, length) == 1){
            printf("First");
        }else if(wl[0][length] == 1){
            printf("Second\n");
        }else{
            printf("First\n");
        }
    }


    return 0;
}