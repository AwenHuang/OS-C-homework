#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/reg.h>


int main(int argc,char *argv[])
{
		FILE *fp,*fp2;
		char comd_over;

		int status;
		pid_t pid;
		long orig_eax;
		pid = fork();
		
	
		if(argc  < 3){
				printf("Error!No target file or document\n");
				return 0;
		}

		if(pid == 0){
				ptrace(PTRACE_TRACEME, 0, 0, 0);

				fp = fopen(argv[1],"r");
				if(!fp){
					printf("Source file does not exit\n");
					return 0;
				}
				else{
				//先檢查目的檔案存不存在
						fp2 = fopen(argv[argc-1],"r");
						if(fp2){ // 存在
								printf("Target file has already exist\nOverwrite it?(y/n)\n");
								scanf("%c",&comd_over);
								if(comd_over == 'n')
										return 0;
						}
				
						fp2 = fopen(argv[argc-1],"w");
				
						char c;
						while((c = getc(fp)) != EOF)
								putc(c, fp2);
						fclose(fp);
						fclose(fp2);
				}
		}
		else{
				while(1){
						wait(&status);
						if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) {
								// stopped before or after a system call -- query the child and print out info
								orig_eax = ptrace(PTRACE_PEEKUSER, pid, 4 * ORIG_RAX, NULL);
								printf("The child made a system call %ld\n", orig_eax);
						}
						if (WIFEXITED(status) || WIFSIGNALED(status)) {
								 // child has exited or terminated
								break;
						}
						ptrace(PTRACE_SYSCALL, pid, NULL, NULL); // ignore any signal and continue the child
				}
		}
				return 0;
}
						


