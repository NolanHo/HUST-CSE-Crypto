#include "core.h"

#pragma comment(lib,"ws2_32.lib")

#define DATA_SIZE 512 //数据块大小

#define BUFLEN 255
#define PKT_MAX_RXMT 3 //最大重传次数

#define PKT_RCV_TIMEOUT 3*1000 //最长等待时间

using namespace std;

#pragma warning(disable:4996) // 禁用安全警告

// TFTP数据包结构体
struct tftpPacket{
	unsigned short cmd;	// 前两个字节表示操作码
	union	// 中间区字段
	{
		unsigned short code;//传输模式 netascii/octet
		unsigned short block;//块号
		char filename[2];	//文件名，溢出可以覆盖后面的内存，主要是请求包中使用
	};
	char data[DATA_SIZE];// 最后是数据区字段
};

sockaddr_in serverAddr, clientAddr;//服务器和客户端的ip地址
SOCKET sock;	// 客户端socket
unsigned int addr_len;	// ip地址长度

double transByte, consumeTime;
FILE* logFp;
char logBuf[512];
time_t rawTime;	//当地时间
tm* info;

void setnonblocking(int sockfd) {//非阻塞模式
	unsigned long on = 1;
	ioctlsocket(sockfd, FIONBIO, &on);
}
/*
 * upload
 * param: filename
 * return: bool
*/
bool upload(char* filename){
	int rxmt;//重传次数的变量计数
	double spack = 0, epack = 0;//成功包和丢失包的数量记录
	clock_t start, end;	// 记录时间
	transByte = 0;	// 传输字节数
	int time_wait_ack, r_size, choose;	// 等待时间,接收包大小,传输格式
	tftpPacket sendPacket, rcv_packet;	// 发送包,接收包
	// 写请求数据包
	sendPacket.cmd = htons(CMD_WRQ);	// 写入操作码
	// 在Linux和Windows网络编程时需要用到htons和htonl函数，用来将主机字节顺序转换为网络字节顺序。
	// 由于网络字节顺序是大端字节序，而主机字节顺序是小端字节序，所以在发送数据时需要将主机字节顺序转换为网络字节顺序。
	std::cout << "mode:(1.netascii  2.octet)" << endl;//选择传输模式
	std::cin >> choose;
	if (choose == 1)
		sprintf(sendPacket.filename, "%s%c%s%c", filename, 0, "netascii", 0);
	else if (choose == 2)
		sprintf(sendPacket.filename, "%s%c%s%c", filename, 0, "octet", 0);
	else 
	    printf("请输入正确的传输模式！\n");
	// 发送请求数据包
	//传输次数循环
	for (rxmt = 0; rxmt < PKT_MAX_RXMT; rxmt++)
	{
		if (sendto(sock, (char*)&sendPacket, sizeof(tftpPacket), 0, (struct sockaddr*)&serverAddr, addr_len) == SOCKET_ERROR)
		{
			continue;
			//epack++; //丢包数累加
		}
		else spack++;

		// 等待接收回应,最多等待3s,每隔20ms刷新一次
		for (time_wait_ack = 0; time_wait_ack < PKT_RCV_TIMEOUT; time_wait_ack += 20)
		{
			// 尝试接收
			r_size = recvfrom(sock, (char*)&rcv_packet, sizeof(tftpPacket), 0, (struct sockaddr*)&serverAddr, (int*)&addr_len);
			if (r_size > 0 && r_size < 4)
				printf("packet err: r_size=%d\n", r_size);	// 接收包异常
			if (r_size >= 4 && rcv_packet.cmd == htons(CMD_ACK) && rcv_packet.block == htons(0))
			{
				break;	// 成功收到ACK并且接收到的包为ACK，且确认号与发送包的块号相同
				spack++;//成功包数累加
			}
			if (r_size == -1)//未接收到则等待20ms
				Sleep(20);
		}
		if (time_wait_ack < PKT_RCV_TIMEOUT)
			break;	// 发送成功break掉循环，无需重传
		else // 未收到ACK，重传
		{
			printf("ACK timeout, drop\n");
			epack++;//丢包数累加，进行重传
			time(&rawTime);//获取时间
			info = localtime(&rawTime);
			sprintf(logBuf, "%s WARNING: upload %s, mode: %s, %s\n", asctime(info), filename, choose == 1 ? ("netascii") : ("octet"), "Can't receive ACK, Retransmission");
			//minus
			fwrite(logBuf, 1, strlen(logBuf), logFp);//写入日志
			continue;
		}
	}
	if (rxmt >= PKT_MAX_RXMT)//重传三次后未收到ACK
	{
		// 重传三次也未接收到ACK终止本次传输
		printf("Could not receive ACK from server.(upload), because 3 packet drop.\n");
		time(&rawTime);
		info = localtime(&rawTime);
		sprintf(logBuf, "%s ERROR: upload %s, mode: %s, %s\n", asctime(info), filename, choose == 1 ? ("netascii") : ("octet"), "Could not receive from server.");
		fwrite(logBuf, 1, strlen(logBuf), logFp);//写入日志
		return false;//直接结束
	}

	FILE* fp = NULL;	// 打开文件
	if (choose == 1)
		fp = fopen(filename, "r");//ascii使用r打开文件
	else
		fp = fopen(filename, "rb");//二进制使用rb打开文件
	if (fp == NULL) {//打开文件失败
		printf("文件打开失败!\n");
		time(&rawTime);
		info = localtime(&rawTime);
		sprintf(logBuf, "%s ERROR: upload %s, mode: %s, %s\n", asctime(info), filename, choose == 1 ? ("netascii") : ("octet"), "File not exists!");
		fwrite(logBuf, 1, strlen(logBuf), logFp);
		return false;//种植传输
	}
	int s_size = 0;
	unsigned short block = 1;//块编号
	sendPacket.cmd = htons(CMD_DATA);	// 数据包操作码
	// 传送数据包
	start = clock();//开始计时
	do
	{
		memset(sendPacket.data, 0, sizeof(sendPacket.data));
		sendPacket.block = htons(block);	// 写入块编号
		s_size = fread(sendPacket.data, 1, DATA_SIZE, fp);	// 读入数据
		transByte += s_size;//传输字节数
		// 最多重传3次
		for (rxmt = 0; rxmt < PKT_MAX_RXMT; rxmt++)//重传次数累计
		{
			// 发送数据包
			if (sendto(sock, (char*)&sendPacket, s_size + 4, 0, (struct sockaddr*)&serverAddr, addr_len) == SOCKET_ERROR)
			{
				//epack++;//发送失败则坏包数累加
				continue;
			//	epack++;
			}
			else spack++;
			printf("Sending the block:%d\n", block);
			// 等待ACK,最多等待3s,每隔20ms刷新一次
			for (time_wait_ack = 0; time_wait_ack < PKT_RCV_TIMEOUT; time_wait_ack += 20)
			{
				r_size = recvfrom(sock, (char*)&rcv_packet, sizeof(tftpPacket), 0, (struct sockaddr*)&serverAddr, (int*)&addr_len);
				if (r_size > 0 && r_size < 4)
					printf("packet err: r_size=%d\n", r_size);
				if (r_size >= 4 && rcv_packet.cmd == htons(CMD_ACK) && rcv_packet.block == htons(block))
				{
					//接收到ACK且ACK确认块编号与发送的块编号相同
					break;//本块成功发送，结束循环
					//spack++;无需累加了，因前面成功发送已累加
				}
				if (r_size == -1)//还未接收到ACK，等待20ms再尝试
					Sleep(20);
			}
			if (time_wait_ack < PKT_RCV_TIMEOUT)
				break;	// 发送成功
			else // 未收到ACK，重传
			{
				cout << "ACK drop.." << endl;
				epack++;//掉包数累加
				time(&rawTime);
				info = localtime(&rawTime);
				sprintf(logBuf, "%s WARNING: upload %s, mode: %s, %s\n", asctime(info), filename, choose == 1 ? ("netascii") : ("octet"), "Can't receive ACK, Retransmission");
				fwrite(logBuf, 1, strlen(logBuf), logFp);
				continue;
			}
		}
		if (rxmt >= PKT_MAX_RXMT)
		{
			// 3次重传失败
			printf("Could not receive ACK from server.(upload), because 3 packet drop.\n");
			fclose(fp);
			time(&rawTime);
			info = localtime(&rawTime);
			sprintf(logBuf, "%s ERROR: upload %s, mode: %s, %s\n", asctime(info), filename, choose == 1 ? ("netascii") : ("octet"), "Could not receive ACK from server.");
			fwrite(logBuf, 1, strlen(logBuf), logFp);
			return false;
		}
		block++;	// 传输下一个数据块
	} while (s_size == DATA_SIZE);	// 当数据块未装满时认为时最后一块数据，结束循环
	end = clock();
	printf("上传文件成功!\n");
	fclose(fp);
	consumeTime = ((double)(end - start)) / CLK_TCK;//计算传输时间
	//cout<<
	printf("文件大小: %.2f KB, 耗时: %.3f s\n", transByte / 1024, consumeTime);
	printf("上传速度: %.2f KB/s\n", transByte / (1024 * consumeTime));
	//cout << epack << endl << spack << endl;
	printf("丢包率: %.2f%%\n", epack / (epack + spack) * 100);
	time(&rawTime);
	info = localtime(&rawTime);
	sprintf(logBuf, "%s\n INFO: upload %s, mode: %s, size: %.1f kB, consuming time: %.4f s\n", asctime(info), filename, choose == 1 ? ("netascii") : ("octet"), transByte / 1024, consumeTime);
	fwrite(logBuf, 1, strlen(logBuf), logFp);
	return true;
}

