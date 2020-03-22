#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t m[5] = {PTHREAD_MUTEX_INITIALIZER};
int shop[5] = {0};

struct args
{
    int val;
    int num;
};

void* shopping(void* vali)
{
    struct args *tmp = (struct args*) vali;
    int i = rand() % 5;
    if(!pthread_mutex_trylock(&m[i]))
    {
	if(tmp->num == 3)
        {
            printf("\nLoader goes to the shop %d (it's stuff - %d) and pick %d, current stuff - %d\n\n", i, shop[i], -(tmp->val), shop[i] - tmp->val);
        }
        else
        {
            printf("Buyer %d goes to the shop %d (it's stuff - %d), his before grid - %d, after grid - %d\n", tmp->num, i, shop[i], tmp->val, tmp->val - shop[i]);
        }
        if(tmp->val >= shop[i])
        {
            tmp->val -= shop[i];
            shop[i] = 0;
        }
        else
        {
            shop[i] -= tmp->val;
            tmp->val = 0;
        }
        pthread_mutex_unlock(&m[i]);
    }
}

void* buyer(void *numi)
{
    int *number = (int*)numi;
    struct args tmp;
    tmp.val = 1000;
    tmp.num = *number;
    pthread_t tid;
    while(tmp.val > 0)
    {
        pthread_create(&tid, NULL, shopping, &tmp);
        pthread_join(tid, NULL);
        sleep(2);
    }
    printf("Buyer %d has been eliminated\n", *number);
}

void* loader()
{
    int load;
    struct args tmp;
    pthread_t tid;
    while(1)
    {
        load = -rand() % 150;
        tmp.val = load;
        tmp.num = 3;
        pthread_create(&tid, NULL, shopping, &tmp);
        pthread_join(tid, NULL);
        sleep(3);
    }
}

int main()
{
    int tmp[3] = {0};
    pthread_t tid[4];
    for(int i = 0; i < 3; i++)
    {
        tmp[i] = i;
        pthread_create(&tid[i], NULL, buyer, &tmp[i]);
    }
    pthread_create(&tid[3], NULL, loader, NULL);
    for(int i = 0; i < 3; i++)
    {
        pthread_join(tid[i], NULL);
    }
    pthread_cancel(tid[3]);
    printf("End of the life\n");
    return 0;
}
