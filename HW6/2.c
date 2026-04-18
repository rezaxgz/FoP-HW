#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Student{
    int id;
    char name[50];
    int age;
    char field[50];
} Student;

int get_next_id();
void insert();

void select_students();

void update();

void delete_student();

int main(){
    FILE* f = fopen("database.dat", "a");
    fclose(f);
    char cmd[50];
    scanf("%s", cmd);
    while(strcmp(cmd, "exit") != 0){
        if(strcmp(cmd, "INSERT") == 0){
            insert();
        }else if(strcmp(cmd, "SELECT") == 0){
            select_students();
        }else if(strcmp(cmd, "UPDATE") == 0){
            update();
        }else if(strcmp(cmd, "DELETE") == 0){
            delete_student();
        }

        scanf("%s", cmd);   
    }
    return 0;
}

int get_next_id() {
    FILE* db = fopen("database.dat", "rb");
    if(!db){
        fclose(db);
        return 1;
    }
    fseek(db, -(long)sizeof(Student), SEEK_END);

    Student lastStudent;

    if(fread(&lastStudent, sizeof(Student), 1, db) == 1){
        int id = lastStudent.id;
        fclose(db);
        return id + 1;
    }
    fclose(db);
    return 1;
}

void insert(){
    FILE *db = fopen("database.dat", "ab");
    int id = get_next_id();
    Student student;
    student.id = id;
    scanf(" student(%49[^,], %d, %49[^)])", student.name, &student.age, student.field);
    fwrite(&student, sizeof(Student), 1, db);
    fclose(db);
}  


void select_students(){
    FILE *db = fopen("database.dat", "rb");
    printf("----------\nID / name / age / field\n");

    Student s;

    while(fread(&s, sizeof(Student), 1, db) == 1){
        printf("%d %s %d %s\n", s.id, s.name, s.age, s.field);
    };
    printf("----------\n");
    fclose(db);
}

void update(){
    int id; 
    scanf(" ID: %d", &id);
    Student new_student;
    new_student.id = id;
    scanf(" student(%49[^,], %d, %49[^)])", new_student.name, &new_student.age, new_student.field);

    FILE *db = fopen("database.dat", "r+b");
    FILE *temp = fopen("temp.dat", "wb");

    Student currentStudent; 
    int found = 0;
    while(fread(&currentStudent, sizeof(Student), 1, db) == 1){
        if(currentStudent.id == id){
            fwrite(&new_student, sizeof(Student), 1, temp); 
            found = 1; 
        }else{
            fwrite(&currentStudent, sizeof(Student), 1, temp);
        }
    }
    if(found){
        printf("Record updated.\n");
    }else{
        printf("ID not found!\n");
    }
    fclose(db);
    fclose(temp);
    remove("database.dat");
    rename("temp.dat", "database.dat");
}

void delete_student(){
    int id; scanf(" ID: %d", &id);

    FILE *db = fopen("database.dat", "r+b");
    FILE *temp = fopen("temp.dat", "wb");

    Student currentStudent; 
    int found = 0;
    while(fread(&currentStudent, sizeof(Student), 1, db) == 1){
        if(currentStudent.id != id){
            fwrite(&currentStudent, sizeof(Student), 1, temp);
        }else{
            found = 1;
        }
    }
    if(found){
        printf("Record deleted.\n");
    }else{
        printf("ID not found!\n");
    }
    fclose(db);
    fclose(temp);
    remove("database.dat");
    rename("temp.dat", "database.dat");
}