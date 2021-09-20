#include "counter.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    counter *c;
    int n_inc;
} counter_test;

void *n_increments(void *data);

void serial_test();

void concurrent_inc_test();

void concurrent_inc_and_get_test();

int main() {
    serial_test();
    concurrent_inc_test();
    concurrent_inc_and_get_test();

    return 0;
}

void *n_increments(void *data) {
    counter_test *test = (counter_test *) data;
    for (int i = 0; i < test->n_inc; ++i) {
        inc(test->c);
    }

    pthread_exit(NULL);
}

void serial_test() {
    counter *c = init();

    const int n_inc = 14;

    for (int i = 0; i < n_inc; ++i) {
        inc(c);
    }

    int result = get(c);
#ifdef SERIAL_TEST
    printf("Result is equal %d: %s\n", n_inc, (result == n_inc) ? "true" : "false");
#endif // SERIAL_TEST

    destroy(c);
}

void concurrent_inc_test() {
    counter *c = init();

    const int n_inc_t1 = 8;
    const int n_inc_t2 = 4;
    const int n_inc_t3 = 2;
    const int n_inc = n_inc_t1 + n_inc_t2 + n_inc_t3;

    counter_test test1, test2, test3;

    test1.c = c;
    test1.n_inc = n_inc_t1;
    test2.c = c;
    test2.n_inc = n_inc_t2;
    test3.c = c;
    test3.n_inc = n_inc_t3;

    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, n_increments, &test1);
    pthread_create(&t2, NULL, n_increments, &test2);
    pthread_create(&t3, NULL, n_increments, &test3);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    int result = get(c);
#ifdef CONCURRENT_INC_TEST
    printf("Result is equal %d: %s\n", n_inc, (result == n_inc) ? "true" : "false");
#endif // CONCURRENT_INC_TEST

    destroy(c);
}

void concurrent_inc_and_get_test() {
    counter *c = init();

    inc(c);
    inc(c);

    int begin_value = get(c);

    const int n_inc_t1 = 3;
    const int n_inc_t2 = 3;
    const int n_inc_t3 = 4;
    const int n_inc = n_inc_t1 + n_inc_t2 + n_inc_t3;

    counter_test test1, test2, test3;

    test1.c = c;
    test1.n_inc = n_inc_t1;
    test2.c = c;
    test2.n_inc = n_inc_t2;
    test3.c = c;
    test3.n_inc = n_inc_t3;

    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, n_increments, &test1);
    pthread_create(&t2, NULL, n_increments, &test2);
    pthread_create(&t3, NULL, n_increments, &test3);

    int result = get(c);
#ifdef CONCURRENT_INC_AND_GET_TEST
    printf("Result in diapason [%d; %d]: %s\n", begin_value, (begin_value + n_inc),
           (begin_value <= result && result <= (begin_value + n_inc)) ? "true" : "false");
#endif // CONCURRENT_INC_AND_GET_TEST


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    destroy(c);
}
