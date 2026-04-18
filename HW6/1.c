#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

typedef struct File{
    char *path;
    char *name;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    struct File *duplicate;
} File;

File * files[1000] = {NULL};
int files_count = 0;

File *duplicate_files[1000] = {NULL};
int duplicate_files_count = 0;

char * getName(char * path);

File* readFile(char *path);
void buildFileDatabase(char *path);
void addFile(File *file);

int isFile(struct dirent *entry);
int filecmp(File* f1, File* f2);

void getDuplicateFiles();
void sortDuplicateFiles();
void printDuplicateFiles();

void freeMemory();

void printFileStruct(File* f){
    printf("name: %s\npath: %s\nhash: ", f->name, f->path);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        printf("%02x", f->hash[i]);
    printf("\n\n");
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: Please provide a folder name.\nUsage: %s <folder_path>\n", argv[0]);
        return 1;
    }

    buildFileDatabase(argv[1]);

    getDuplicateFiles();
    sortDuplicateFiles();
    printDuplicateFiles();

    freeMemory();

    return 0;
}

int isFile(struct dirent *entry){
    int i = 0;
    while(entry->d_name[i] != '\0'){
        if(entry->d_name[i] == '.')return 1;
        i++;
    }
    return 0;
}

int filecmp(File* f1, File* f2){
    if(strcmp(f1->name, f2->name) != 0)return 0;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
        if(f1->hash[i] != f2->hash[i])return 0;
    }
    return 1;
}

char * getName(char * path){
    int lastSlash = 0;
    int i = 0;
    while(path[i] != '\0'){
        if(path[i] == '/')lastSlash = i;
        i++;
    }
    if(lastSlash){
        return path + lastSlash + 1;
    }
    return path;
}

File* readFile(char *path){
    File *fileStruct = malloc(sizeof(File));

    fileStruct->path = strdup(path);
    fileStruct->name = strdup(getName(fileStruct->path));
    fileStruct->duplicate = NULL;
    FILE *file = fopen(path, "rb");
    if (!file) {
        free(fileStruct);
        return NULL;
    }

    unsigned char data[1024];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;

    SHA256_Init(&ctx);

    size_t bytes;
    while ((bytes = fread(data, 1, 1024, file)) != 0)
        SHA256_Update(&ctx, data, bytes);

    SHA256_Final(hash, &ctx);

    fclose(file);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
        fileStruct->hash[i] = hash[i];
    }   

    return fileStruct;
}

void addFile(File *file) {
    for (int i = 0; i < files_count; i++) {
        if (filecmp(file, files[i])) {
            File *head = files[i];
            
            if (strcmp(file->path, head->path) < 0) {
                file->duplicate = head->duplicate;
                file->duplicate = head->duplicate;
                files[i] = file;
                file->duplicate = head;
                return;
            }

            File *prev = head;
            File *cur = head->duplicate;
            while (cur && strcmp(cur->path, file->path) < 0) {
                prev = cur;
                cur = cur->duplicate;
            }
            file->duplicate = cur;
            prev->duplicate = file;
            return;
        }
    }

    file->duplicate = NULL;
    files[files_count++] = file;
}



void buildFileDatabase(char *path){
    int len = strlen(path);
    DIR *dir = opendir(path);
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;
        char newPath[1024];
        snprintf(newPath, sizeof(newPath), "%s/%s", path, entry->d_name);
        if(isFile(entry)){
            File *f = readFile(newPath);
            if (f) addFile(f);
        }else{
            buildFileDatabase(newPath);
        }
    }
    closedir(dir);
}


void getDuplicateFiles(){
    for(int i = 0; i < files_count; i++){
        if(files[i]->duplicate != NULL){
            duplicate_files[duplicate_files_count] = files[i];
            duplicate_files_count++;
        }
    }
}

void sortDuplicateFiles() {
    for (int i = 0; i < duplicate_files_count - 1; i++) {
        for (int j = 0; j < duplicate_files_count - i - 1; j++) {
            if (strcmp(duplicate_files[j]->name, duplicate_files[j + 1]->name) > 0) {
                File *tmp = duplicate_files[j];
                duplicate_files[j] = duplicate_files[j + 1];
                duplicate_files[j + 1] = tmp;
            }
        }
    }
}


void printDuplicateFiles(){
    printf("Duplicated Files List:\n");
    for(int i = 0; i < duplicate_files_count; i++){
        printf("%d.(%s)\n", i + 1, duplicate_files[i]->name);
        File* f = duplicate_files[i];
        while(f != NULL){
            printf("%s\n", f->path);
            f = f->duplicate;
        }
        printf("\n");
    }
};

void freeFile(File* f){
    if(f->duplicate != NULL){
        freeFile(f->duplicate);
    }
    free(f);
}
void freeMemory() {
    for (int i = 0; i < files_count; i++) {
        freeFile(files[i]);
    }
    files_count = 0;
    duplicate_files_count = 0;
}
