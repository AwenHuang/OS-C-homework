// central process
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>

int const  CentralMailBox = 48; // central mailbox number
int const  ProcessNum = 4;  // external process amount

struct{
		long priority;
		int temp;
		int pid;
		int stable;
}msgp,exmsgp;

int main(int argc,char *argv[])
{
		int i,stat,status;
		int msqid[ProcessNum]; // external process id;
		int stability = 0;
		
		
		msgp.priority = 2; // according to textbook's accommand
		msgp.temp = atoi(argv[1]);
		msgp.pid = 0; // central mailbox  pid = 0
		msgp.stable = 0; // central mailbox stable = 0

	
		// creat central mailbox
		int cmsqid = msgget(CentralMailBox, 0600 | IPC_CREAT);
		

		// creat the 4 external mailbox
		for(i=1; i<=ProcessNum; i++)
				msqid[i-1] = msgget((CentralMailBox + i) , 0600 | IPC_CREAT);

		while(msgp.stable != 1) // assume each temperature not equal at begining
		{
				int temp_sum = 0,count = 0;

				//recieve new message from the central mailbox 4 times
				for(i=0; i<ProcessNum; i++){
						stat = msgrcv( cmsqid, &exmsgp, sizeof(exmsgp)-sizeof(long), 2, 0);

						temp_sum = temp_sum + exmsgp.temp;
						if(msgp.temp == exmsgp.temp)
								count++;
				}

				// all 4 external process temperature are equal to central
				if(count == 4)
						stability++;

		
				if(stability == 1){ 
						
						printf("\nSystem has stabilized at %d temperature\n",msgp.temp);
						
						msgp.stable = 1;
				}
				else
						msgp.temp = (2*msgp.temp + temp_sum)/6;
						
				//send message to 4 external process		
				for(i=0;i<ProcessNum;i++)
						stat = msgsnd(msqid[i], &msgp, sizeof(msgp)-sizeof(long), 0);
		}
		
		printf("Stable central temperature = %d\n",msgp.temp);
		
		//remove central mailbox
		status = msgctl(cmsqid, IPC_RMID, 0);
		return 0;

}
				
						
		






