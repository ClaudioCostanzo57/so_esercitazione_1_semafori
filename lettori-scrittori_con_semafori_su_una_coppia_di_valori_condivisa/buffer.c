#include <unistd.h>
#include <stdio.h>

#include "buffer.h"

void leggi_buffer(buffer * b, int sem_id, int *val_1, int *val_2) {

    printf("[%d] Inizio lettura\n", getpid());

    /* TBD: Inizio lettura */
    Wait_Sem(sem_id,MUTEXL);
    b->num_lettori++;
    if(b->num_lettori==1){
        Wait_Sem(sem_id,SYNCH);
    }
    Signal_Sem(sem_id,MUTEXL);
    


    printf("[%d] Lettura buffer: val1=%d, val2=%d\n", getpid(), b->val_1, b->val_2);

    sleep(1);

    *val_1 = b->val_1;
    *val_2 = b->val_2;


    printf("[%d] Fine lettura\n", getpid());

    /* TBD: Fine lettura */
    Wait_Sem(sem_id,MUTEXL);
    b->num_lettori--;
    if(b->num_lettori==0){
    Signal_Sem(sem_id,SYNCH);
    }
    Signal_Sem(sem_id,MUTEXL);
}

void scrivi_buffer(buffer *b, int sem_id, int val_1, int val_2) {

    printf("[%d] Inizio scrittura\n", getpid());

    /* TBD: Inizio scrittura */
    Wait_Sem(sem_id,SYNCH);
    

    printf("[%d] Scrittura buffer: val1=%d, val2=%d\n", getpid(), val_1, val_2);

    sleep(2);

    b->val_1 = val_1;
    b->val_2 = val_2;


    printf("[%d] Fine scrittura\n", getpid());

    /* TBD: Fine scrittura */
    Signal_Sem(sem_id,SYNCH);
}
