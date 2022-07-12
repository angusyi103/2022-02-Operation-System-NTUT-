#include<sys/wait.h>
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int collatz(int n) {
    if (n%2 ==0) {
        return n/2;
    } else {
        return n*3 + 1;
    }
}

int main () {
    int i;
    scanf("%d", &i);

    if (i < 0) {
        printf("error input");
        return 0;
    }

    pid_t pid;
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    } else if (pid == 0) { // child
        while (1) {
            if (i == 1) {
                printf("%d\n", i);
                break;
            } else {
                printf("%d, ", i);
            }

            i = collatz(i);
        }
    } else { //parent
        wait(NULL);
        printf("child complete");
    }
    
    return 0;
}