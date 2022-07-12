#include<stdio.h>
#include<stdlib.h>

#define pageSize 4096

int main(int argc, char *argv[]) {
    unsigned long page, offset, address;

    address = atoi(argv[1]);
    page = address / pageSize;
    offset = address % pageSize;
    
    printf("The address 19986 contains:\n");
    printf("page number = %lu\n", page);
    printf("offset = %lu\n", offset);
    return 0;
}