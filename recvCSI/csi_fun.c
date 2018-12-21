/*
 * =====================================================================================
 *      Filename:  ath9k_csi.c
 *
 *   Description:  basic csi processing fucntion
 *                 you can implement your own fucntion here
 *       Version:  1.0
 *
 *        Author:  Yaxiong Xie 
 *        Email :  <xieyaxiongfly@gmail.com>
 *  Organization:  WANDS group @ Nanyang Technological University 
 *
 *   Copyright (c) WANDS group @ Nanyang Technological University 
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "csi_fun.h"

#define csi_st_len 23
/* test and find out the system is big endian or not*/
//for 16/32/64 system this should be all fine.
bool is_big_endian(){
    unsigned int a = 0x1;
    unsigned char b = *(unsigned char *)&a;
    if ( b == 0)
    {
        return true;
    }
    return false;
}

int open_csi_device(){
   int fd;
   fd = open("/dev/CSI_dev",O_RDWR);
    return fd;
}

void close_csi_device(int fd){
    close(fd);
    //remove("/dev/CSI_dev");
}


int read_csi_buf(unsigned char* buf_addr,int fd, int BUFSIZE){
    int cnt;
    /* listen to the port
     * read when 1, a csi is reported from kernel
     *           2, time out
     */           
    cnt = read(fd,buf_addr,BUFSIZE);
    if(cnt)
        return cnt;
    else
        return 0;
}
