#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <signal.h>

#define frand() ((double)rand()/(RAND_MAX))
#define rand_times 3500

pthread_t tid[1]; // creare child thread
int global_count;
int loop;

void calculate();

void* doSomeThing(void *arg){
		pthread_t id = pthread_self();
		if(pthread_equal(id,tid[0])){
				printf("\n\033[1;33mFirst thread processing...\033[m\n");
				
				int i,s;
				int count=0;
				for(i=0; i<rand_times; i++){
				
						double x,y,dist;
						int radius = 1; 

						x = frand(); // 0.0 <= frand() < 1
						y = frand();
					
						dist = pow(x-0,2) + pow(y-0,2);
						
						if(dist <= radius)
								count++;
						
						global_count = count;
						
				}

				printf("\n\033[1;33mFirst thread done\033[m\n");
				global_count = count; // update global_count
		}

		return NULL;
}

void calculate(){
		double pi;
		pi = 4* (double)global_count/(double)(rand_times);
		printf("\nglobal count=%d , rand_times=%d\n",global_count,rand_times);
		printf("\n\033[1;41mpi is %2.6f\033[m\n",pi);

		exit(1);
}

int main(void){
		int error;
		int i=0,j=0;

		error = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);

		if(error != 0)
				printf("can't create thread\n");
		else
				printf("Thread create sucessfully\n");
		
		pthread_join(tid[j], NULL);

		calculate();
				
		
		return 0;
}


		

