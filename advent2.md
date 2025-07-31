# ADVENT 2024

Part 1:

```c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
void printLine(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int isOneDir(int arr[], int size) {
    int down= 0;
    int up = 0;
    for(int i = 0; i < size - 1; i++) {
        if(arr[i] - arr[i + 1] < 0){
            up++;
        }
        if(arr[i] - arr[i + 1] > 0){
            down++;
        }
        
    }
    return (up == size - 1 || down == size - 1);
}
int isSafe(int arr[], int size) {
    for(int i = 0; i < size - 1; i++) {
        if(arr[i] - arr[i + 1] == 0 || abs(arr[i] - arr[i + 1]) > 3) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int total = 0;
    char line[MAX];
    int nums[MAX];

    FILE* fp = fopen("./input2.txt", "r");

    if(fp == NULL) {
        printf("failed to read file\n");
        return 1;
    }
    while(fgets(line, sizeof(line), fp)) {
        int count = 0;

        char* token = strtok(line, " \n");
        while(token != NULL) {
            int value = atoi(token);
            nums[count] = value;
            count++;
            token = strtok(NULL, " \n");
        }
        //printLine(nums, count);
        if (isOneDir(nums,count) && isSafe(nums, count)) {
            total++;
        }
    }

    printf("%d\n", total);



}

```
Part 2:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

void printLine(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int isOneDir(int arr[], int size) {
    int down = 0;
    int up = 0;
    for(int i = 0; i < size - 1; i++) {
        if(arr[i] - arr[i + 1] < 0){
            up++;
        }
        if(arr[i] - arr[i + 1] > 0){
            down++;
        }
        
    }
    return (up == size - 1 || down == size - 1);
}
int isSafe(int arr[], int size) {
    int bad = 0;
    for(int i = 0; i < size - 1; i++) {
        if(arr[i] - arr[i + 1] == 0 || abs(arr[i] - arr[i + 1]) > 3) {
            return 0;
        }
    }
    return 1;
}

int check(int arr[], int size) {
    if (isOneDir(arr, size) && isSafe(arr, size)) {
            return 1;
    }

    for(int i = 0; i < size; i++) {
        int temp[MAX];
        int k = 0;

        for(int j = 0; j < size; j++) {
            if(j != i) {
                temp[k++] = arr[j];
            }
        }

        if (isOneDir(temp, k) && isSafe(temp, k)) {
            return 1;
        }
    }
    return 0;


}

int main() {
    int total = 0;
    char line[MAX];
    int nums[MAX];

    FILE* fp = fopen("./input2.txt", "r");

    if(fp == NULL) {
        printf("failed to read file\n");
        return 1;
    }
    while(fgets(line, sizeof(line), fp)) {
        int count = 0;

        char* token = strtok(line, " \n");
        while(token != NULL) {
            int value = atoi(token);
            nums[count] = value;
            count++;
            token = strtok(NULL, " \n");
        }
        //printLine(nums, count);
        if (check(nums, count)) {
            total++;
        }
    }

    printf("%d\n", total);



}
```


