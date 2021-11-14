#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "initGPIO.h"

unsigned int *getGPIOPtr(void)
{
	int fdgpio = open("/dev/gpiomem", O_RDWR);
	
	if (fdgpio <0) {
		printf("unable to open");
	}
	
	// Note: The original line below causes error
	//unsigned int *gpioPtr = (unsigned int *)mmap(0,4096,PROT_READ|cat,MAP_SHARED,fdgpio,0);
	

/*
	0 = address
	4096 = length
	PROT_READ+PROT_WRITE are the protect types, means the user can read and write
	MAP_SHARED = flag (means this flag is used to share the mapping with all other processes, which are mapped to this object)
	fdgpio = file descriptor which has to be mapped
	0 = offset
*/

	unsigned int *gpioPtr = (unsigned int *)mmap(NULL,4096,PROT_READ+PROT_WRITE,MAP_SHARED,fdgpio,0);

	
	return gpioPtr;
}
