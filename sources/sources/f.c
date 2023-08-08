//adding required libraries

#include <stdio.h> // stdio. h is a header file which has the necessary information to include the input/output related functions in our program. 
#include <stdlib.h> // header of the general purpose standard library of C programming language which includes functions involving memory allocation, process control, conversions and others. 
#include <sys/mman.h> // memory management declarations
#include <sys/types.h> // defines data types used in system source code
#include <sys/stat.h> // functions that have arguments or return values of type mode_t, so that symbolic values for that type can be used
#include <fcntl.h> // eader in the C POSIX library for the C programming language that contains constructs that refer to file control, e.g. opening a file, retrieving and changing the permissions of 
//file, locking a file for edit, etc.
#include <unistd.h> // header file that provides access to the POSIX operating system API
#include <string.h> // the predefined functions which are designed to handle strings
#include <sys/mman.h> // memory management declarations
#include <sys/shm.h> // shared memory facility
#include <semaphore.h> // header defines the sem_t type, used in performing semaphore operations
#include <time.h> // header file contains definitions of functions to get and manipulate date and time information

// Here, paths for semaphores and shared memory defined
#define SHMOBJ_PATH "/shm_AOS"
#define SHMOBJ_PATH1 "/shm_AOS1"
#define SHMOBJ_PATH2 "/shm_AOS2"
#define SHMOBJ_PATH3 "/shm_AOS3"
#define SHMOBJ_PATH4 "/shm_AOS4"
#define SEM_PATH_1 "/sem_AOS_1"
#define SEM_PATH_2 "/sem_AOS_2"
#define SEM_PATH_3 "/sem_AOS_3"
#define SEM_PATH_4 "/sem_AOS_4"
#define SEM_PATH_5 "/sem_AOS_5"

// function to generate random numbers 
int generate_random(int l,int o){


		int rand_num=(rand() %(o-l+1))+l;
	        return rand_num;
} // end of random number function

