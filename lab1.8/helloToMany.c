#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

/* the thread runs in this function */
void *runner(void *param);

main(int argc, int argv[])
{
    int i, policy, num_threads, thread_counter;
    if (argc < 2) {
        printf("Please provide a number of threads!\n");
        return;
    }
    num_threads = atoi(argv[1]);
    pthread_t tid[num_threads];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    for (i = 0; i < num_threads; i++) {
        printf("I am thread 1. Created new thread (%d) in iteration %d...\n", i+2, i);
        pthread_create(&tid[i],&attr,runner,(void *)i);
        thread_counter++;
        if (i % 5 == 0)
            sleep(1);
    }
    sleep(1);
}

void *runner(void *param)
{
    long id;
    id = (long) param;
    printf("Hello from thread %d - I was created in iteration %d \n", param+2, param);
    pthread_exit(0);
}
