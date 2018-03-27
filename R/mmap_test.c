/****************************************************************************
 * FileName : mmap_test.c
 *
 * Abstract :
 * 	This file is a program for memory map test
 *
 * Modified :
 * 	Created : March 16, 2018 by Dongheon Han
****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>

#define FPGA_BASEADDRESS        0x08000000
#define LED_OFFSET	0x16

int main(void)
{
  int i;
	int fd;
	unsigned short *addr_fpga;
	unsigned short *addr_led;

	if ((fd=open("/dev/mem",O_RDWR|O_SYNC)) < 0) {
		perror("mem open fail\n");
		exit(1);
	}

	addr_fpga= (unsigned short *)mmap(NULL, 4096, PROT_WRITE|PROT_READ, MAP_SHARED, fd, FPGA_BASEADDRESS);
	addr_led = addr_fpga + LED_OFFSET / sizeof(unsigned short);

	if( *addr_led == (unsigned short)-1 ) {
		printf("mmap error\n");
		exit(1);
	}

  *addr_led = 0x01;
  for( i = 0; i < 7; i++) {
    *addr_led *= 2;
    sleep(1);
  }
  
	munmap(addr_fpga,4096);
	close(fd);
	return 0;
}