// main ()
// argc stands for argument count and argv stands for argument values. These are variables passed to the main function when it starts executing.
int main(int argc, char *argv[]) 
{
const char *chopstick[5]={"F1","F2","F3","F4","F5"}; // declared an array for chopstick
int pid,pid1,pid2,pid3,pid4,pid5; // variables for PIDs
const int SIZE=4096; // constant size 
int i,k,count=2; // required variables declared

// sem_t sem; where 5 semaphores are created for read and write which indicates the five chopsticks
sem_t * sem_id1 = sem_open(SEM_PATH_1, O_CREAT, S_IRUSR | S_IWUSR, 1);
sem_t * sem_id5 = sem_open(SEM_PATH_5, O_CREAT, S_IRUSR | S_IWUSR, 1);
sem_t * sem_id2 = sem_open(SEM_PATH_2, O_CREAT, S_IRUSR | S_IWUSR, 1);
sem_t * sem_id4 = sem_open(SEM_PATH_4, O_CREAT, S_IRUSR | S_IWUSR, 1);
sem_t * sem_id3 = sem_open(SEM_PATH_3, O_CREAT, S_IRUSR | S_IWUSR, 1);

// sem_init() function is used to initialise the unnamed semaphore referred to by sem. 
sem_init(sem_id3, 1, 1); //initialized to 1 fork3
sem_init(sem_id4, 1, 1); //initialized to 1 fork4
sem_init(sem_id2, 1, 1); //initialized to 1 fork2
sem_init(sem_id1, 1, 1); //initialized to 1 fork1
sem_init(sem_id5, 1, 1); //initialized to 1 fork5
void * ptr,*ptr1,*ptr2,*ptr3,*ptr4; //pointers for writing and reading the fork status 

// Parameters: name: The first parameter specifies the name of the shared-memory object. Processes that wish to access this shared memory must refer to the object by this name.
// The shm_open() function shall establish a connection between a shared memory object and a file descriptor. It shall create an open file description that refers to the shared memory object and a 
//file descriptor that refers to that open file description.
int shm_fd = shm_open(SHMOBJ_PATH, O_CREAT | O_RDWR, 0666);
int shm_fd1 = shm_open(SHMOBJ_PATH1, O_CREAT | O_RDWR, 0666);
int shm_fd2 = shm_open(SHMOBJ_PATH2, O_CREAT | O_RDWR, 0666);
int shm_fd3 = shm_open(SHMOBJ_PATH3, O_CREAT | O_RDWR, 0666);
int shm_fd4 = shm_open(SHMOBJ_PATH4, O_CREAT | O_RDWR, 0666);

// The ftruncate() function truncates the file indicated by the open file descriptor fildes to the indicated length. fildes must be a regular file that is open for writing. If the file size exceeds 
//length, any extra data is discarded.
ftruncate(shm_fd, SIZE);
ftruncate(shm_fd1, SIZE);
ftruncate(shm_fd2, SIZE);
ftruncate(shm_fd3, SIZE);
ftruncate(shm_fd4, SIZE);
//forking 5 process one per philosopher
pid=fork();
    
     if(pid != 0){ 
     	pid1=fork();
     if(pid1!=0){
     	pid2=fork();	
     if(pid2 != 0){
	pid3=fork();
     if(pid3 != 0){
     	pid4=fork();
     if(pid4 != 0){
     			//philosopher4
				//semaphore 3 and 4 to be used by philosopher4
     		sem_t * sem_id3 = sem_open(SEM_PATH_3,0);
			sem_t * sem_id4 = sem_open(SEM_PATH_4,0);
			//shared memory related to chopstick 3 and 4 are opened
			shm_fd3 = shm_open(SHMOBJ_PATH3, O_RDONLY,0666);
			shm_fd4 = shm_open(SHMOBJ_PATH4, O_RDONLY,0666);
			
			// mmap() is a POSIX-compliant Unix system call that maps files or devices into memory.
			//pointers used to read the chopstick status using shared memory
			ptr3 = mmap(NULL, SIZE, PROT_READ, MAP_SHARED,shm_fd3, 0); 
     		ptr4 = mmap(NULL, SIZE, PROT_READ, MAP_SHARED,shm_fd4, 0);
		while(1){
			int low=5,off=14;
    			srand(time(0));
    			int delay=generate_random(low,off);
        		printf("Philosopher4 is thinking\n"); 
        		fflush(stdout);//thinking state
        		sleep(delay);
        		printf("Philosopher4 is hungry\n");
			sem_wait(sem_id3); //takes 3rd chopstick if its available
			sem_wait(sem_id4); //takes 4th chopstick  if its available
			printf("philosopher4 takes fork %s %s\n",(char *)ptr3,(char *)ptr4); // status for taking the chopsticks
			
			printf("Philosopher 4 is eating\n"); //eatings status
			fflush(stdout);
			delay=generate_random(low,off);
			sleep(delay);
			sem_post(sem_id3); //release chopstick 3
			sem_post(sem_id4); //release chopstick 4
			printf("philosopher4 keeps fork %s %s\n",(char *)ptr3,(char *)ptr4); // status for releasing the chopsticks
			
		
		}
	
			
	
	 }else{  //philosopher5
	 	
		//semaphore 4 and 5 to be used by philosopher4
     	sem_t * sem_id4 = sem_open(SEM_PATH_4, 0);
		sem_t * sem_id5 = sem_open(SEM_PATH_5, 0);
		//shared memory related to chopstick 4 and 5 are opened
		shm_fd1 = shm_open(SHMOBJ_PATH1, O_RDONLY,0666);
		shm_fd4 = shm_open(SHMOBJ_PATH4, O_RDONLY,0666);
		//pointers used to read the chopstick status using shared memory
		ptr1 = mmap(NULL, SIZE, PROT_READ, MAP_SHARED,shm_fd1, 0);
     	ptr4 = mmap(NULL, SIZE, PROT_READ, MAP_SHARED,shm_fd4, 0);
 

	while(1){
		int low=5,off=14;
    		srand(time(0));
    		int delay=generate_random(low,off);
        	printf("Philosopher5 is thinking\n"); 
        	fflush(stdout);//thinking state
        	sleep(delay);
        	printf("Philosopher5 is hungry\n");
		sem_wait(sem_id4); //takes 4th chopstick if its available
		sem_wait(sem_id5); //takes 5th chopstic if its available
		printf("philosopher5 takes fork %s %s\n",(char *)ptr1,(char *)ptr4); // status for taking the chopsticks
		printf("Philosopher 5 is eating\n"); //eatings status
		fflush(stdout);
		delay=generate_random(low,off);
		sleep(delay);
		sem_post(sem_id4); //release chopstick 4
		sem_post(sem_id5); //release chopstick 5
		printf("philosopher5 keeps fork %s %s\n",(char *)ptr1,(char *)ptr4); // status for releasing the chopsticks
     		
		
        }
        }}else{  //philosopher3
			//semaphore 2 and 3 to be used by philosopher3
            sem_t * sem_id2 = sem_open(SEM_PATH_2, 0);
			sem_t * sem_id3 = sem_open(SEM_PATH_3,0);
			//shared memory related to chopstick 2 and 3 are opened
			shm_fd2 = shm_open(SHMOBJ_PATH2, O_RDONLY,0666);
			shm_fd3 = shm_open(SHMOBJ_PATH3, O_RDONLY,0666);
			//pointers used to read the chopstick status using shared memory
     		ptr2 = mmap(NULL, SIZE, PROT_READ, MAP_SHARED,shm_fd2, 0);
     		ptr3 = mmap(NULL, SIZE, PROT_READ, MAP_SHARED,shm_fd3, 0);
		while(1){
		int low=5,off=14;
    		srand(time(0));
    		int delay=generate_random(low,off);
        	printf("Philosopher3 is thinking\n"); 
        	fflush(stdout);//thinking state
        	sleep(delay);
        	printf("Philosopher3 is hungry\n");
		sem_wait(sem_id2); //takes 2nd chopstick if its available
		sem_wait(sem_id3); //takes 3rd chopstick if its available
		printf("philosopher3 takes fork %s %s\n",(char *)ptr2,(char *)ptr3); // status for taking the chopsticks
		printf("Philosopher 3 is eating\n"); //eatings status
		fflush(stdout);
		delay=generate_random(low,off);
		sleep(delay);
		sem_post(sem_id2); //release chopstick 2
		sem_post(sem_id3); //release chopstick 3
		printf("philosopher3 keeps fork %s %s\n",(char *)ptr2,(char *)ptr3); // status for releasing the chopsticks
		
		 

		
		
	}
            
        }
        }else{
               	//philosopher2
		//semaphore 2 and 3 to be used by philosopher2
		sem_t * sem_id1 = sem_open(SEM_PATH_1, 0);
		sem_t * sem_id2 = sem_open(SEM_PATH_2, 0);
		//shared memory related to chopstick 1 and 2 are opened
		shm_fd = shm_open(SHMOBJ_PATH, O_RDONLY,0666);
		shm_fd2 = shm_open(SHMOBJ_PATH2, O_RDONLY,0666);
		//pointers used to read the chopstick status using shared memory
     	ptr = mmap(NULL, SIZE, PROT_READ, MAP_SHARED,shm_fd, 0);
       	ptr2 = mmap(NULL, SIZE, PROT_READ, MAP_SHARED,shm_fd2, 0);
		while(1){
		int low=5,off=14;
    		srand(time(0));
    		int delay=generate_random(low,off);
       	 printf("Philosopher2 is thinking\n"); 
        	fflush(stdout);//thinking state
        	sleep(delay);
        	printf("Philosopher2 is hungry\n");
		sem_wait(sem_id1); //takes 1st chopstick if its available
		sem_wait(sem_id2); //takes 2nd chopstick if its available
		printf("philosopher2 takes fork %s %s\n",(char *)ptr,(char *)ptr2); // status for taking the chopsticks
		printf("Philosopher 2 is eating\n");
		fflush(stdout);
		delay=generate_random(low,off);
		sleep(delay); 
		sem_post(sem_id1); //release chopstick 1
		sem_post(sem_id2); //release chopstick 2
		printf("philosopher2 keeps fork %s %s\n",(char *)ptr,(char *)ptr2); // status for releasing the chopsticks

		
		
	}
       
       }} else{
        	 //philosopher1
		//semaphore 1 and 5 to be used by philosopher1
		sem_t * sem_id1 = sem_open(SEM_PATH_1, 0);
		sem_t * sem_id5 = sem_open(SEM_PATH_5, 0);
		//shared memory related to chopstick 1 and 5 are opened
		shm_fd = shm_open(SHMOBJ_PATH, O_RDONLY,0666);
		shm_fd1 = shm_open(SHMOBJ_PATH1, O_RDONLY,0666);
		//pointers used to read the chopstick status using shared memory
     	ptr = mmap(NULL, SIZE, PROT_READ, MAP_SHARED,shm_fd, 0);
     	ptr1 = mmap(NULL, SIZE, PROT_READ, MAP_SHARED,shm_fd1, 0);
        while(1){
		int low=5,off=14;
    		srand(time(0));
    		int delay=generate_random(low,off);
        	printf("Philosopher1 is thinking\n"); 
        	fflush(stdout);//thinking state
        	sleep(delay);
        	printf("Philosopher1 is hungry\n");
		sem_wait(sem_id1); //takes 1st chopstick if its available
		sem_wait(sem_id5); //takes 5th chopstick if its available
		printf("philosopher1 takes fork  %s %s\n",(char *)ptr,(char *)ptr1); // status for taking the chopsticks
		printf("Philosopher 1 is eating\n");
		fflush(stdout);
		delay=generate_random(low,off);
		sleep(delay);
		sem_post(sem_id1); //release chopstick 1
		sem_post(sem_id5); //release chopstick 5
		printf("philosopher1 keeps fork %s %s\n",(char *)ptr,(char *)ptr1); // status for releasing the chopsticks
 }}
        
       } else{ 
		   //This process holds the 5 chopsticks status in a array and using 5 different 5 shared memory
           while(1){
			//five pointers for 5 different chopsticks
			ptr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,shm_fd, 0);
			ptr1 = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,shm_fd1, 0);
			ptr2 = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,shm_fd2, 0);
			ptr3 = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,shm_fd3, 0);
			ptr4 = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,shm_fd4, 0);
			//using sprintf the required chopstick number is been written to the respectuve philosopher
			sprintf(ptr,"%s",chopstick[0]);
			sprintf(ptr1,"%s",chopstick[4]);
			sprintf(ptr2,"%s",chopstick[1]);
			sprintf(ptr3,"%s",chopstick[2]);
			sprintf(ptr4,"%s",chopstick[3]);
		}
		}
 return 0;
 } // end of main ()
 


