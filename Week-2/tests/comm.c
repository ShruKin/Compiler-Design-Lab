#include <stdio.h>

/*
  This program calculates the sum* of the
  first 10 natural numbers
*/

int main(int argc, char const *argv[]) {
    int sum = 0;  // initializing sum to zero

    for (int i = 0; i < 10 /* running 10 times */; i++) {
        sum += i;
    }

    printf("%d", sum);

    return 0;
}
