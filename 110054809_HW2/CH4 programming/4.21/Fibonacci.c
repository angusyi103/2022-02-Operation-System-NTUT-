#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int fibAry[100000]; //shared array

void *fibonacci(void *input) {
    int f1 = 0, f2 =1, num;
    for (int i = 0; i < *(int *) input; i++) {
        if (i <= 1) {
            num = i;
        } else {
            num = f1 + f2;
            f1 = f2;
            f2 = num;
        }
        fibAry[i] = num;
    }

    pthread_exit(0);
}

int main() {
    printf("Enter the number of Fibonacci numbers to generate: ");
    int input;
    scanf("%d", &input);

    pthread_t thread;
    pthread_create(&thread, NULL, fibonacci, (void *) &input);
    pthread_join(thread, NULL);

    for (int i = 0; i < input; i++) {
        printf("%d ", fibAry[i]);
    }

    printf("\n");
    return 0;
}