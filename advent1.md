 #ADVENT 2024

 Part 1

 ```c
#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    int int_a = *(int *)a;
    int int_b = *(int *)b;
    return int_a - int_b;
}

int main() {
    FILE* fp;

    fp = fopen("./input.txt", "r");

    if(fp == NULL) {
        printf("File read error!");
        exit(1);
    }
    int a;
    int b;
    int one[1000];
    int two[1000];

    for(int i = 0; i < 1000; i++) {
        if (fscanf(fp, "%d   %d", &a, &b) != 2) {
            printf("Something wrong");
            exit(1);
        }
        one[i] = a;
        two[i] = b;
    }


    qsort(one, 1000, sizeof(int), compare);
    qsort(two, 1000, sizeof(int), compare);

    printf("%d\n", one[3]);
    printf("%d\n", two[3]);

    int sum = 0;

    for(int i = 0; i < 1000; i++) {
        int temp = one[i] - two[i];
        if(temp < 0) {
            temp = temp * -1;
        }
        //printf("%d\n", temp);
        sum += temp;
    }
    printf("%d\n", sum);

}

```
Part 2

```c

#include <stdio.h>
#include <stdlib.h>

int wasSeen(int num, int arr[], int size) {
    for(int i = 0; i <= size; i++) {
        if(num == arr[i]) {
            return 1;
        }
    }
    return 0;
}
int main() {
    FILE* fp;

    fp = fopen("./input.txt", "r");

    if(fp == NULL) {
        printf("File read error!");
        exit(1);
    }
    int a;
    int b;
    int size = 0;
    int score = 0;
    int count = 0;
    int one[1000];
    int two[1000];
    int seen[1000];

    for(int i = 0; i < 1000; i++) {
        if (fscanf(fp, "%d   %d", &a, &b) != 2) {
            printf("Something wrong");
            exit(1);
        }
        one[i] = a;
        two[i] = b;
    }

    for(int i = 0; i < 1000; i++) {
        if(wasSeen(one[i], seen, size)) {
            continue;
        }
        count = 0;
        for(int j = 0; j < 1000; j++) {
            if(one[i] == two[j]) {
                count++;
            }
        }
        seen[size] = one[i];
        size++;
        score += count * one[i];

    }
    printf("%d\n", score);


}

```
