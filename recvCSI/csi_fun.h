/*
 * =====================================================================================
 *       Filename:  csi_fun.h
 *
 *    Description:  head file for csi processing fucntion  
 *        Version:  1.0
 *
 *         Author:  Yaxiong Xie  
 *         Email :  <xieyaxiongfly@gmail.com>
 *   Organization:  WANDS group @ Nanyang Technological University
 *
 *   Copyright (c)  WANDS group @ Nanyang Technological University
 * =====================================================================================
 */
#include <stdbool.h>
#include <sys/types.h>

#define Kernel_CSI_ST_LEN 23 

bool  is_big_endian();
int   open_csi_device();
void  close_csi_device(int fd);
int   read_csi_buf(unsigned char* buf_addr,int fd, int BUFSIZE);

