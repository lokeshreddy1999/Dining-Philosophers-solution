# Dining-Philosophers-solution
Dining-Philosophers-solution using semaphore 

Problem Statement:The Dining Philosopher Problem states that  philosophers seated around a circular table with one chopstick between each pair of philosophers. There is one chopstick between each philosopher. A philosopher may eat if he can pickup the two chopsticks adjacent to him. One chopstick may be picked up by any one of its adjacent followers but not both.

Before let me expain what i have done I used threads as the main agents to do the the required functions(producing and consuming) I selected threads so that my program will run for many threads at the same time(i.e.PARALLEL PROCESS) Then I implmented semphores on my OWN semaphore (in two ways)

First way:which uses only while loop but disadvantage is Busy Waiting(wastes cpu cycles)

Secondway Way:which uses queue datastucture to store block() threads

see the files semphores library files to get full code. Here i implemented 3 main semaphores functions

1)sem_init_(for inilization of any semapores)

2)sem_wait (act as w(s) signal)

3)sem_post (act as v(s) signal)

Here i implemented the same function name and syntax ( such as type of parameteres and no_of para) as there in inbuilt. i implemented in that way because i want to test with inbuilt semaphore code(i.e. i will just import my semaphore library instead to see whether is it giving simillar seqeuence of threads with the solution obtained by inbuilt semapore library)
this is the good way for testingtypedef struct

struct for first way 

{ 

atomic_int s;// atomic varible to protect through control section

pthread_mutex_t lock1; // lock for sem wait

}

struct for the second way 
{ 

atomic_int s; // semaphore varible 

queue Q; // queue for storing blocked threads 

pthread_mutex_t lock1; pthread_mutex_t lock2;


pthread_mutex_t excusion_between_signal_ans_wait ; 
}

Each philosopher is represented by the following pseudocode:

process P[i]
 while true do
   {  
   
   THINK;
     
      PICKUP(CHOPSTICK[i], CHOPSTICK[i+1 mod 5]);
      
      EAT;
      
      PUTDOWN(CHOPSTICK[i], CHOPSTICK[i+1 mod 5])
   }
   
   
There are three states of philosopher : THINKING, HUNGRY and EATING. Here there are two semaphores : Mutex and a semaphore array for the philosophers. Mutex is used such that no two philosophers may access the pickup or putdown at the same time. The array is used to control the behavior of each philosopher.    
   


