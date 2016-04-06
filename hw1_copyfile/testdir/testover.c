#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
		FILE *fp,*fp2;
		int comd_over;
		
		
		if(argc  < 3){
				printf("Error!No target file or document\n");
				return 0;
		}

		// 判斷來源檔案存不存在
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

		return 0;
}
						


