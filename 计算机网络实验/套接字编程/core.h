#include <WinSock2.h>
#include <stdio.h>
#include <WS2tcpip.h>
#include <cstdlib>
#include <iostream>
#include <time.h>

#define SEND_ERR 1
#define FIRST_RECV_ERR 2
#define RECV_ERR 3	
#define FILE_ERR 4
#define CONNECT_ERR 5
#define ERR_PACK 6 
#define PACK_CORR 7
// TFTP的操作码
#define CMD_RRQ (short)1
#define CMD_WRQ (short)2
#define CMD_DATA (short)3
#define CMD_ACK (short)4
#define CMD_ERROR (short)5
#define CMD_LIST (short)6
#define CMD_HEAD (short)7


bool upload(char* filename);

bool download(char* remoteFile , char* localFile);

