/****************************************************************************
 * FileName : mmap_test.c
 *
 * Abstract :
 * 	This file is a program for memory map test
 *
 * Modified :
 * 	Created : March 16, 2018 by Dongheon Han
****************************************************************************/

/*
Address information
LED                 0x08000016
Seven Segment(FND)  0x08000004
Dot Matrix(FND)     0x08000210
Text LCD            0x80000090
Buzzer              0x80000070
Push Switch         0x80000000 9개의 버튼에 각각의 address 존재
Step Motor          0x8000000C
*/
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

/*
제어해야 할 것들 목록
fgpa_test_fnd
fpga_test_lcd
fgpa_test_dot
fgpa_test_push_switch 
fgpa_test_ 
fgpa_test 
*/

int main(void)
{
    int i;
	int fd;
	char ascValue;

	if ((fd=open("/dev/mem",O_RDWR|O_SYNC)) < 0) {
		perror("mem open fail\n");
		exit(1);
	}
  
	if( *addr_led == (unsigned short)-1 ) {
		printf("mmap error\n");
		exit(1);
	}

	while(true)
	{
		// 아직 코드를 보지 못해서 감이 잘 안옴 	
	}

	close(fd); // 파일 디렉토리를 닫아 줌 
	return 0;
}
