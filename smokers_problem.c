#include <stdbool.h>
#include "semaphore_lib_without_busywaiting.h" 

#define NO_OF_SMOKERS 3

//personA tobacco
//personB paper
//personC match


sem_t agentsem;
sem_t Tobacco; 
sem_t Paper;
sem_t Match;

bool isTobacco=false,isPaper=false,isMatch=false;
sem_t Tobaccosem;
sem_t Papersem;
sem_t Matchsem;  



sem_t mutex;

bool done[NO_OF_SMOKERS];  

void make()
{
  int val=rand()%3;
  printf("val %d\n",val);
  sleep(val);
}





void *agent()
{

     
    while(1)
    {
      
      sem_wait(&agentsem);  
        
        sem_wait(&mutex);

      int select=rand()%3;
        while(done[select])
        {
          int k1=NO_OF_SMOKERS;
           select=(select+1)%k1;
        } 
   
    if(select!=0)
    {
            sem_post(&Tobacco);
    }
    if(select!=1)
    {
         sem_post(&Paper);  
    }
    if(select!=2)
    {
       sem_post(&Match);
      }
      sem_post(&mutex);
    }    
      
   
}

void *pusherA()
{
  while(1)
  {

     sem_wait(&Tobacco);
   sem_wait(&mutex);
    if(isPaper)
    {
      isPaper=false;
      printf("invoked personC");
        sem_post(&Matchsem);
      }
    else if(isMatch)
    {
       isMatch=false;
       printf("invoked personB");
         sem_post(&Papersem);
    }
    else
    {
        isTobacco=true;
    }

    sem_post(&mutex);

    }
}

void *pusherB()
{
    while(1)
  {

     sem_wait(&Paper);
   sem_wait(&mutex);
    if(isMatch)
    {
      isMatch=true; 
      printf("invoked personA");
      sem_post(&Tobaccosem); 
    }
    else if(isTobacco)
    {
       isTobacco=false;
       printf("invoked personC");
       sem_post(&Matchsem);
    }
    else
    {
        isPaper=true;
    }
     
     sem_post(&mutex);
    
    }

}

void  *pusherC()
{

     while(1)
  {


   sem_wait(&Match);
   sem_wait(&mutex);
    if(isPaper)
    {
      isPaper=true; 
      printf("invoked personA");
      sem_post(&Tobaccosem); 
    }
    else if(isTobacco)
    {
       isTobacco=false;
       printf("invoked personB");
       sem_post(&Papersem);
    }
    else
    {
        isMatch=true;
    }
     
     sem_post(&mutex);
        
    }     
}


void *tobacco()
{

  sem_wait(&Tobaccosem);
  printf("personA got chance\n");
  make();
  done[0]=true;
  printf("personA done with this\n");
  sem_post(&agentsem);   
}
void *paper()
{
  sem_wait(&Papersem);
  printf("personB got chance\n");
  make();
  done[1]=true;
  printf("personB done with this\n");
  sem_post(&agentsem);   
}

void *match()
{
  sem_wait(&Matchsem);
  printf("personC got chance\n");
  make();
    done[2]=true;
    printf("personC done with this\n");
  sem_post(&agentsem);   
}


int main(int argc, int **argv) 
{
    
    for (int i = 0; i < NO_OF_SMOKERS; ++i)
    {
      done[i]=false;
    }
   

    

     sem_init(&agentsem,0,1);
     sem_init(&Papersem,0,0);
     sem_init(&Matchsem,0,0);
     sem_init(&Tobaccosem,0,0);
     sem_init(&Paper,0,0);
     sem_init(&Match,0,0);
     sem_init(&Tobacco,0,0);

     sem_init(&mutex,0,1);


     pthread_t thread[NO_OF_SMOKERS];
     pthread_t pushers[NO_OF_SMOKERS];
     
     pthread_create(thread + 0,NULL,*tobacco,NULL);
     pthread_create(pushers + 0,NULL,*pusherA,NULL);
     pthread_create(thread + 1,NULL,*match,NULL);
     pthread_create(pushers + 1,NULL,*pusherB,NULL);
     pthread_create(thread + 2,NULL,*paper,NULL);  
     pthread_create(pushers + 2,NULL,*pusherC,NULL);
     
     pthread_t Agent[1];
     pthread_create(Agent+0,NULL,*agent,NULL);   

     for (int i = 0; i < NO_OF_SMOKERS; ++i)
      {
         pthread_join(thread[i],NULL);
      }   
          
 

   
 
    return 0;
} 