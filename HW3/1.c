#include <stdio.h>

void removeChar(char text[], int size, int index){
    for(int i = index + 1; i < size; i++){
        text[i - 1] = text[i];
    }
}
int len(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}
void copy(char dest[], const char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
void cat(char dest[], const char src[]) {
    int i = len(dest);
    int j = 0;
    while (src[j] != '\0') {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
}
void insertChar(char text[], int size, int index, char c) {
    for (int i = size - 1; i >= index; i--) {
        text[i + 1] = text[i];
    }
    text[index] = c;
}
void insertString(char text[], int size, int index, const char str[]) {
    int l = 0;
    while (str[l] != '\0') l++;

    for (int i = size - 1; i >= index; i--) {
        text[i + l] = text[i];
    }

    for (int j = 0; j < l; j++) {
        text[index + j] = str[j];
    }
}
void clean_up(char text[], int size){
    char last = '\0';
    for(int i = 0; i < size; i++){
        char cur = text[i];
        if(last == ' ' && cur == ' '){
            removeChar(text, size, i);
            size--;
            i--;
            continue;
        };
        if(cur == '.' || cur ==  ',' || cur == '!' || cur ==  '?'){
            if(last == ' '){
                removeChar(text, size, i - 1);
                i--;
                size--;
                last = cur;
                continue;
            }
        }
        if(last == '.' || last ==  ',' || last == '!' || last ==  '?'){
            if(cur != ' '){
                insertChar(text, size, i, ' ');
                last = cur;
                size++;
                continue;
            }
        }
        last = cur;
    }
    text[size] = '\0';
}
int validate(char text[], int size){
    for(int i = 0; i < size; i++){
        char cur = text[i];
        if((cur == ' ') || (cur >= '0' && cur <= '9') || (cur >= 'a' && cur <= 'z') || (cur >= 'A' && cur <= 'Z') || (cur < 48 && cur > 41) || cur == '!' || cur == '?' || cur == '=')continue;
        return 0;
    }
    return 1;
};


int strint(char str[]) {
    int result = 0;
    int i = 0;
    while (str[i] != '\0') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}

const char *ones[]  = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const char *teens[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
const char *tens[]  = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};


void twodigit(int n, char output[]) {
    output[0] = '\0';

    if (n >= 20) {
        copy(output, tens[n / 10]);
        if (n % 10) {
            cat(output, " ");
            cat(output, ones[n % 10]);
        }
    } else if (n >= 10) {
        copy(output, teens[n - 10]);
    } else if (n > 0) {
        copy(output, ones[n]);
    }
}

void numToWord(int n, char output[]) {
    output[0] = '\0';
    if (n == 0) {
        copy(output, "zero");
        return;
    }

    int m = n % 1000;
    char s[200];
    s[0] = '\0';

    if (m >= 100) {
        cat(s, ones[m / 100]);
        cat(s, " hundred");
        m %= 100;
        if (m) cat(s, " ");
    }

    if (m) {
        char ss[100];
        ss[0] = '\0';
        twodigit(m, ss);
        cat(s, ss);
    }

    copy(output, s);
}
int ex(char cur){
    return cur == '+'||cur=='-'||cur=='*'||cur=='/'||cur=='=';
}
int read(char text[], int index) {
    int i = index;
    int j = 0;
    char dest[7];
    while (text[i] != '\0' && text[i] != ' ' && text[i] <= '9' && text[i] >= '0')  {
        dest[j++] = text[i++];
    }
    dest[j] = '\0';
    if((index > 0 && ex(text[index - 1])) || (text[i] != '\0' && ex(text[i]))){
        return -1;
    }
    return strint(dest);
}
void decoding(char text[], int size){
    int x = 0;
    char prev = '\0';
    for(int i = 0; i < size; i++){
        char cur = text[i];
        if(cur >= '0' && cur <= '9'){
            if(prev >= '0' && prev <= '9'){
                continue;
            };
            int n = read(text, i);
            if(n == -1){
                prev = cur;
                continue;
            };
            int l = 0;
            int m = n;
            if(m == 0)l = 1;
            while(m){
                l++;
                m /= 10;
            }
            for(int j = 0; j < l; j++){
                removeChar(text, size, i);
                size--;
            }
            char number[100];
            numToWord(n, number);
            insertString(text,len(text), i, number);
            i += len(number);
            size += len(number);
        }
        prev = cur;
    }
    text[size] = '\0';
};

int main(){
    char str[5000];

    fgets(str, sizeof(str), stdin);
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
    if(validate(str, len(str)) == 0){
        printf("The message may have been leaked!");
        return 0;
    }
    clean_up(str, len(str));
    decoding(str, len(str));
    // clean_up(str, len(str));
    printf("%s\n", str);
    return 0;
}