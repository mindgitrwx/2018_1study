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
#include <signal.h>

#define BUFSIZE 128

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

#include <stdio.h>

#define BUFSIZE 128

int parse_output(void) {
    char *cmd = "ls -l";    

    char buf[BUFSIZE];
    FILE *fp;

    if ((fp = popen(cmd, "r")) == NULL) {
        printf("Error opening pipe!\n");
        return -1;
    }

    //[0] [0] [0] [0] [0] [0] [0] [0]
    //[0][0][0][0][0][0][0][0]
    while (fgets(buf, BUFSIZE, fp) != NULL) {
        // Do whatever you want here...
        printf("OUTPUT: %s", buf);
    }

    if(pclose(fp))  {
        printf("Command not found or exited with error status\n");
        return -1;
    }
    return 0;
}

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
	//dev_led = open("/dev/fpga_led", O_RDWR);
	//dev_fnd = open("/dev/fpga_fnd", O_RDWR);
	//dev_dot = open("/dev/fpga_dot", O_RDWR);
	//dev_text_lcd = open("/dev/fpga_text_lcd", O_RDWR);

	//close(dev_push_switch);
	//close(dev_led);
	//close(dev_fnd);
	//close(dev_dot);
	//close(dev_text_lcd);
        ////for get dev number
        //printf("Device Open switch  dev number: %d \n", dev_push_switch);
        //printf("Device Open led dev number: %d \n", dev_led);
        //printf("Device Open fnd dev number: %d \n", dev_fnd);
        //printf("Device Open dot dev number: %d \n", dev_dot);
        //printf("Device Open text dev number: %d \n", dev_text_lcd);

        // Device Push open
        if(dev_push_switch<0)
        {
            //close(dev_push_switch);
            //close(DEV_NUM_SWITCH);
            //close(DEV_NUM_LED);
            //close(DEV_NUM_FND);
            //close(DEV_NUM_DOT);
            //close(DEV_NUM_TEXT);

	    close(dev_push_switch);
	 //   close(dev_led);
         //   close(dev_fnd);
	 //   close(dev_dot);
	 //   close(dev_text_lcd);
        
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
           flag_push[9];
           
           for(i=0; i<9; i++)
           {
                 if(push_sw_buff[i] == 1){
                        
                        printf("is it on adding flag_push? \n");
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
           if(flag_push[5])//for exit while to close devices
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
           //  for exit while
           
        }

        //close(DEV_NUM_SWITCH);
        //close(DEV_NUM_LED);
        //close(DEV_NUM_FND);
        //close(DEV_NUM_DOT);
        //close(DEV_NUM_TEXT);

        close(dev_push_switch);
        close(dev_led);
        close(dev_fnd);
        close(dev_dot);
        close(dev_text_lcd);
        
         
   //     close(dev_push_switch);

	return 0;
}
