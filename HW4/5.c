#include <stdio.h>
#include <string.h>
const char* roots[] = {"go", "run", "play", "right", "light", "happy", "quick", "art", "rat", "star"};
const int roots_len = 10;
int cursor = 1;
int len = 0;
void update_len(char str[]){
    len = strlen(str);
}
int isA(char a){
    if((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))return 1;
    return 0;
}
int isO(char c){
    return (c == 'a' || c == 'e' || c == 'i' ||
            c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' ||
            c == 'O' || c == 'U');
}
void insert_string(char *dest, const char *src, int pos) {
    int dest_len = strlen(dest);
    int src_len  = strlen(src);
    memmove(dest + pos + src_len, dest + pos, dest_len - pos + 1);
    memcpy(dest + pos, src, src_len);
}
int replace_range(char str[], int i, int j, const char *word) {
    int len = strlen(str);
    int word_len = strlen(word);
    int remove_len = j - i + 1;

    memmove(str + i + word_len, str + j + 1, len - j);

    memcpy(str + i, word, word_len);

    str[len + word_len - remove_len] = '\0';

    return word_len - remove_len;
}

int handle_root(char str[], int word_start, int word_end){
    char word[word_end - word_start + 2];
    for(int i = word_start; i <= word_end; i++){
        word[i - word_start] = str[i];
    }
    word[word_end - word_start + 1] = '\0';
    // printf("%d %d %s\n", word_start, word_end, word);
    for(int i = 0; i < roots_len; i++){
        if(strstr(word, roots[i]) != NULL){
            return replace_range(str, word_start, word_end, roots[i]);
        }
    }
    return 0;
}
void rooting(char str[]){
    int i = 0;
    while (1){
        if(str[i] == '\0')break;
        if(isA(str[i])){
            int start = i;
            while(isA(str[i + 1]))i++;
            int end = i;
            i += 1 + handle_root(str, start, end);
        }else{
            i++;
        }
    }
    if(cursor >= strlen(str)){
        cursor = strlen(str) - 1;
    }
}

void add(char *str, char word[]){
    if(isA(str[cursor])){
        int i = cursor;
        while(isA(str[i]))i++;
        insert_string(str, " ", i);
        insert_string(str, word, i + 1);
    }else{
        insert_string(str, word, cursor + 1);
        if(isA(str[cursor + 1 + strlen(word)]))insert_string(str, " ", cursor + 1 + strlen(word));
    }
}
void reverse(char str[]){
    if(isA(str[cursor]) == 0)return;
    int word_start = cursor;
    while(word_start > 0 && isA(str[word_start - 1]))word_start--;
    int word_end = cursor;
    int len = strlen(str);
    while(word_end + 1 < len && isA(str[word_end + 1]))word_end++;
    while(word_start < word_end){
        char a = str[word_start];
        char b = str[word_end];
        str[word_end] = a;
        str[word_start] = b;
        word_end--;
        word_start++;
    }
}
void wow(char str[]){
    int i = 0;
    int len = strlen(str);
    int in_word = 0;
    int word_len = 0;
    int count = 0;
    while(i < len){
        if(isA(str[i]) == 0){
            if(in_word == 1 && word_len > 4 && count > 1){
                insert_string(str, "!", i);
                i++;
                len++;
            }
            in_word = 0;
            word_len = 0;
            count = 0;
        }else{
            in_word = 1;
            word_len++;
            if(isO(str[i]))count++;
        }
        i++;
    }
    if(in_word == 1 && word_len > 4 && count > 1){
        insert_string(str, "!", i);
        i++;
        len++;
    }
}
char to_lower(char c) {
    if (c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}
char to_upper(char c) {
    if (c >= 'a') {
        return c - ('a' - 'A');
    }
    return c;
}
void lower(char str[]){
    int i = cursor;
    int len = strlen(str);
    while(isA(str[i]) && i < len){
        str[i] = to_lower(str[i]);
        i++;
    }
}
void upper(char str[]){
    int i = cursor;
    int len = strlen(str);
    while(isA(str[i]) && i < len){
        str[i] = to_upper(str[i]);
        i++;
    }
}
char shift(char a){
    if(a == 'z')return 'a';
    if(a == 'Z')return 'A';
    return a + 1;
}
void change(char str[], int amount){
    if(cursor + amount >= len){
        printf("Not enough characters.\n");
        return;
    }
    for(int i = cursor; i < cursor + amount; i++){
        if(isA(str[i]))str[i] = shift(str[i]);
    }
    cursor += amount;
}
void move(int amount){
    if(cursor + amount >= len || cursor + amount < 0){
        printf("Not enough characters.\n");
        return;
    }
    cursor += amount;
}
int main(){
    char str[505];
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    char cmd[500];
    cursor = 0;
    scanf("%s", &cmd);
    while(strcmp(cmd, "###") != 0){
        update_len(str);
        // printf("%s\n", cmd);
        if(strcmp(cmd, "rooting") == 0){
            rooting(str);
        }else if(strcmp(cmd, "add") == 0){
            char word[100];
            scanf("%s", word);
            add(str, word);
        }else if(strcmp(cmd, "reverse") == 0){
            reverse(str);
        }else if(strcmp(cmd, "WOW") == 0){
            wow(str);
        }else if(strcmp(cmd, "lower") == 0){
            lower(str);
        }else if(strcmp(cmd, "upper") == 0){
            upper(str);
        }else if(strcmp(cmd, "change") == 0){
            int amount; scanf("%d", &amount);
            change(str, amount);
        }else if(strcmp(cmd, "location") == 0){
            printf("%d\n", cursor);
        }else if(strcmp(cmd, "move") == 0){
            int amount; scanf("%d", &amount);
            move(amount);
        }
        // printf("%s\n", str);
        scanf("%s", &cmd);
    }
    printf("%s", str);
    return 0;
}