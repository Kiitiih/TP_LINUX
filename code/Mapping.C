#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdint.h> //include pour uint32
#include <sys/mman.h> //include pour mmap

//Include pour le open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main () {
	
	uint32_t * p;
	int fd = open("/dev/mem", O_RDWR);
	p = (uint32_t*)mmap(NULL, 4, PROT_WRITE|PROT_READ, MAP_SHARED,
	fd, 0xFF203000);
	while(1)
	{
		for (int i = 0 ; i < 10 ; i++)
		{
			*p = (1<<i);
			usleep(100000);
		}
		
		
	} 
}