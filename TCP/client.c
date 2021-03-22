#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){
	// 创建套接字
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	// 向服务器(特定的端口和Ip)发起请求
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(1234);
	// int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);
	// sockfd: 通过socket函数产生的文件描述符
	// serv_addr:
	// 	sockaddr_in: 要连接的IP4地址和端口
	// 	sockaddr_in6: 要连接的IPv6地址和端口
	// addrlen: serv_addr长度
	//
	// 阻塞模式下connect的返回值和参数设置:
	// 阻塞和非阻塞不是connect函数的属性
	// 而是通过socket函数获取的文件描述符
	// 所指向的抽象文件的属性 所以需要通过操作socket
	// 获取文件描述符fd(file description)来对其设置为
	// 非阻塞 默认情况下socket文件是阻塞的
	//
	// 建立阻塞的socket文件描述符时
	// 调用connect函数即完成了整个过程
	// 连接成功返回0 连接失败返回-1
	// 返回-1时表明该连接发生了错误 即没有
	// 成功建立连接 并会将发生的错误记录在
	// 一个全局变量errno中 errno的取值有...
	//
	// 注意: inet_pton 和 socket 函数都有可能调用失败 
	// 需要对其返回值处理
	//
	// 非阻塞模式下connect的返回值和参数设置
	// 对于非阻塞的connect连接，其不会在调用connect时进行阻塞
	// 而是立即返回 如果返回0 说明调用connect的时候会没来得及
	// 让connect返回便已经建立了连接 如果返回-1 errno会记录一个
	// 错误码 如果该错误码为EINPROGRESS 则说明该连接还正在建立
	// 并不能说明该连接出错 一个非阻塞connect的样例:
	//
	// int flag;
	// int fd = socket(AF_INET, SOCK_STREAM, 0);
	// 获取文件描述符属性
	// flag = fcntl(connect_fd, F_GETFLK, 0);
	// 将文件描述符设置为非阻塞
	// fcntl(connect_fd, F_SETFLK, flag | 0_NONBLOCK);
	// struct sockaddr_in addr = {0};
	// addr.sin_family = AF_INET;
	// addr.sin_port = htons(80);
	// inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
	// for(;;){
	//	flag = connect(fd, &addr, len);
	//	if(flag == 0){
	//		printf("connect success!\n");
	//		break;
	//	} else {
	//		if(errno != EINPROGRESS){
	//			printf("connect error!" "errno: %d \n ", errno);
	//			break;
	//		} else {
	//			printf("connection is being established \n")
	//			sleep(1);
	//			continue;
	//		}
	//	}
	//
	// }
	// 
	//
	//
	// fcntl 函数:
	// int fcntl(int fd, int cmd, ...);
	// 常见用法
	// 1. 复制一个文件描述符
	// 2. 获取或设置文件状态标志
	// 3. 获得、设置文件记录锁
	//
	// 获得、设置记录锁 (cmd = F_GETLK, F_SETLK, F_SETLKW)
	// F_GETLK: 获得上锁的状态
	// F_SETLK: 非阻塞上锁
	// F_SETLKW: 阻塞上锁
	//
	//
	connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	// 读取服务器传回的数据
	char buffer[40];
	read(sock, buffer, sizeof(buffer) - 1);
	printf("Message from server: %s\n", buffer);

	// 关闭套接字
	close(sock);
	

	return 0;
}
