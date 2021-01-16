#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "buffer.h"

int main()
{

    int buf1_id;
    int buf2_id;
    buffer *buf1;
    buffer *buf2;
    int sem_id;

    key_t shm_key=ftok(".",'a');
    buf1_id =shmget(shm_key,sizeof(buffer),IPC_CREAT|0664); /* TBD: Creazione shared memory buffer singolo */

    if (buf1_id < 0)
    {
        perror("Errore creazione SHM buf1");
        exit(1);
    }

    key_t shm2_key=ftok(".",'b');
    buf2_id = shmget(shm2_key,sizeof(buffer),IPC_CREAT|0664);/* TBD: Creazione shared memory buffer singolo */

    if (buf2_id < 0)
    {
        perror("Errore creazione SHM buf2");
        exit(1);
    }

    key_t sem_key=ftok(".",'c');
    sem_id =semget(sem_key,2,IPC_CREAT|0664);/* TBD: Creazione vettore semafori */

    if (sem_id < 0)
    {
        perror("Errore creazione semafori");
        exit(1);
    }

    buf1 =shmat(buf1_id,NULL,0); /* TBD: Attach shared memory buffer singolo */

    if (buf1 == (void *)-1)
    {
        perror("Errore attach SHM buf1");
        exit(1);
    }

    buf2 = shmat(buf2_id,NULL,0);/* TBD: Attach shared memory buffer singolo */

    if (buf2 == (void *)-1)
    {
        perror("Errore attach SHM buf2");
        exit(1);
    }

    /* TBD: inizializzazione stato buf1 e buf2 */
    buf1->stato=LIBERO;
    buf2->stato=LIBERO;

    /* TBD: inizializzazione semafori */
    semctl(sem_id,SPAZIO_DISP,SETVAL,2);//due  buffer
    semctl(sem_id,MESSAGGIO_DISP,SETVAL,0);


    /* TBD: Creazione processo produttore */
    pid_t pid=fork();
    if(pid==0){
        execl("./main-produttore","main-produttore",NULL);
        exit(0);
    }
    else if(pid<0){
        perror("errore fork produttore");
        exit(1);
    }
    
    /* TBD: Creazione processo consumatore */
    pid=fork();
    if(pid==0){
        execl("./main-consumatore","main-consumatore",NULL);
        exit(0);
    }
    else if(pid<0){
        perror("errore fork consumatore");
        exit(1);
    }


    for (int i = 0; i < 2; i++)
    {
        wait(NULL);
    }

    shmctl(buf1_id, IPC_RMID, NULL);
    shmctl(buf2_id, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);
}