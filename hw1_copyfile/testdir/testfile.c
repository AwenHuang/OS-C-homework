#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
		DIR *dir;
		struct dirent *dirptr;
		FILE *fp,*fp2;
		
		
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
				fp2 = fopen(argv[argc-1],"w");
				
			
				char *str;
				char *ptr;
				char document[100];
				str = argv[argc-1];
				ptr = strstr(argv[argc-1],"/");
				//printf("str=%d ptr=%d\n",str,ptr);
				if(ptr != NULL){
						strncpy(document,argv[argc-1],ptr-str);
						printf("%s\n",document);
				}

				char c;
				while((c = getc(fp)) != EOF)
						putc(c, fp2);
				fclose(fp);
				fclose(fp2);
		}

		/*
		if(target_dir == 1){
				while((dirptr = readdir(dir))!=NULL){
					
						//資料夾內有一樣的檔案名
						if(strcmp(argv[1],dirptr->d_name) == 0){
								int comd_over;
								printf("File name has already exist\nOverwrite it?(y/n)\n");
								scanf("%c",&comd_over);
								if(comd_over == 'y')
										continue;
								else if(comd_over == 'n')
										return 0;
						}
				}
				char pathname[100];
				sprintf(pathname,"%s/%s",argv[argc-1],argv[1]);
				fp2 = fopen(pathname,"w");
				char c;
				while((c = getc(fp)) != EOF)
						putc(c,fp2);
				fclose(fp);
				fclose(fp2);
				closedir(dir);
		}*/

		return 0;
}
						


