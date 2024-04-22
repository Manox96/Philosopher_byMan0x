

#include <libc.h>
#include <pthread.h>
#include <stdio.h>

int mail = 0;
pthread_mutex_t lock;

void* routine()
{
    for (int i = 0;i < 100000;i++)
    {
        pthread_mutex_lock(&lock);
        mail++;
        pthread_mutex_unlock(&lock);
    }
    return 0;
}

int main(int ac, char **av)
{
    pthread_t t1,t2;
    pthread_mutex_init(&lock,NULL);
    pthread_create(&t1,NULL,&routine,NULL);
    pthread_create(&t2,NULL,&routine,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    printf("--> %d",mail);

}