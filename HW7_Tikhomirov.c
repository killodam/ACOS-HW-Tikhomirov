#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4

/* Global sum protected by mutex */
long long sum = 0;
pthread_mutex_t sum_mutex = PTHREAD_MUTEX_INITIALIZER;

/* Struct passed to each thread */
typedef struct {
    int *arr;
    int start;
    int end;   /* exclusive */
} ThreadArgs;

void *worker(void *arg) {
    ThreadArgs *ta = (ThreadArgs *)arg;
    long long local_sum = 0;

    for (int i = ta->start; i < ta->end; i++)
        local_sum += ta->arr[i];

    pthread_mutex_lock(&sum_mutex);
    sum += local_sum;
    pthread_mutex_unlock(&sum_mutex);

    return NULL;
}

int main(void) {
    int N;
    printf("Enter N (>= 16): ");
    if (scanf("%d", &N) != 1 || N < 16) {
        fprintf(stderr, "N must be an integer >= 16\n");
        return 1;
    }

    /* Allocate array on heap */
    int *arr = malloc(N * sizeof(int));
    if (!arr) { perror("malloc"); return 1; }

    srand((unsigned)time(NULL));
    for (int i = 0; i < N; i++)
        arr[i] = rand() % 201 - 100;   /* values in [-100, 100] */

    /* Print array */
    printf("Array (%d elements):\n", N);
    for (int i = 0; i < N; i++) {
        printf("%4d", arr[i]);
        if ((i + 1) % 16 == 0 || i == N - 1) putchar('\n');
    }

    /* Split into 4 approximately equal parts */
    pthread_t threads[NUM_THREADS];
    ThreadArgs args[NUM_THREADS];
    int base  = N / NUM_THREADS;
    int extra = N % NUM_THREADS;   /* first `extra` parts get one extra element */
    int start = 0;

    for (int t = 0; t < NUM_THREADS; t++) {
        int chunk = base + (t < extra ? 1 : 0);
        args[t].arr   = arr;
        args[t].start = start;
        args[t].end   = start + chunk;
        start += chunk;

        printf("Thread %d: indices [%d, %d)\n", t, args[t].start, args[t].end);
        pthread_create(&threads[t], NULL, worker, &args[t]);
    }

    /* Join all threads */
    for (int t = 0; t < NUM_THREADS; t++)
        pthread_join(threads[t], NULL);

    printf("\nSum (via threads) = %lld\n", sum);

    /* Verify with a sequential sum */
    long long check = 0;
    for (int i = 0; i < N; i++) check += arr[i];
    printf("Sum (sequential)  = %lld  %s\n",
           check, check == sum ? "[OK]" : "[MISMATCH!]");

    pthread_mutex_destroy(&sum_mutex);
    free(arr);
    return 0;
}
