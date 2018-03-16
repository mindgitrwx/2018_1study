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

#define FPGA_BASEADDRESS     0x08000000
#define LED_OFFSET	         0x16
#define SEVEN_SEGMENT_OFFSET 0x4
#define DOT_MATRIX_OFFSET    0x210
#define TEXT_LCD_OFFSET      0x90
#define BUZZER_OFFSET        0x70
#define PUSH_SWITCH_OFFSET   0x50
#define DIP_SWITCH_OFFSET    0x0
#define STEP_MOTOR_OFFSET    0xC

// push switch, 9개의 버튼에 각각의 address 존재 
// button 제어 시 해당 address 의 값이 0 또는 1로 설정됨

#define PUSH_ON_1            addr_push_switch  
#define PUSH_ON_2            addr_push_switch + 1 
#define PUSH_ON_3            addr_push_switch + 2 
#define PUSH_ON_4            addr_push_switch + 3
#define PUSH_ON_5            addr_push_switch + 4
#define PUSH_ON_5            addr_push_switch + 5
#define PUSH_ON_5            addr_push_switch + 6
#define PUSH_ON_5            addr_push_switch + 7
#define PUSH_ON_5            addr_push_switch + 8


// address 에 관련된 부분을 빼 놓고 싶음 
/*
typedef struct {
	
} 
*/

const int seven_segments[MAX_DIGITS][MAX_SEGMENTS] =
{
	{1,1,1,1,1,1,0}, {0,1,1,0,0,0,0}, {1,1,0,1,1,0,1}, {1,1,1,1,0,0,1},
	{0,1,1,0,0,1,1}, {1,0,1,1,0,1,1}, {0,0,1,1,1,1,1}, {1,1,1,0,0,0,0},
	{1,1,1,1,1,1,1}, {1,1,1,0,0,1,1}
};

const int push_flag[5] = {0,};

