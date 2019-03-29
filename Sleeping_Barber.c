#include "semaphore_lib_through_while_loop.h"

#define NUMB_CUSTOMERS 20
#define NUMB_FREESEATS 6



sem_t Customers;
sem_t Barber;
sem_t Seats;
sem_t print;
int FreeSeats=NUMB_FREESEATS;
void *barber(void *thread_n)
{
   int n1=*(int *)thread_n;
   while(1) { 
            /* waits for a customer (sleeps). */
            sem_wait(&Customers); 
  
            /* mutex to protect the number of available seats.*/
            sem_wait(&Seats); 
  
            /* a chair gets free.*/
            FreeSeats++; 

            sleep(10);
            /* bring customer for haircut.*/
            sem_post(&Barber); 
             
            /* release the mutex on the chair.*/
            sem_post(&Seats); 
            /* barber is cutting hair.*/
      }
}

void *customer(void *thread_n)
{
       int n1=*(int *)thread_n;
          
        printf("%dstarted\n", n1);

          sem_wait(&Seats); 
          if(FreeSeats > 0) 
          {

                
                  /* sitting sem_wait.*/
                FreeSeats--; 
                
                 printf("%dseated and no of persons seated is %d\n", n1,NUMB_FREESEATS-FreeSeats);  
                   /* notify the barber. */
                 sem_post(&Customers); 
                   
                  /* release the lock */
                 sem_post(&Seats); 
                   
                  /* wait in the waiting room if barber is busy. */
                 sem_wait(&print); 
                 printf("%dhaircut and no of persons seated is  %d\n", n1,NUMB_FREESEATS-FreeSeats);
                 sem_wait(&Barber);
                 printf("%dcompleted\n", n1);
                 sem_post(&print); 
                  // customer is having hair cut 
            } 

            else 
            { 
                  /* release the lock */
               printf("%dwentout\n", n1);     
                  sem_post(&Seats); 
                  // customer leaves 
            }
      
}

int main(int argc, int **argv) 
{
   sem_init(&Customers,0,0);
   sem_init(&Barber,0,0);
   sem_init(&Seats,0,1);
   sem_init(&print,0,1);
   pthread_t thread_customers[NUMB_CUSTOMERS];
   pthread_t thread_barber[1];
   int thread_numb[NUMB_CUSTOMERS];
   int x=1;
   pthread_create(thread_barber+0,NULL, barber,&x); 

   for (int i = 0; i < NUMB_CUSTOMERS;i++ ) 
   {
      thread_numb[i] = i;
      pthread_create(thread_customers + i,NULL, customer,thread_numb + i);
        
   }

   for (int i = 0; i < NUMB_CUSTOMERS; i++)
   {
      pthread_join(thread_customers[i], NULL);
   }

   
 
   


}





