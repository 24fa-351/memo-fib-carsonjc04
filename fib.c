#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_FIB 1000

unsigned long long int fib_memo[MAX_FIB + 1] = {0};

unsigned long long int fib_r_core(unsigned long long int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fib_r_core(n - 1) + fib_r_core(n - 2);
}

unsigned long long int fib_r(unsigned long long int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    if (fib_memo[n] != 0) return fib_memo[n];
    fib_memo[n] = fib_r_core(n);
    return fib_memo[n];
}

unsigned long long int fib_i_core(unsigned long long int n) {
    unsigned long long int term_1 = 0, term_2 = 1, nextTerm;
    if (n == 0) return term_1;
    if (n == 1) return term_2;
    for (unsigned long long int i = 1; i < n; ++i) {
        nextTerm = term_1 + term_2;
        term_1 = term_2;
        term_2 = nextTerm;
    }
    return term_2;
}

unsigned long long int fib_i(unsigned long long int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    if (fib_memo[n] != 0) return fib_memo[n];
    fib_memo[n] = fib_i_core(n);
    return fib_memo[n];
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <integer> <method>\n", argv[0]);
        return 1;
    }

    unsigned long long int num_from_cli = strtoull(argv[1], NULL, 10);  
    char method = argv[2][0];                                           

    if (num_from_cli > MAX_FIB) {
        fprintf(stderr, "Error: Input exceeds memoization limit\n");
        return 1;
    }

    for (int i = 0; i <= MAX_FIB; ++i) fib_memo[i] = 0;

    unsigned long long int result;

    if (method == 'r') {
        result = fib_r(num_from_cli);
    } else if (method == 'i') {
        result = fib_i(num_from_cli);
    } else {
        fprintf(stderr, "Error: Method must be 'r' (recursive) or 'i' (iterative)\n");
        return 1;
    }

    printf("Fibonacci number at position %llu is %llu\n", num_from_cli, result);

    return 0;
}
