#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>    
#include <stdlib.h>
#include <sys/stat.h>  
#include "display.h"
#include <sys/wait.h> 




int main()
{
int i;
sem_t *mutex;

mutex=sem_open("mysem", O_CREAT | O_EXCL, 0777,1);
sem_unlink("mysem");

if (fork())
{
for (i=0;i<10;i++){
sem_wait(mutex);
display("Hello world\n");
sem_post(mutex);
}
sem_destroy (mutex);
wait(NULL);

exit(0);
}
else
{
for (i=0;i<10;i++){
sem_wait(mutex);
display("Kalimera kosme\n");
sem_post(mutex);
}
sem_destroy (mutex);
exit(0);
}

}