int main(void)
{
  int i;
	int fd;
	char ascValue;

	// length of unsinged short : 4	
	unsigned short *addr_fpga;
	unsigned short *addr_led;
	unsigned short *addr_buzzer;
	unsigned short *addr_dot_matrix;
	unsigned short *addr_push_switch;
	unsigned short *addr_seven_segment;
	unsigned short *addr_step_motor;
	unsigned short *addr_text_lcd;

	if ((fd=open("/dev/mem",O_RDWR|O_SYNC)) < 0) {
		perror("mem open fail\n");
		exit(1);
	}
  
	/*mmap 특정 메모리 주소, Memory Segment Length, rwx 권한, mapping 영역 공유 권한, device file descripter, mapping 할 물리 주소 */
	addr_fpga            = (unsigned short *)mmap(NULL, 4096, PROT_WRITE|PROT_READ, MAP_SHARED, fd, FPGA_BASEADDRESS);
	addr_led             = addr_fpga + LED_OFFSET          / sizeof(unsigned short);
	addr_seven_segment   = addr_fpga + SEVEN_SEGMENT_OFFSET/ sizeof(unsigned short);
	addr_dot_matrix      = addr_fpga + DOT_MATRIX_OFFSET   / sizeof(unsigned short);
	addr_text_lcd        = addr_fpga + TEXT_LCD_OFFSET     / sizeof(unsigned short);
	addr_buzzer          = addr_fpga + BUZZER_OFFSET       / sizeof(unsigned short);
	addr_push_switch     = addr_fpga + PUSH_SWITCH_OFFSET  / sizeof(unsigned short);
	addr_step_motor      = addr_fpga + STEP_MOTOR_OFFSET   / sizeof(unsigned short);

	if( *addr_led == (unsigned short)-1 ) {
		printf("mmap error\n");
		exit(1);
	}

    // 주소 안의 값을 나타냄 temp example 
    *addr_led = 0x01;
    for( i = 0; i < 7; i++) {
      *addr_led *= 2;
      sleep(1);
    }

	/* process start */
    /* 처음 실행시 Text LCD는 빈 칸으로 표시, 이외 나머진 off 상태 */

    /* 
	  init 
      종료 조건을 설정하지 않는다고 가정했으므로 그냥 while true 로 처리. ctrl-z 로 끔 
	*/
	while(true)
	{ 
		if(PUSH_ON_1) // 첫번째 누를 시 8개 중 아래쪽의 4개 LED on, 두번째 누를 시 8개 중 위 쪽의 4개 LED ON, 세번째 누를 시 모든 LED ON, 네번째 누를 시 모든 LED OFF
		{
			push_flag[0]++;
			if(push_flag[0] == 1)
			{
                // 아래쪽의 led on 
				for(int i = 0; i < 8; i++)
				{
					if(i<4)
					{
  				        *(addr_led + i) = 0x01; // 이렇게 하는것이 맞는지 헷갈림 
					}
					else
					{
  				 	    *(addr_led + i) = 0x00; // 이렇게 하는것이 맞는지 헷갈림 
					}
				}
			}
			else if(push_flag[0] == 2)
			{
				for(int i = 0; i < 8; i++)
				{
					if(i<4)
					{
  				       *(addr_led + i) = 0x00; // 이렇게 하는것이 맞는지 헷갈림 
					}
					else
					{
  				  	   *(addr_led + i) = 0x01; // 이렇게 하는것이 맞는지 헷갈림 
					}
				}
			}
			else if(push_flag[0] == 3)
			{
				for(int i = 0; i < 8; i++)
				{
  				 	*(addr_led + i) = 0x01;   // 이렇게 하는것이 맞는지 헷갈림 
				}
	
			}
			else if(push_flag[0] == 4)
			{
				for(int i = 0; i < 8; i++)
				{
  					*(addr_led + i) = 0x00;
				}
				push_flag[0] = 0; // push flag 초기화
			}
		} // TODO : extract function from seven_segments 
		else if(PUSH_ON_2) //첫번째 누를 시 seven segment의 각 digit 에 2 0 1 8 표시, 두번째 누를 시 seven segment OFF
		{
			push_flag[1]++;
			if(push_flag[1] == 1)      // 2 0 1 8 표시 
			{
				for(int i = 0; i < 8; i++)
				{
				    *(addr_seven_segment + 0 + i) = seven_segments[2][i];
					*(addr_seven_segment + 8 + i) = seven_segments[0][i];
					*(addr_seven_segment + 16+ i) = seven_segments[1][i];
					*(addr_seven_segment + 24+ i) = seven_segments[8][i];
				}
			}
			else if(push_flag[1] == 2) // seven segement off
			{
         	for(int i = 0; i < 36; i++)
				{
					*(addr_seven_segment + i) = 0x00;
				} 
				push_flag[1] = 0;	
			}
		}
		else if(PUSH_ON_3) //첫번째 누를 시 dot matrix 에 자기 조 숫자 표시 - 크기 관계 없음 10조의 경우 0 1조의 경우 1 2조의 조의 경우 2
		{

			push_flag[2]++;
		} // TODO: 끄라는 이야기는 안보임 : 요구사황을 보다 명확하게 바꿀 필요가 있음. Dot matrix 감이 잘 안옴
		else if(PUSH_ON_4) //첫번째 누를 시 Text lcd 화면의 첫 라인에 2017.03.16, 두 번째 라인에 Team xx 출력 (xx: 자신의 팀 번호)*/
		{
			// char 형으로 선언되어 있지 않으므로 이렇게 노가다해야 하는지 의문스럽다. 
			// upper line
			*(addr_text_lcd + 0) = '2';
			*(addr_text_lcd + 1) = '0';
			*(addr_text_lcd + 2) = '1';
			*(addr_text_lcd + 3) = '7';
			*(addr_text_lcd + 4) = '.';
			*(addr_text_lcd + 5) = '0';
			*(addr_text_lcd + 6) = '3';
			*(addr_text_lcd + 7) = '.';
			*(addr_text_lcd + 8) = '1';
			*(addr_text_lcd + 9) = '6';
			/*
			*addr_text_lcd =
			*addr_text_lcd =
			*addr_text_lcd =
			*addr_text_lcd =
			*addr_text_lcd =
		    *addr_text_lcd =
			*/

      		// under line
			*(addr_text_lcd + 16) = 'T';
			*(addr_text_lcd + 17) = 'e';
			*(addr_text_lcd + 18) = 'a';
			*(addr_text_lcd + 19) = 'm';
			*(addr_text_lcd + 20) = ' '; 
			*(addr_text_lcd + 21) = '0';
			*(addr_text_lcd + 22) = '9';
      
			/*
			*addr_text_lcd =
			*addr_text_lcd =
			*addr_text_lcd =
     		*/

			push_flag[3]++;
		}// TODO : refactor this fucntion for simplify 
		else if(PUSH_ON_5) // 초기 상태로 복귀 
		{
			for(i=0;i< 1024;i++)
			{
				*(addr_fpga + i) = 0; // 초기화 - 이렇게 하는게 맞는지 의문임 
			}
			push_flag[4]++;
		} 
	} // end of while

	/* The munmap() function shall remove any mappings for those entire pages containing any part of the address space of the process starting at addr and continuing for len bytes.*/
	munmap(addr_fpga         ,4096);
	/*
	munmap(addr_buzzer       ,4096);
	munmap(addr_dot_matrix   ,4096);
	munmap(addr_led          ,4096);
	munmap(addr_push_switch  ,4096);
	munmap(addr_seven_segment,4096);
	munmap(addr_step_motor   ,4096);
	munmap(addr_text_lcd     ,4096);
    */
	
	close(fd);
	return 0;
}
