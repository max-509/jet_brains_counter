#ifndef JET_BRAINS_COUNTER_COUNTER_H
#define JET_BRAINS_COUNTER_COUNTER_H

#include <stdlib.h>
#include <time.h>
#include <stdatomic.h>
#include <stdio.h>

#define K 16

typedef struct counter counter;

struct counter *init();

unsigned simple_random(unsigned seed) {
    const unsigned a = 16807;
    const unsigned m = 2147483647;
    seed = (a * seed) % m;
    return seed / m;
}

int get(struct counter *c);

void inc(struct counter *c);

void destroy(struct counter *c);

struct counter {
    atomic_int subcounters[K];
};

counter *init() {
    counter *c = (counter *) malloc(sizeof(counter));

    for (unsigned i = 0; i < K; ++i) {
        atomic_init(&(c->subcounters[i]), 0);
    }

    return c;
}

void inc(counter *c) {
    unsigned random_idx = simple_random(time(NULL)) % K;
    atomic_fetch_add_explicit(&(c->subcounters[random_idx]), 1, memory_order_relaxed);
}

int get(counter *c) {
    int sum = 0;
    for (unsigned i = 0; i < K; ++i) {
        sum += atomic_load_explicit(&c->subcounters[i], memory_order_relaxed);
    }

    return sum;
}

void destroy(struct counter *c) {
    free(c);
}

#endif //JET_BRAINS_COUNTER_COUNTER_H
