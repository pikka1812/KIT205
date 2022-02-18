//
//  main.c
//  Tutorial 2
//
//  Created by Phong on 19/02/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long f1(long n){
    long k = 0;
    for (long i = 0; i < n; i++){
           for (long j = 0; j < n; j++){
                  k++;
           }
    }
    return k;
}

void f2(long n){
    long k = 0;
    for (long i = 0; i < n; i++){
          for (long j = 0; j < i; j++){
                  k++;
          }
          for (long t = 0; t < 10000; t++){
                  k++;
          }
    }
}

void f3(long n){
    if (n > 0){
           f3(n / 2);
           f3(n / 2);
    }
}

void f4(long n){
    if (n > 0){
           f4(n / 2);
           f4(n / 2);
           f2(n);
    }
}

void f5(long n){
    long k = 0;
    for (long i = 0; i < 10; i++){
          long j = n;
          while (j > 0){
                  f1(1000);
                  k++;
                  j = j / 2;
          }
    }
}

void f6(long n){
    f2(n);
    f3(n);
    f5(n);
}

void f7(long n){
    long k = 0;
    for (long i = 0; i < f1(n); i++){
           k++;
    }
    for (long j = 0; j < n; j++){
           k++;
    }
}

void calculate_time(clock_t start) {
    clock_t diff = clock() - start;
    long msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Operation took %ld milliseconds\n\n", msec);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int quit = 0;
    while (!quit) {
        int option;
        printf("Choose the option: ");
        scanf("%d", &option);
        if(option != 0) {
            long n;
            printf("Enter a value for n: ");
            scanf("%ld", &n);
            clock_t start = clock();

            switch(option) {
                case 1:
                    f1(n);
                    calculate_time(start);
                    break;
                case 2:
                    f2(n);
                    calculate_time(start);
                    break;
                case 3:
                    f3(n);
                    calculate_time(start);
                    break;
                case 4:
                    f4(n);
                    calculate_time(start);
                    break;
                case 5:
                    f5(n);
                    calculate_time(start);
                    break;
                case 6:
                    f6(n);
                    calculate_time(start);
                    break;
                case 7:
                    f7(n);
                    calculate_time(start);
                    break;
            }
        }
        else quit = 1;
    }
    return 0;
}
