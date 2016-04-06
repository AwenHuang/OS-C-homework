#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <signal.h>

#define frand() ((double)rand()/(RAND_MAX))
#define rand_times 3500

pthread_t tid[6]; // creare child thread

int global_count = 0;
int counter;
pthread_mutex_t lock; // set lock


void calculate(){

		double pi;
		pi = 4* (double)global_count/(double)rand_times;
		printf("\nglobal count = %d , rand times = %d\n",global_count,rand_times);
		printf("\n\033[1;41mpi is %2.6f\033[m\n",pi);
		exit(1);
}


void* doSomeThing(void *arg){
			
			pthread_mutex_lock(&lock);

			int i,s;
			int count = 0;
			counter = counter + 1;
					
			printf("\n\033[1;34mThread %d starting ...\033[m\n",counter);
		

			for(i=0;i<rand_times;i++){
				
						double x,y,dist;
						int radius = 1; 

						x = frand(); // 0.0 <= frand() < 1
						y = frand();
						dist = pow(x-0,2) + pow(y-0,2);

						if(dist <= radius)
								count++;
			}
			

			printf("\n\033[1;32mThread %d count = %d\033[m\n",counter,count);

			global_count = count; // update new count
		
			printf("\n\033[1;34mThread %d finished\033[m\n",counter);

			pthread_mutex_unlock(&lock);

		return NULL;
}


int main(void){
		
		int error;
		int i=0,j=0;
		

		if(pthread_mutex_init(&lock, NULL) != 0){
				printf("\nmutex init failed\n");
				return 1;
		}
		while(i < 6){
				error = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
		
				if(error != 0)
						printf("can't create thread\n");
				else
						printf("\nThread %d create sucessfully\n",i+1);

				i++;
		}
			
		while(j < 6){
				pthread_join(tid[j], NULL);
				j++;
		}
		
		pthread_mutex_destroy(&lock);
		
		calculate();		
		
		return 0;
}


		

