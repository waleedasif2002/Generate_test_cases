#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>

void *fibonacciGenerator(void *arg);
void *countEvenNumbers(void *arg);
void *countOddNumbers(void *arg);
void *calculateSum(void *arg);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s N\n", argv[0]);
        return EXIT_FAILURE;
    }
    int N = atoi(argv[1]);

    pthread_t tid[4];
    int *fib = malloc((N+1) * sizeof(int));
    fib[0] = N;
    pthread_create(&tid[0], NULL, fibonacciGenerator, fib);
    pthread_join(tid[0], NULL);
    printf("ID = %ld, Series:", tid[0]);
    for (int i = 1; i <= N; i++) {
        printf(" %d", fib[i]);
    }
    printf("\n");

    void *evenCount = 0;
    pthread_create(&tid[1], NULL, countEvenNumbers, fib);
    pthread_join(tid[1], &evenCount);
    int counteven =(int)(intptr_t)evenCount;
    
    printf("ID = %ld, Even Numbers: %d\n", tid[1], counteven);

    void* oddCount = 0;
    pthread_create(&tid[2], NULL, countOddNumbers, fib);
    pthread_join(tid[2], &oddCount);
    int countodd =(int)(intptr_t)oddCount;
    printf("ID = %ld, Odd Numbers: %d\n", tid[2], countodd);

    void* sum = 0;
    pthread_create(&tid[3], NULL, calculateSum, fib);
    pthread_join(tid[3], &sum);
    int sumptr =(int)(intptr_t)sum;
    printf("ID = %ld, Sum: %d\n", tid[3], sumptr);

    FILE *fp = fopen("sum.txt", "w");
    fprintf(fp, "%d", sumptr);
    fclose(fp);

    free(fib);

    return EXIT_SUCCESS;
}

void *fibonacciGenerator(void *arg) {
    int *fib = (int *)arg;
    fib[1] = 0;
    fib[2] = 1;
    for (int i = 3; i <= fib[0]; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    return NULL;
}

void *countEvenNumbers(void *arg) {
    int *fib = (int *)arg;
    int count = 0;
    for (int i = 1; i <= fib[0]; i++) {
        if (fib[i] % 2 == 0) {
            count++;
        }
    }
    intptr_t COUNT_PTR=(intptr_t)count;
    return (int*)COUNT_PTR;
  
}

void *countOddNumbers(void *arg) {
    int *fib = (int *)arg;
    int count = 0;
    for (int i = 1; i <= fib[0]; i++) {
        if (fib[i] % 2 != 0) {
            count++;
        }
    }
   intptr_t COUNT_PTR=(intptr_t)count;
    return (int*)COUNT_PTR;
    
    }

void *calculateSum(void *arg) {
    int *fib = (int *)arg;
    int sum = 0;
    for (int i = 1; i <= fib[0]; i++) {
        sum += fib[i];
    }
   intptr_t SUM_PTR=(intptr_t)sum;
   return (int*)SUM_PTR;
   
   
}