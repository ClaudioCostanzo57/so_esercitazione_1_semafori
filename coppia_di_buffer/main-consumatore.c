#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "buffer.h"

int main()
{

    int buf1_id;
    int buf2_id;
    buffer *buf1;
    buffer *buf2;
    int sem_id;

    key_t shm_key=ftok(".",'a');
    buf1_id =shmget(shm_key,sizeof(buffer),0664); /* TBD: Acquisizione shared memory buffer singolo */

    if (buf1_id < 0)
    {
        perror("Errore accesso SHM buf1");
        exit(1);
    }

    key_t shm2_key=ftok(".",'b');
    buf2_id =shmget(shm2_key,sizeof(buffer),0664); /* TBD: Acquisizione shared memory buffer singolo */

    if (buf2_id < 0)
    {
        perror("Errore accesso SHM buf2");
        exit(1);
    }

    key_t sem_key=ftok(".",'c');
    sem_id =semget(sem_key,2,0664); /* TBD: Acquisizione vettore semafori */

    if (sem_id < 0)
    {
        perror("Errore accesso semafori");
        exit(1);
    }

    buf1 =shmat(buf1_id,NULL,0); /* TBD: Attach shared memory */

    if (buf1 == (void *)-1)
    {
        perror("Errore attach SHM buf1");
        exit(1);
    }

    buf2 =shmat(buf2_id,NULL,0); /* TBD: Attach shared memory */

    if (buf2 == (void *)-1)
    {
        perror("Errore attach SHM buf2");
        exit(1);
    }



    for (int i = 0; i < 5; i++)
    {
        int valore = consumazione(sem_id, buf1, buf2);
    }

    exit(0);
}