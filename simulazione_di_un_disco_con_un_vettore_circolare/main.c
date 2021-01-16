#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "coda_richieste.h"

#define DIM_DISCO 20

void Schedulatore(coda_richieste *c)
{

    int disco[DIM_DISCO];
    int posizione_corrente = 0;

    richiesta r;
    for (int i = 0; i < 25; i++)
    {

        /* TBD: Effettuare la consumazione */
        preleva_richiesta(c,&r);

        printf("[%d] Prelevo richiesta: posizione=%d, processo=%d\n", getpid(), r.posizione, r.processo);

        int attesa = abs(posizione_corrente - r.posizione);

        printf("[%d] Attesa Schedulatore... (%d secondi)\n", getpid(), attesa);

        sleep(attesa);

        disco[r.posizione] = r.processo;

        posizione_corrente = r.posizione;
    }
}

void Utente(coda_richieste *c)
{
    richiesta r;

    for (int i = 0; i < 5; i++)
    {

        printf("[%d] Richiesta Utente: posizione=%d, processo=%d\n", getpid(), r.posizione, r.processo);

        /* TBD: Effettuare la produzione */
        inserisci_richiesta(c,&r);
    }
}

int main()
{
    coda_richieste * c;

    /* TBD: Allocazione coda richieste, chiamando "inizializza_coda()" */
    c=inizializza_coda();


    /* TBD: Creazione del processo Schedulatore */
    pid_t pid=fork();
    if(pid==0){
        Schedulatore(c);
        exit(0);

    }


    /* TBD: Creazione dei processi Utente */
    for(int i=0;i<5;i++){
        pid=fork();
        if(pid==0){
            Utente(c);
            exit(0);
        }
    }
    


    /* TBD: Attesa terminazione processi figli */
    for (int  i = 0; i < 6; i++)
    {
        wait(NULL) ;
    }

    printf("fine \n");
    
}