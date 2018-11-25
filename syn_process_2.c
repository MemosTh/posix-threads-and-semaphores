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






int main()
{
int i;

sem_t *mutex;
sem_t *mutex1;

mutex=sem_open("mysem", O_CREAT | O_EXCL, 0644,1);
mutex1=sem_open("mysem1", O_CREAT | O_EXCL, 0644,0);
sem_unlink("mysem");
sem_unlink("mysem1");

if (fork())
{

for (i=0;i<10;i++){

sem_wait(mutex);
display("ab");
sem_post(mutex1);

}
sem_destroy (mutex);
wait(NULL);

exit(0);
}
else
{
for (i=0;i<10;i++){
sem_wait(mutex1);
display("cd\n");
sem_post(mutex);



}

sem_destroy (mutex);

exit(0);
}

}

