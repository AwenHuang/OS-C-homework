// external process  
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int const  CentralMailBox = 48; // central mailbox number

struct{
		long priority;
		int temp;
		int pid;
		int stable;
}msgp,exmsgp;

int main(int argc, char *argv[]){

		int stat,status;
		int unstable = 1;
		int id = atoi(argv[2]); // get external process id
		


		// creat central mailbox
		int cmsqid = msgget(CentralMailBox , 0600 | IPC_CREAT);
		
		// creat external mailbox
		int msqid = msgget((CentralMailBox + id), 0600 | IPC_CREAT);



		exmsgp.priority = 2; // according to the textbook recommend
		exmsgp.pid = id; 
		exmsgp.temp = atoi(argv[1]); 
		exmsgp.stable = 0 ; // external box set to 0

	
		// assume the external process not equal at begining
		while(msgp.stable != 1){
				//send message from external process to central
				stat = msgsnd(cmsqid, &exmsgp, sizeof(exmsgp)-sizeof(long), 0);

				//receive message from central process
				stat = msgrcv(msqid, &msgp, sizeof(msgp)-sizeof(long), 2, 0);

				//stable
				if(msgp.stable == 1){
						unstable = 0;
						printf("\nProcess %d ,Temperature:%d\n",exmsgp.pid, exmsgp.temp);
				}
				else
						exmsgp.temp = (exmsgp.temp*3 + msgp.temp*2)/5;
		}
		//remove the external mailbox
		status = msgctl(msqid, IPC_RMID, 0);
		return 0;
}


				
				
