#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>

#include "buffer.h"

int main() {

    printf("[%d] Creazione shared memory\n", getpid());

    key_t chiave_shm =ftok(".",'a'); /* TBD: Definire una chiave */

    int shm_id =shmget(chiave_shm,sizeof(buffer),IPC_CREAT|0664); /* TBD: Allocare una memoria condivisa */

    if(shm_id < 0) {
        perror("Errore creazione shared memory");
        exit(1);
    }

    buffer * b =shmat(shm_id,NULL,0);/* TBD: Ottenere un puntatore alla memoria condivisa */

    if(b == (void*)-1) {
        perror("Errore attach shared memory");
        exit(1);
    }


    /* TBD: Inizializzare la memoria condivisa */
    b->num_lettori=0;
    b->val_1=0;
    b->val_2=0;



    printf("[%d] Creazione semafori\n", getpid());

    key_t sem_chiave =ftok(".",'b'); /* TBD: Definire una chiave */

    int sem_id =semget(sem_chiave,2,IPC_CREAT|0664); /* TBD: Allocare un vettore di semafori */

    if(sem_id < 0) {
        perror("Errore creazione semafori");
        exit(1);
    }


    /* TBD: Inizializzare il vettore di semafori */
    semctl(sem_id,MUTEXL,SETVAL,1);
    semctl(sem_id,SYNCH,SETVAL,1);





    printf("[%d] Creazione processo scrittore\n", getpid());

    /* TBD: Creare un processo scrittore, ed eseguire "main_scrittore" */

    pid_t pid=fork();
    if(pid==0){
        execl("./main_scrittore","main_scrittore",NULL);
        exit(0);
    }
    else if(pid<0){
            perror("errore fork scrittore");
            exit(1);
        }


    for(int i=0; i<2; i++) {

        printf("[%d] Creazione processo lettore\n", getpid());

        /* TBD: Creare un processo lettore, ed eseguire "main_lettori" */
        pid=fork();
        if(pid==0){
            execl("./main_lettori","main_lettori",NULL);
            exit(0);
        }
        else if(pid<0){
            perror("errore fork lettori");
            exit(1);
        }
    }




    printf("[%d] In attesa di terminazione dei processi\n", getpid());

    /* TBD: Attendere la terminazione dei processi figli */
    for(int i=0;i<3;i++){
        wait(NULL);
    }



    printf("[%d] Deallocazione risorse\n", getpid());

    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);
}
