/* ALGO@ IN1 20A LAB01
   KACPER WINNIK
   wk47616@zut.edu.pl*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


struct myStruct {
    int myInt;
    char myChar;
    float myFloat;
};


struct myStruct** loadingRand(int n) {

    srand(time(NULL));
    struct myStruct** ptr = NULL;

    int upperInteger = 9000;
    int lowerInteger = -1000;
    int upperChar = 83;
    int lowerChar = 66;

    ptr = malloc(sizeof(struct myStruct*)*n);

    if (ptr == NULL) {
        printf("Zabrakło pamięci na stercie!");
        exit(-1);
    }

    for (int i = 0; i < n; i++) {
        int toRadnChar = (rand() % (upperChar - lowerChar + 1)) + lowerChar;

        ptr[i] = malloc(sizeof(struct myStruct));

        if (ptr[i] == NULL) {
            printf("Za mało pamięci na stercie!");
            for (int j = 0; j < i; j++) {
                free(ptr[j]);
             }
             free(ptr);
             exit(-1);
        }

        ptr[i]->myChar = (char)(toRadnChar);
        ptr[i]->myFloat = 1000 + i;
    }

    int deck[10000];
    int i, j, temp;

    for (i = 0; i < 10000; i++) {
        deck[i]=-1000 + i;
    }

    for (i = 0; i < 10000; i++) {
        j = (rand() % 9999) + 1;

        temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }

    for(i = 0 ; i < n; i++) {
        ptr[i]->myInt = deck[i];
    }

    return ptr;
}

void structFree(struct myStruct** ptr, int n) {

    for (int i = 0; i < n; i++) {
        free(ptr[i]);
    }
    free(ptr);
}

void bubbleSorting(struct myStruct** ptr, int n) {

    for (int i = 0; i < n; i++) {
        bool flag = false;
        for (int j = 0; j < n-1; j++) {
            if (ptr[j]->myInt > ptr[j+1]->myInt) {
                struct myStruct* swap = ptr[j];
                ptr[j] = ptr[j+1];
                ptr[j+1] = swap;
                flag = true;
            }
        }
        if(flag == false)
            return;
    }
}

int characterCounter(struct myStruct** ptr, int n, char x) {
    int counter = 0;
    for (int i = 0; i < n; i++) {
        if (ptr[i]->myChar == x) {
            counter = counter + 1;
        }
    }
    return counter;
}

void main() {

    int N;
    char X;
    FILE* fp =fopen("inlab01.txt", "r");
    if (fp == NULL) {
        return -1;
    }
    fscanf(fp, "%d %c", &N, &X);
    fclose(fp);

    clock_t begin, end;
    double time_spent;
    begin = clock();

    struct myStruct** myPtr = loadingRand(N);
    bubbleSorting(myPtr, N);
    int repQuantities = characterCounter(myPtr, N, X);
    for (int i = 0; i < 20; i++) {
        printf("%d\n", myPtr[i]->myInt);
        printf("%c\n", myPtr[i]->myChar);
        printf("%f\n\n", myPtr[i]->myFloat);
    }
    structFree(myPtr, N);

    end = clock();
    time_spent = ((double)(end - begin)) / CLOCKS_PER_SEC;

    printf("\nIlosc powtorzen znaku wynosi: %d\n", repQuantities);
    printf("Czas wykonania programu wynosi: %lf \n", time_spent);
}
