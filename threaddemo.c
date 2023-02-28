/* threaddemo.c */
/* Thread demonstration program. Note that this program uses a shared variable
   in an unsafe manner (eg mutual exclusion is not attempted!) */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int x = 50;   /* a global (shared) variable */
int quantidadeDeChamadas = 0;
const clock_t MAXDELAY = 2000000;

void delay(clock_t ticks) { /* a "busy" delay */
  clock_t start = clock();
  do
    ; while (clock() < start + ticks);
}

void * adjustX(void *n)
{  int i = (int)n;
   
   printf("adjustment = %2i; x = %i\n", i, x);
   quantidadeDeChamadas += 1;
   x += i*quantidadeDeChamadas;
   delay(rand()%MAXDELAY);
   
   return(n);
}

main()
{  int a;
   srand(time(NULL));
   pthread_t  up_thread, dn_thread;

   pthread_attr_t *attr;  /* thread attribute variable */
   attr=0;  

   printf("creating threads:\n");
   
   while(1){
	   pthread_create(&up_thread,attr, adjustX, (void *)1);
	   pthread_join(up_thread, NULL);
	   pthread_create(&dn_thread,attr, adjustX, (void *)-1);
	   pthread_join(dn_thread, NULL);
	   pthread_cancel(up_thread);
	   pthread_cancel(dn_thread);
   }
 
}
