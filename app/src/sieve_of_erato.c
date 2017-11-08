
#include <stdio.h>
#include <stdlib.h>

#include "dbg.h"

typedef struct count_prime {
    int count;
    int max_prime;
} count_prime;

/* Using sieve of Erato, find the maximum prime number less than or
 equal to the max_range. Natural numbers only.
 max_range must be larger than or equal to 2 */
count_prime sieve(int max_range) {
    int i,j;
    int max_prime = 2;
    int count;
    int* array_num;
    count_prime answer;

    check(max_range >= 2, "max_range must be larger than or equal to 2");

    /*initialize all numbers to 0, prime. 1 means non-prime.
    array_num[num] represent the non-prime-ness of number num */
    array_num = calloc(max_range+1, sizeof(int));

    // init count
    count = 0;

    // 0 and 1 to be marked as non-prime
    array_num[0] = 1;
    array_num[1] = 1;

    for (i = 2; i <= max_range; i++) {
        debug("Value of i: %d", i);
        if (!array_num[i]) {    // if prime
            debug("This number is prime");
            count++;
            debug("The count is %d", count);
            max_prime = i;
            debug("max_prime = %d", max_prime);
            for (j = 2*i; j <= max_range; j = j + i) {
                array_num[j] = 1;   // mark as non-prime
                debug("marked %d as non-prime", j);
            }
        } else {
            debug("This number is not prime.");
        }
    }

    debug("Returning %d as max_prime", max_prime);
    debug("Returning %d as count", count);

    answer.max_prime = max_prime;
    answer.count = count;
    return answer;

error:
    answer.max_prime = 0;
    answer.count = 0;
    return answer;
}


int main(int argc, char* argv[]) {
    //check(argc == 2, "Takes exactly 1 argument, the maximum number");
    int max_range;
    count_prime answer;

    max_range = 1000000; //strtol(argv[1], NULL, 10);
    answer = sieve(max_range);

    printf("Max_prime is %d\n", answer.max_prime );
    printf("Prime count is %d\n", answer.count);

    return 0;
}

