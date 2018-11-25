#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>    
#include <sys/stat.h>
#include <pthread.h>
#include <sys/sem.h>
#include <stdlib.h>
#include "display.h"

int predicate = 0;
int predicate1 = 1;


pthread_cond_t      condA  = PTHREAD_COND_INITIALIZER;
pthread_cond_t      condB  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

 
void *thrd1(void *arg){
int i;

for (i=0;i<10;i++){


   pthread_mutex_lock(&mutex);
        while (predicate == 1)
            pthread_cond_wait(&condA, &mutex);
	    
       pthread_mutex_unlock(&mutex);

pthread_mutex_lock(&mutex);
display("ab");
pthread_mutex_unlock(&mutex);
predicate=1;
 pthread_mutex_lock(&mutex);
        predicate1=0;
        pthread_cond_signal(&condB);
        pthread_mutex_unlock(&mutex);



}

pthread_exit(NULL);
}



void *thrd2(void *arg){
int i;
for (i=0;i<10;i++){


 pthread_mutex_lock(&mutex);
        while (predicate1 == 1)
            pthread_cond_wait(&condB, &mutex);
	
        pthread_mutex_unlock(&mutex);


pthread_mutex_lock(&mutex);

display("cd\n");

pthread_mutex_unlock(&mutex);
predicate1=1;

 pthread_mutex_lock(&mutex);
        predicate=0;
        pthread_cond_signal(&condA);
        pthread_mutex_unlock(&mutex);


}

pthread_exit(NULL);
}


int main()
{
int i;

pthread_t mth1;
pthread_create(&mth1,NULL,thrd1,NULL);
pthread_t mth2;

pthread_create(&mth2,NULL,thrd2,NULL);

pthread_join(mth1,NULL);
pthread_join(mth2,NULL);

pthread_mutex_destroy(&mutex);
return 0;
}

