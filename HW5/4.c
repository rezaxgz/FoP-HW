#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Car{
    char plate[100];
    char color[100];
    Car *behind;
} Car;
enum LANE{
    LEFT_LANE,
    RIGHT_LANE,
};
int len[2] = {0, 0};
Car* create_car(char plate[], char color[]) {
    Car* newCar = (Car*)malloc(sizeof(Car));
    if(!newCar){
        printf("failed\n");
        return NULL;
    }
    strcpy(newCar->plate, plate);
    strcpy(newCar->color, color);
    newCar->behind = NULL;
    return newCar;
}
void add(char plate[], int pos, char color[], Car **head){
    if (*head == NULL && pos != 1) {
        printf("wrong add call\n");
        return;
    }
    Car *new_car = create_car(plate, color);
    if(pos == 1){
        new_car->behind = *head;
        *head = new_car;
        return;
    }
    int i = 1;
    Car *temp = *head;
    while(i < pos - 1){
        temp = temp->behind;
        i++;
    }
    new_car->behind = temp->behind;
    temp->behind = new_car;
}
void checked_add(Car **right_lane, Car **left_lane){
    int lane; scanf("%d", &lane);
    int k; scanf("%d", &k);
    char plate[100]; scanf("%s", plate);
    char color[100]; scanf("%s", color);
    Car *cur = *right_lane;
    while(cur != NULL){
        if(strcmp(cur->plate, plate) == 0){
            printf("this plate was already given\n");
            return;
        }
        cur = cur->behind;
    }
    cur = *left_lane;
    while(cur != NULL){
        if(strcmp(cur->plate, plate) == 0){
            printf("this plate was already given\n");
            return;
        }
        cur = cur->behind;
    }
    if(lane == LEFT_LANE && k > len[LEFT_LANE] + 1 || lane == RIGHT_LANE && k > len[RIGHT_LANE] + 1){
        printf("an invalid number is given\n");
        return;
    }
    add(plate, k, color, lane == LEFT_LANE ? left_lane : right_lane);
    len[lane]++;
}
void output(Car *right_lane, Car *left_lane){
    printf("lane 0:\n");
    Car *car_ptr = left_lane;
    while(car_ptr != NULL){
        printf("%s (%s)\n", car_ptr->plate, car_ptr->color);
        car_ptr = car_ptr->behind;
    }
    printf("**********\nlane 1:\n");
    car_ptr = right_lane;
    while(car_ptr != NULL){
        printf("%s (%s)\n", car_ptr->plate, car_ptr->color);
        car_ptr = car_ptr->behind;
    }
}
void delete_black_cars(Car **head, int i){
    if((*head) == NULL)return;
    while(*head && strcmp("black", (*head)->color) == 0){
        Car* next = (*head)->behind;
        free(*head);
        *head = next;
        len[i]--;
    }
    if((*head) == NULL)return;
    Car *temp = *head;
    while(temp->behind != NULL){
        if(strcmp(temp->behind->color, "black") == 0){
            Car* next = temp->behind->behind;
            free(temp->behind);
            len[i]--;
            temp->behind = next;
        }else{
            temp = temp->behind;
        }
    }
}
int find(char plate[], Car *lane){
    int pos = 1;
    while(lane != NULL){
        if(strcmp(lane->plate, plate) == 0){
            return pos;
        }
        pos++;
        lane = lane->behind;
    }
    return 0;
}
void change(Car **right_lane, Car **left_lane){
    char plate[100]; scanf("%99s", plate);
    Car **cur_lane;
    Car **other_lane;
    int lane_number;
    if(find(plate, *right_lane) != 0){
        cur_lane = right_lane;
        other_lane = left_lane;
        lane_number = RIGHT_LANE;
    }else if(find(plate, *left_lane) != 0){
        cur_lane = left_lane;
        other_lane = right_lane;
        lane_number = LEFT_LANE;
    }else{
        printf("Car not found\n");
        return;
    }
    Car *temp = *cur_lane;
    int pos = 2;
    if(strcmp(temp->plate, plate) == 0){
        add(plate, 1, temp->color, other_lane);
        len[lane_number ^ 1]++;
        Car *del = temp;
        *cur_lane = (*cur_lane)->behind;
        free(del);
        len[lane_number]--;
    }else{
        while(temp->behind && strcmp(temp->behind->plate, plate) != 0){
            temp = temp->behind;
            pos++;
        }
        Car *target = temp->behind;
        add(plate, pos > (len[lane_number ^ 1] + 1) ? (len[lane_number ^ 1] + 1): pos, target->color, other_lane);
        len[lane_number ^ 1]++;
        temp->behind = target->behind;
        free(target);
        len[lane_number]--;
    }
}
void overtake(Car **left_lane, Car **right_lane){
    char plate[100]; scanf("%99s", plate);
    int number; scanf("%d", &number);

    if(number < 1){
        printf("an invalid number is given\n");
        return;
    }
    Car **lane;
    int pos = find(plate, *left_lane);
    if(pos != 0){
        lane = left_lane;
    }else{
        pos = find(plate, *right_lane);
        if(pos != 0){
            lane = right_lane;
        }else{
            printf("Car not found\n");
            return;
        }
    }

    int target_pos = (number >= pos) ? 1 : pos - number;

    if(pos == 1)return;

    Car *prev = *lane;
    for(int i = 2; i < pos; i++){
        prev = prev->behind;
    }
    Car *node = prev->behind;
    prev->behind = node->behind;

    if(target_pos == 1){
        node->behind = *lane;
        *lane = node;
    }else{
        Car *cur = *lane;
        for(int i = 2; i < target_pos; i++){
            cur = cur->behind;
        }
        node->behind = cur->behind;
        cur->behind = node;
    }
}
int main(){
    Car *right_lane = NULL;
    Car *left_lane = NULL;

    char cmd[500];
    while(1){
        scanf("%499s", cmd);
        if(strcmp(cmd, "add") == 0){
            checked_add(&right_lane, &left_lane);
        }else if(strcmp(cmd, "EXIT") == 0){
            break;
        }else if(strcmp(cmd, "delete") == 0){
            delete_black_cars(&right_lane, RIGHT_LANE);
            delete_black_cars(&left_lane, LEFT_LANE);
        }else if(strcmp(cmd, "change") == 0){
            change(&right_lane, &left_lane);
        }else if(strcmp(cmd, "print") == 0){
            output(right_lane, left_lane);
        }else if(strcmp(cmd, "overtake") == 0){
            overtake(&left_lane, &right_lane);
        }
    }

    output(right_lane, left_lane);
}