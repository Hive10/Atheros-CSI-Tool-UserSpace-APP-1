/*
 * =====================================================================================
 *       Filename:  main.c
 *
 *    Description:  Here is an example for receiving CSI matrix 
 *                  Basic CSi procesing fucntion is also implemented and called
 *                  Check csi_fun.c for detail of the processing function
 *        Version:  1.0
 *
 *         Author:  Yaxiong Xie
 *         Email :  <xieyaxiongfly@gmail.com>
 *   Organization:  WANDS group @ Nanyang Technological University
 *   
 *   Copyright (c)  WANDS group @ Nanyang Technological University
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "csi_fun.h"

#define BUFSIZE 4096
#define PRINT 100

unsigned char buf_addr[BUFSIZE];

int main(int argc, char* argv[])
{
    FILE*       fp;
    int         fd;
    int         i;
    int         total_msg_cnt,cnt;
    u_int16_t   buf_len;
    
    /* check usage */
    if (1 == argc){
        /* If you want to log the CSI for off-line processing,
         * you need to specify the name of the output file
         */
        printf("/**************************************/\n");
        printf("/*   Usage: recv_csi <output_file>    */\n");
        printf("/**************************************/\n");
    }
    if (2 == argc){
        fp = fopen(argv[1],"w");
        if (!fp){
            printf("Fail to open <output_file>, are you root?\n");
            fclose(fp);
            return 0;
        }   
    }
    if (argc > 2){
        printf(" Too many input arguments !\n");
        return 0;
    }

    fd = open_csi_device();
    if (fd < 0){
        perror("Failed to open the device...");
        return errno;
    }
    
    printf("#Receiving data! Press Ctrl+C to quit!\n");

    total_msg_cnt = 0;
    
    while(1){
        /* keep listening to the kernel and waiting for the csi report */
        cnt = read_csi_buf(buf_addr,fd,BUFSIZE);

        if (cnt){
            total_msg_cnt += 1;

            if (total_msg_cnt % PRINT == 0)
            	printf("Recv %dth msg with rate: 0x%02x | Tx: %d | Rx: %d | Carriers: %d\n",total_msg_cnt, buf_addr[14], buf_addr[18], buf_addr[17], buf_addr[16]);
            
            /* log the received data for off-line processing */
	    buf_len = ((buf_addr[cnt-2] << 8) & 0xff00) | (buf_addr[cnt-1] & 0x00ff);
	    fwrite(&buf_len,1,2,fp);
	    fwrite(buf_addr,1,buf_len,fp);
        }
    }
    fclose(fp);
    close_csi_device(fd);
    return 0;
}
