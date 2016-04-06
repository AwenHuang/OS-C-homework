#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#define FILE_LENGTH 0x400

int main(int argc, char *argv[])
{
		int fd,i,j;
		void *map_memory;
		const int len=100;
		/* Open a file to be mapped. */
		fd = open("hw4.test", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
		lseek(fd,len+1, SEEK_SET);
		write(fd, "\0", 1);
		lseek(fd, 0, SEEK_SET);

		/* Create map memory. */
		map_memory = mmap(0, len, PROT_WRITE, MAP_SHARED, fd, 0);
		close(fd);

		/* Write to mapped memory. */
		char *a = "Hello";
		char *b = "400410048";
		sprintf(map_memory, "%s\n%s\n",a,b);

		return 0;
}
