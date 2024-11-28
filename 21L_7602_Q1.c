#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void sortArray(int arr[], int size)
{
    int i, j, min_idx;

    for (i = 0; i < size - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
int main(int argc, char *argv[])
{
    int arr[10];
    pid_t pid;
    int i;

    for (i = 0; i < 10; i++)
    {
        arr[i] = atoi(argv[i + 1]);
    }
    pid = fork();

    if (pid == -1)
    {
        printf("Error: Failed to fork a child process\n");
        return 1;
    }
    else if (pid == 0)
    {
        sortArray(arr, 10);
        printf("Sorted array: ");
        printArray(arr, 10);
        printf("Child process ID: %d\n", getpid());
    }
    else
    {
        wait(NULL);
    }

    return 0;
}