/*
 * download
 * param: filename
 * return: bool
*/
bool download(char* remoteFile , char* localFile){
	//char* remoteFile=filename1, char* localFile=filename1;
	FILE* fp = NULL;
	int cnt = 0;

	//int rxmt;//重传次数计数变量
	double epack = 0, spack = 0;//成功发送的包和坏包数量计数
	clock_t start, end;	// 记录时间
	transByte = 0;	// 传输字节数
	int time_wait_ack, r_size, choose;	// 等待时间,接收包大小，选择模式
	tftpPacket sendPacket, rcv_packet, ack;// 发送包,接收包
	int time_wait_data;//等待时间
	unsigned short block = 1;//块标号
	// 读请求数据包
	start = clock();
	sendPacket.cmd = htons(CMD_RRQ);	// 读取操作码
	std::cout << "mode:(1.netascii  2.octet)" << endl;//选择传输模式
	std::cin >> choose;
	if (choose == 1)
		sprintf(sendPacket.filename, "%s%c%s%c", remoteFile, 0, "netascii", 0);
	else
		sprintf(sendPacket.filename, "%s%c%s%c", remoteFile, 0, "octet", 0);
	// 发送请求数据包
	if (sendto(sock, (char*)&sendPacket, sizeof(tftpPacket), 0, (struct sockaddr*)&serverAddr, addr_len) == SOCKET_ERROR)
	{
		epack++;
		//continue;
	}
	else spack++;
	// 新建本地写入文件

	if (choose == 1)
		fp = fopen(localFile, "w");//ASCII用w写入文件
	else
		fp = fopen(localFile, "wb");//二进制用wb写入文件
	if (fp == NULL)//打开文件失败
	{
		printf("创建文件失败!\n");
		time(&rawTime);
		info = localtime(&rawTime);
		sprintf(logBuf, "%s ERROR: download %s as %s, mode: %s, Create file \"%s\" error.\n", asctime(info), remoteFile, localFile, choose == 1 ? ("netascii") : ("octet"), localFile);
		fwrite(logBuf, 1, strlen(logBuf), logFp);
		return false;//直接终止传输
	}
	// 接收数据

	sendPacket.cmd = htons(CMD_ACK);
	do {
		for (time_wait_data = 0; time_wait_data < PKT_RCV_TIMEOUT; time_wait_data += 20)
		{
			//接收服务器发送的数据包
			r_size = recvfrom(sock, (char*)&rcv_packet, sizeof(tftpPacket), 0, (struct sockaddr*)&serverAddr, (int*)&addr_len);
			if (r_size > 0 && r_size < 4)
				printf("packet err: r_size=%d\n", r_size);//坏包
			if (r_size >= 4 && rcv_packet.cmd == htons(CMD_DATA) && rcv_packet.block == htons(block))
			{//接收到数据包，并且包的块号一致
				cnt = 0;
				spack++;//累加
				printf("Received: blockNum=%d, dataSize=%d\n", ntohs(rcv_packet.block), r_size - 4);
				// 发送ack请求
				sendPacket.block = rcv_packet.block;	//ack包数据区编号
				sendto(sock, (char*)&sendPacket, sizeof(tftpPacket), 0, (struct sockaddr*)&serverAddr, addr_len);//发送ACK
				//写入数据
				fwrite(rcv_packet.data, 1, r_size - 4, fp);
				break;
			}
			if (r_size == -1)
				Sleep(20);
		}
		if (time_wait_data >= PKT_RCV_TIMEOUT && block == 1)//超时且为第一个包说明连接超时，结束传输
		{
			epack++;
			break;
		}
		if (time_wait_data >= PKT_RCV_TIMEOUT && block > 1 && cnt < 3)//超时且不为第一个包
		{
			printf("DataPack timeout, drop\n");
			cnt++;
			epack++;
			sendPacket.block = htons(block - 1);
			sendto(sock, (char*)&sendPacket, sizeof(tftpPacket), 0, (struct sockaddr*)&serverAddr, addr_len);//发送重复ACK给服务器告知未接收到包
			r_size = DATA_SIZE + 4;
			continue;
		}

		if (time_wait_data >= PKT_RCV_TIMEOUT && cnt == 3)//重传三次ACK且仍未接收到新包则ERROR，直接结束
		{
			printf("Waiting for DATA #%d timeout.\n", block);
			fclose(fp);
			time(&rawTime);
			info = localtime(&rawTime);
			sprintf(logBuf, "%s ERROR: download %s as %s, mode: %s, Wait for DATA #%d timeout.\n", asctime(info), remoteFile, localFile, choose == 1 ? ("netascii") : ("octet"), block);
			fwrite(logBuf, 1, strlen(logBuf), logFp);
			return false;
		}
		transByte += (r_size - 4);
		block++;
	} while (r_size == DATA_SIZE + 4);
	end = clock();
	consumeTime = ((double)(end - start)) / CLK_TCK;
	printf("文件大小: %.2f KB, 耗时: %.3f s\n", transByte / 1024, consumeTime);
	printf("下载速度: %.2f kB/s\n", transByte / (1024 * consumeTime));
	printf("丢包率 :%.1f%%\n", epack / (epack + spack) * 100);
	fclose(fp);
	time(&rawTime);
	info = localtime(&rawTime);
	sprintf(logBuf, "%s INFO: download %s as %s, mode: %s, size: %.1f kB, consuming time: %.2f s\n", asctime(info), remoteFile, localFile, choose == 1 ? ("netascii") : ("octet"), transByte / 1024, consumeTime);
	fwrite(logBuf, 1, strlen(logBuf), logFp);
	return true;
}