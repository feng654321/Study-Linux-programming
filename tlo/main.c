// main.c
#include <stdio.h>
#include "math.h"

int main() {
    int a = 5;
    int b = 3;
    int i = 1;
    for(i=0;i<1000;i++){
    printf("Add: %d\n", add(a, b));
    printf("Multiply: %d\n", multiply(a, b));}
    return 0;
}

