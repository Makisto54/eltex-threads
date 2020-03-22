#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void* func(void *arg)
{
    int* ptr = (int*)arg;
    printf("%d\n", *ptr);
}

int main()
{
    pthread_t th[9];
    int a[9];
    for(int i = 0; i < 9; i++)
    {
        a[i] = i;
    }
    for(int i = 0; i < 9; i++)
    {
        pthread_create(&th[i], NULL, func, &a[i]);
    }
}
