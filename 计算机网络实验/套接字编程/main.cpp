#include "core.h"
#include "core.cpp"
#include <stdio.h>

// 建议使用 g++ 编译, 不要用clang++

int main() {
	// chcp 65001 用于设置控制台编码为UTF-8
	system("chcp 65001");
	printf("--------------------TFTP--------------------\n");

	//获取时间
	time(&rawTime);
	//转换为当地时间
	info = localtime(&rawTime);

	// 打开日志文件
	logFp = fopen("tftp.log", "a");
	if (logFp == NULL)
		std::cout << "打开日志文件失败！" << endl;

	//打印当前时间
	printf("time: %s", asctime(info));

	char buf[BUFLEN];//数据缓冲区

	WSADATA wsaData;
	addr_len = sizeof(struct sockaddr_in);

	//初始化 winsock
	int nRC = WSAStartup(0x0101, &wsaData);
	if (nRC){
		printf("客户端winsock出错!\n");
		return 0;
	}
	if (wsaData.wVersion != 0x0101){
		printf("客户端winsock版本有误!\n");
		WSACleanup();
		return 0;
	}
	printf("客户端winsock初始化完成 !\n");

	char serverIP[20],clientIP[20];
	std::cout << "请输入服务器IP：";
	scanf("%s", serverIP);
	std::cout << "请输入客户端IP：";
	scanf("%s", clientIP);

	// 创建客户端socket
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET){
		std::cout << "客户端socket创建失败!" << endl;
		WSACleanup();
		return 0;
	}
	printf("客户端socket创建成功!\n");


	// 设置客户端 地址族 端口 ip
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(0);//设为0，自动分配
	clientAddr.sin_addr.S_un.S_addr = inet_addr(clientIP);


	//socket绑定
	nRC = bind(sock, (LPSOCKADDR)&clientAddr, sizeof(clientAddr));
	if (nRC == SOCKET_ERROR){
		// 绑定失败
		printf("客户端socket绑定失败!\n");
		closesocket(sock);
		WSACleanup();
		return 0;
	}
	setnonblocking(sock);//使用非阻塞模式

	while (1){
		// 设置服务器 地址族(ipv4) 端口 ip
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(69);
		serverAddr.sin_addr.S_un.S_addr = inet_addr(serverIP);
		int op;
		//选择要进行的操作
		printf("请选择要进行的操作：\n1.上传文件\n2.下载文件\n3.退出\n");
		scanf("%d", &op);

		if (op==1){ //上传文件
			char uploadFilename[20];
			printf("请输入要上传的文件名：\n");
			scanf("%s", uploadFilename);
			
			if (uploadFilename[0] != 0)
				upload(uploadFilename);
			else
				printf("上传文件名不合法，请重新输入！！！\n");
			printf("------上传文件开始------\n\n");
		}else if (op==2){//下载文件

			char remoteFile[20], localFile[20];
			printf("请输入要下载的文件名：\n");
			scanf("%s", remoteFile);
			
			printf("请输入要保存的文件名：\n");
			scanf("%s", localFile);
			if (remoteFile[0] != 0 && localFile[0] != 0)
				download(remoteFile, localFile);
			else
				printf("下载文件名不合法或保存文件名不合法，请重新输入！！！\n");
			printf("------下载文件开始------\n\n");
		}else if (op==3){
			printf("------退出程序------\n\n");
			break;
		}else
			printf("输入错误，请重新输入！！！\n");
	}
	fclose(logFp);//保存日志

}
