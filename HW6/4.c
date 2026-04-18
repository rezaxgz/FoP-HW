#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef enum JsonType{
    NUMBER,
    STRING,
    OBJECT
} JsonType;

typedef struct JsonValue JsonValue;

typedef struct JsonPair{
    char *key;
    JsonValue *value;
} JsonPair;

typedef struct JsonObject{
    JsonPair *pairs;
    size_t count;
} JsonObject;


struct JsonValue {
    JsonType type;
    union {
        int number;
        char *string;
        JsonObject object;
    };
};

JsonValue* parse_value(const char **json);
JsonObject parse_object(const char **json);
char* parse_string(const char **json);
int parse_number(const char **json);

void skip_whitespace(const char **json);

int calculate_depth(JsonValue *v, int ply);
void getType(char *path, JsonValue *v);
void getValue(char *path, JsonValue *v);


int main(){
    char filename[50];
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    FILE *fp = fopen(filename, "r");
    fseek(fp, 0, SEEK_END);
    int count = ftell(fp) / sizeof(char);

    fseek(fp, 0, SEEK_SET);
    char *JsonString = malloc(sizeof(char) * (count + 1));

    fread(JsonString, sizeof(char), count, fp);
    fclose(fp);
    JsonString[count] = '\0';
    const char *ptr = JsonString;
    JsonValue *json = parse_value(&ptr);
    
    char line[1000];
    
    
    while(fgets(line, sizeof(line), stdin)){
        line[strcspn(line, "\n")] = '\0';
        if(strncmp(line, "exit", 4) == 0){
            break;
        }else if(strncmp(line, "depth", 5) == 0){
            printf("%d\n", calculate_depth(json, 0));
        }else if(strncmp(line, "typeof", 6) == 0){
            char path[1024];
            sscanf(line, "typeof %s", path);
            getType(path, json);
        }else if(strncmp(line, "valueof", 7) == 0){
            char path[1024];
            sscanf(line, "valueof %s", path);
            getValue(path, json);
        }
    }

    return 0;
}

int calculate_depth(JsonValue *v, int ply){
    if(v->type == NUMBER || v->type == STRING){
        return ply;
    }
    int max_ply = ply + 1;
    if(v->type == OBJECT){
        for(int i = 0; i < v->object.count; i++){
            int p = calculate_depth(v->object.pairs[i].value, ply + 1);
            if(p > max_ply)max_ply = p;
        }
    }
    return max_ply;
}

void getValue(char *path, JsonValue *v){
    char *ptr = strtok(path, ".");
    while(ptr != NULL){
        int found = 0;
        for(int i = 0; i < v->object.count; i++){
            if(strcmp(v->object.pairs[i].key, ptr) == 0){
                v = v->object.pairs[i].value;
                found = 1;
                break;
            }
        }
        if(found == 0){
            printf("No value found for this address!!\n");
            return;
        }
        ptr = strtok(NULL, ".");
    }
    if(v->type == NUMBER){
        printf("%d\n", v->number);
    }else if(v->type == STRING){
        printf("%s\n", v->string);
    }else{
        printf("I can not print objects!\n");
    }

}

void getType(char *path, JsonValue *v){
    char *ptr = strtok(path, ".");
    while(ptr != NULL){
        int found = 0;
        for(int i = 0; i < v->object.count; i++){
            if(strcmp(v->object.pairs[i].key, ptr) == 0){
                v = v->object.pairs[i].value;
                found = 1;
                break;
            }
        }
        if(found == 0){
            printf("No value found for this address!!\n");
            return;
        }
        ptr = strtok(NULL, ".");
    }
    if(v->type == NUMBER){
        printf("INT\n");
    }else if(v->type == STRING){
        printf("STRING\n");
    }else{
        printf("OBJECT\n");
    }
};

void skip_whitespace(const char **json) {
    while (**json == ' ' || **json == '\n' || **json == '\r' || **json == '\t') {
        (*json)++;
    }
}

char* parse_string(const char **json){
    if (**json != '"') return NULL;
    (*json)++;
    const char *start = *json;
    while(**json != '"') (*json)++;
    int len = *json - start;
    char *string = malloc(sizeof(char) * (len + 1));
    strncpy(string, start, len);
    string[len] = '\0';
    (*json)++;

    return string;
}

int parse_number(const char **json){
    int num;
    sscanf(*json, "%d", &num);
    while(isdigit(**json) || strchr("+-", **json))(*json)++;
    return num;
}

JsonObject parse_object(const char **json){
    JsonObject obj;
    obj.count = 0;
    obj.pairs = NULL;

    if((**json) != '{')return obj;
    (*json)++;
    skip_whitespace(json);
    while(**json != '}'){
        skip_whitespace(json);
        obj.pairs = realloc(obj.pairs, sizeof(JsonPair) * (obj.count + 1));
        obj.pairs[obj.count].key = parse_string(json);

        skip_whitespace(json);
        if((**json) == ':')(*json)++;
        skip_whitespace(json);

        obj.pairs[obj.count].value = parse_value(json);
        obj.count++;
        skip_whitespace(json);
        if(**json == ',')(*json)++;
    }
    skip_whitespace(json);
    if((**json) == '}')(*json)++;
    return obj;
}

JsonValue* parse_value(const char **json){
    skip_whitespace(json);
    JsonValue *v = malloc(sizeof(JsonValue));
    if((**json) == '{'){
        v->type = OBJECT;
        v->object = parse_object(json);
    }else if(isdigit(**json) || **json == '.' || **json == '-'){
        v->type = NUMBER;
        v->number = parse_number(json);
    }else if(**json == '"'){
        v->type = STRING;
        v->string = parse_string(json);
    }else{
        free(v);
        return NULL;
    }
    return v;
}
