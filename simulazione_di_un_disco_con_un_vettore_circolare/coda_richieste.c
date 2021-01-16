#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>

#include "coda_richieste.h"

coda_richieste *inizializza_coda()
{
    int shm_id;
    int sem_id;
    coda_richieste *c;

    key_t sem_key=ftok(".",'a');
    sem_id =semget(sem_key,2,IPC_CREAT|0664); /* TBD: Creazione vettore semafori */

    if (sem_id < 0)
    {
        perror("Errore creazione semafori");
        exit(1);
    }

    /* TBD: Inizializzazione vettore semafori */
    semctl(sem_id,SPAZIO_DISP,SETVAL,DIM);
    semctl(sem_id,MSG_DISP,SETVAL,0);


    key_t shm_key=ftok(".",'b');
    shm_id =shmget(shm_key,sizeof(coda_richieste),IPC_CREAT|0664); /* TBD: Creazione shared memory */

    if (shm_id < 0)
    {
        perror("Errore creazione SHM coda richieste");
        exit(1);
    }

    c =shmat(shm_id,NULL,0); /* TBD: Attach shared memory */

    if (c == (void *)-1)
    {
        perror("Errore attach SHM");
        exit(1);
    }

    
    /* TBD: Inizializzazione shared memory */
    c->coda=0;
    c->testa=0;
    c->shm_id=shm_id;
    c->sem_id=sem_id;

}

void preleva_richiesta(coda_richieste *c, richiesta *r)
{

    /* TBD: Inizio consumazione */
    Wait_Sem(c->sem_id,MSG_DISP);


    printf("[%d] Consumazione in coda: %d\n", getpid(), c->coda);

    r->posizione = c->vettore[c->coda].posizione/* TBD */;
    r->processo = c->vettore[c->coda].processo/* TBD */;
    c->coda=(++c->coda) % DIM;

    
    /* TBD: Fine consumazione */
    Signal_Sem(c->sem_id,SPAZIO_DISP);
}

void inserisci_richiesta(coda_richieste *c, richiesta *r)
{
    /* TBD: Inizio produzione */
    Wait_Sem(c->sem_id,SPAZIO_DISP);
    

    printf("[%d] Produzione in testa: %d\n", getpid(), c->testa);

    /* TBD */ c->vettore[c->testa].posizione= r->posizione;
    /* TBD */ c->vettore[c->testa].processo= r->processo;
    c->testa=(++c->testa) % DIM;


    /* TBD: Fine produzione */
    
    Signal_Sem(c->sem_id,MSG_DISP);
}

void *rimuovi_coda(coda_richieste *c)
{
    semctl(c->sem_id, 0, IPC_RMID);
    shmctl(c->shm_id, IPC_RMID, NULL);
}