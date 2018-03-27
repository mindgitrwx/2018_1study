/****************************************************************************
 * FileName : mmap_test.c
 *
 * Abstract :
 * 	This file is a program for memory map test
 *
 * Modified :
 * 	Created : March 16, 2018 by Dongheon Han
 *      Modified: March 27, 2018 by JongHyeon Yeo (jonghyeon.rw@gmail.com)
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
#include <signal.h>

#define FPGA_BASEADDRESS        0x08000000
#define LED_OFFSET	0x16
#define LED_1 "./fpga_test_led 1"
#define LED_2 "./fpga_test_led 2"
#define LED_3 "./fpga_test_led 3"
#define LED_4 "./fpga_test_led 4"
#define LED_5 "./fpga_test_led 5"
#define LED_6 "./fpga_test_led 6"
#define LED_7 "./fpga_test_led 7"
#define LED_8 "./fpga_test_led 8"
#define SWITCH "./fpga_test_push_switch"

#define SEVENSEG "./fpga_test_fnd 2018"
#define SEVENSEG_INIT "./fpga_test_fnd 0000"
#define MAX_BUTTON 9

#define DEV_NUM_SWITCH 3
#define DEV_NUM_LED 4
#define DEV_NUM_FND 5
#define DEV_NUM_DOT 6
#define DEV_NUM_TEXT 7

unsigned char quit = 0;

void user_signal1(int sig)
{
	quit = 1;
}

int main(void)
{
        int i;
	int dev_push_switch, dev_led, dev_fnd, dev_dot, dev_text_lcd;
	int buff_size;
        
        int flag_push[9] = {0,};

	unsigned char push_sw_buff[MAX_BUTTON];

	dev_push_switch = open("/dev/fpga_push_switch", O_RDWR);
        
        // Device Push open
        if(dev_push_switch<0)
        {
	    close(dev_push_switch);
	    printf("Device Open Error: dev number: %d \n", dev_push_switch);
            return -1;
        }
        else
        {
            printf("Switch Device Number %d \n", dev_push_switch );
        }
        
        (void)signal(SIGINT, user_signal1);

	buff_size=sizeof(push_sw_buff);


        // program run
        while(1)
        {
           usleep(40000); // test
           read(dev_push_switch,&push_sw_buff, buff_size);
           
           for(i=0; i<9; i++)
           {
                 if(push_sw_buff[i] == 1){
                        printf("is it on adding flag_push? \n"); // the line is not run 
	                flag_push[i]++;
                        if(i == 0 && flag_push[i]==4)
                        {
                             flag_push[i] = 0;
                        }
                        if(i == 1 && flag_push[i]==2)
                        {
                             flag_push[i] = 0;
                        }
                        if(i == 2 && flag_push[i]==2)
                        {
                             flag_push[i] = 0;
                        }
                        if(i == 3 && flag_push[i]==2)
                        {
                             flag_push[i] = 0;
                        }
                        if(i == 4)
                        {
                             flag_push[i] = 0;
                        }
	         }	
                 
           }

           //for flag debug
           printf("button pushed \n");
           for(i=0; i<9; i++)
           {
                printf("[%d] ", push_sw_buff[i]) ;
           }
           printf("\n");
           printf("number of button pushed \n");
           for(i=0; i<9; i++)
           {
                printf("[%d] ", flag_push[i]) ;
           }
           printf("\n");
           //flag debug end

           if(push_sw_buff[5])
           {
                for(i=0; i<9; i++)
                {
                    printf("push_sw_buffer before exit %d \n", push_sw_buff[i]) ;
                } 
                break;
           }
           if(flag_push[0])
           {
	        system(LED_7);
	        system(LED_8);
           }
           if(flag_push[1])
           {
                if(flag_push[1] == 1)
                {
	    	    system(SEVENSEG);
                }
                if(flag_push[1] == 0)
                {
	    	    system(SEVENSEG_INIT);
                }
           }
 	   if(flag_push[2])
           {
           }
 	   if(flag_push[3])
           {
           }
           if(flag_push[4])
           {
           }
           if(flag_push[5])
           {
           }
           if(flag_push[6])
           {
           }
           if(flag_push[7])
           {
           }
           if(flag_push[8])
           {
           }
        }

        close(dev_push_switch);
        close(dev_led);
        close(dev_fnd);
        close(dev_dot);
        close(dev_text_lcd);
	return 0;
}
