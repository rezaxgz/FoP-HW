#include <stdio.h>
#include <string.h>

int main(){
    char text[10001];
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';
    char words[10001][65];
    int count[10001] = {0};
    int word_count = 0;

    char temp[10001];
    strcpy(temp, text);
    char *token = strtok(temp, " ");

    while(token != NULL){
        int found = -1;
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                found = i;
                break;
            }
        }

        if (found == -1) {
            strcpy(words[word_count], token);
            count[word_count] = 1;
            word_count++;
        } else {
            count[found]++;
        }

        token = strtok(NULL, " ");
    }

    char result1[20001] = {'\0'};

    token = strtok(text, " ");  
    while(token != NULL){
        int found = -1;
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                found = i;
                break;
            }
        }
        if(count[found] == 1){
            strcat(result1, words[found]);
            strcat(result1, " ");
            token = strtok(NULL, " ");
            continue;
        }else{
            char num[20];
            int n = -1;
            for(int x = 0; x <= found; x++)if(count[x] > 1)n++;
            sprintf(num, "%d", n);
            strcat(result1, num);
            char cur[65];
            strcpy(cur, token);
            token = strtok(NULL, " ");
            int rep = 1;
            while(token != NULL && strcmp(cur, token) == 0){
                rep++;
                token = strtok(NULL, " ");
            }
            if(rep > 1){
                char repp[20];
                sprintf(repp, "[%d]", rep);
                strcat(result1, repp);
            }
            strcat(result1, " ");
        }
    }
    int index = 0;
    int i = 0;
    while(i < word_count){
        if(count[i] > 1){
            printf("%d: %s\n", index, words[i]);
            index++;
        }
        i++;
    }
    printf("%s", result1);
    return 0;
}