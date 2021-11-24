#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

pthread_mutex_t mutex;
pthread_barrier_t barrier;

int SharedVariable = 0;

void *SimpleThread(void * which)
{
  int num, val;

	for(num = 0; num < 20; num++){
		#ifdef PTHREAD_SYNC
		if(random() > RAND_MAX / 2) usleep(10);
		 #endif

		// Lock the mutex
    pthread_mutex_lock(&mutex);

		val = SharedVariable;
		printf("***thread %ld sees value %d\n", (long)which, val);
		SharedVariable = val + 1;

		// Unlock the mutex
  	pthread_mutex_unlock(&mutex); 
	}
	
	pthread_barrier_wait(&barrier);

	val = SharedVariable;
	printf("Thread %ld sees final value %d\n", (long)which, val);
	
	pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
	if (argc != 2){
		printf("ERROR; enter a number as argument indicating the desired number of threads\n");
		return -1;
	}

	int NUM_THREADS = atoi(argv[1]);
	if (NUM_THREADS < 1 || NUM_THREADS > 5){
		printf("ERROR; the argument entered must be an integer between 1 and 5 inclusive\n");
		return -1;
	}

	// Initialize the mutex
  if(pthread_mutex_init(&mutex, NULL))
  {
    printf("Unable to initialize a mutex\n");
    return -1;
  }

	// Initialize the barrier
  if(pthread_barrier_init(&barrier, NULL, NUM_THREADS))
  {
    printf("Unable to initialize a barrier\n");
    return -1;
  }

  pthread_t threads[NUM_THREADS];
  int rc;
  
	for(long t=0; t<NUM_THREADS; t++){
    printf("In main: creating thread %ld\n", t);
    rc = pthread_create(&threads[t], NULL, SimpleThread, (void *)t);
    if (rc){
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      return -1;
    }
  }

	for(long t=0; t<NUM_THREADS; t++) {
    rc = pthread_join(threads[t], NULL);
    if (rc) {
    	printf("ERROR; return code from pthread_join() is %d\n", rc);
      return -1;
    }
  }

	// Clean up the mutex
  pthread_mutex_destroy(&mutex);

	//Clean up the barrier
	pthread_barrier_destroy(&barrier);

	/* Last thing that main() should do */
  pthread_exit(NULL);
}