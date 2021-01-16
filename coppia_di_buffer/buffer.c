#include "buffer.h"

#include <unistd.h>
#include <stdio.h>

void produzione(int sem_id, buffer *buf1, buffer *buf2, int valore)
{

    /* TBD: Inizio produzione */
    Wait_Sem(sem_id,SPAZIO_DISP);
    if (buf1->stato == LIBERO/* TBD */)
    {
        /* TBD: Inizio produzione */
        
        


        printf("[%d] In produzione su buf1...\n", getpid());

        sleep(1);
		buf1->stato=INUSO;
        buf1->valore = valore;

        /* TBD: Fine produzione */
        buf1->stato=OCCUPATO;
        

        printf("[%d] Prodotto il valore %d su buf1\n", getpid(), valore);
    }
    else
    {

        /* se il programma è arrivato a questo punto, vi
         * deve essere almeno uno spazio disponibile, e 
         * quello spazio non è in "buf1", per cui "buf2"
         * è necessariamente libero.
         */

        /* TBD: Inizio produzione */
        
        

        printf("[%d] In produzione su buf2...\n", getpid());

        sleep(1);
		
		buf2->stato=INUSO;
        buf2->valore = valore;

        /* TBD: Fine produzione */
        buf2->stato=OCCUPATO;
        

        printf("[%d] Prodotto il valore %d su buf2\n", getpid(), valore);

    }

    /* TBD: Fine produzione */
    Signal_Sem(sem_id,MESSAGGIO_DISP);
}

int consumazione(int sem_id, buffer *buf1, buffer *buf2)
{

    int valore;

    /* TBD: Inizio consumazione */
    Wait_Sem(sem_id,MESSAGGIO_DISP);

    if (buf1->stato ==OCCUPATO /* TBD */)
    {
        /* TBD: Inizio consumazione */
        
        

        printf("[%d] In consumazione su buf1...\n", getpid());

        sleep(2);
		
		buf1->stato=INUSO;
        valore = buf1->valore;

        /* TBD: Fine consumazione */
        buf1->stato=LIBERO;
        

        printf("[%d] Consumato il valore %d su buf1\n", getpid(), valore);

    }
    else
    {
        /* se il programma è arrivato a questo punto, vi
         * deve essere almeno un messaggio disponibile, e 
         * quel messaggio non è in "buf1", per cui "buf2"
         * è necessariamente occupato.
         */

        /* TBD: Inizio consumazione */
       

        printf("[%d] In consumazione su buf2...\n", getpid());

        sleep(2);
		
		buf1->stato=INUSO;
        valore = buf2->valore;

        /* TBD: Fine consumazione */
        buf2->stato=LIBERO;
        

        printf("[%d] Consumato il valore %d su buf2\n", getpid(), valore);

    }

    /* TBD: Fine consumazione */
    Signal_Sem(sem_id,SPAZIO_DISP);

    return valore;
}
