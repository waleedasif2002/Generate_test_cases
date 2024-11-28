#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sum = 0;

void *sum_func(void *arg) {
    int n = *(int *)arg;
    for (int i = 0; i <= n; i++) {
        sum += i;
    }
    pthread_exit(NULL);
}

int main() {
    int n;
    printf("Enter an integer: ");
    scanf("%d", &n);

    pthread_t tid;
    pthread_create(&tid, NULL, sum_func, &n);

    pthread_join(tid, NULL);
    printf("The summation of integers from 0 to %d is %d\n", n, sum);

    return 0;
}
