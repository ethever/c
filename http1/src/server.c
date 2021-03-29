#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
	// 创建套接字
	// int socket(int af, int type, int protocol);
	// af: 地址族(address family) 即ip地址类型 AF_INET AF_INET6
	// type: 数据传输方式/套接字类型 
	//  	SOCK_STREAM: 流格式套接字/面向链接的套接字 
	// 	SOCK_DGRAM: 数据报套接字/无连接的套接字
	// protocol: 传输协议
	// 	IPPROTO_TCP: TCP
	// 	IPPROTO_UDP: UDP
	int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 将套接字和IP、端口绑定
	// sockaddr_in: 
	// 	sa_family_t sin_family: 地址族(address family)
	// 	uint16_t sin_port: 16位TCP/UDP端口号
	// 	struct in_addr sin_addr: 32位Ip地址
	// 		In_addr_t s_addr: 32位Ipv4地址
	// 	char sin_zero[8]: 不使用4
	struct sockaddr_in serv_addr;
	// 每个字节都用0填充
	memset(&serv_addr, 0, sizeof(serv_addr));
	// 使用IPv4地址
	serv_addr.sin_family = AF_INET;
	// 具体的Ip地址
	// uint32 inet_addr(const char *p);
	// 用于将点分十进制IP转换为IPv4的32位无符号整型IP
	// 将无符号整型IP从主机端序转换为网络端字节序
	// 最终返回网络端字节序的32位无符号整数IP
	serv_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
	// 端口
	// htons: 将整型变量从主机字节序转变成网络字节序
	// 即整数在地址空间上存储方式变为高位字节放在内存的低内存地址处
	// 网络字节序是TCP/IP中规定好的一种数据表示格式 它与具体的CPU类型
	// 操作系统无关 从而可以保证数据在不同主机之间传输时能够被正确解释
	// 网络字节序采用 big-endian 模式
	serv_addr.sin_port = htons(1234);
	// 成功 返回 0
	// 失败 返回 -1
	// int bind(int sockfd, const struct sockaddr * addr, socklen_t addrlen);
	// sockfd: 套接字文件描述符 即socket函数创建的套接字文件
	// addrlen: 第二个参数所指向的结构体变量的大小
	// addr: 指向一个struct sockaddr类型的结构体变量 此结构体成员变量用于设置
	// 	 要绑定的ip和端口
	// 	 sockaddr:{
	// 	 	// 指定AF_** 表示使用什么协议族的IP格式
	//		sa_family_t sa_family;
	//		// 字符数组 用于存放ip和端口
	//		char sa_data[14]; 
	// 	 }
	bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	// 进入监听状态,等待用户发起请求
	// int listen(int sock, int backlog);
	// sock: 需要进入监听状态的套接字
	// backlog: 请求队列的最大长度
	// 
	// 通过listen函数让套接字进入被动监听状态
	// 所谓被动监听状态，是指当没有客户端请求时
	// 套接字处于睡眠状态 只有接收到客户端请求时
	// 套接字才会被唤醒来响应请求
	//
	// 请求队列:
	// 	    当套接字正在处理客户端请求时，如果有新的请求进来
	// 	    套接字是没有办法处理的 只能把它放进缓冲区 待当前
	// 	    请求处理完毕之后 再从缓冲区读取出来处理 如果不断
	// 	    有新的请求进来 它们就按照先后顺序在缓冲区中排队
	// 	    直到缓冲区满 这个缓冲区就叫做请求队列。
	// 
	// 缓冲区长度backlog: 可以通过listen函数的backlog指定 但究竟
	// 		      为多少并没有什么标准 并发量小的话可以是
	// 		      10或者20 如果将backlog设置为SOMAXCONN
	// 		      就由系统决定请求队列的长度 这是backlog
	// 		      可能是几百或者更多 当请求队列满时 服务器
	// 		      就不再就收新的请求 对于Linux 客户端会收到
	// 		      ECONNREFUSED错误 对于Windows 客户端会收到
	// 		      WSAECONNREFUSED错误
	//
	// 注意: listen函数只是让套接字进入监听状态 并没有真正接受客户端请求
	// 	 listen函数后面的代码会继续执行 直到遇到accept函数 accept()
	// 	 会阻塞程序执行 直到有新的请求到来。
	listen(serv_sock, 20);

	// 接受客户端请求
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size = sizeof(clnt_addr);
	// int accept(int sock, struct sockaddr *addr, socklen_t *addrlen);
	// 当套接字处于监听状态时，可以通过accept函数来接收客户端请求
	// sock: 服务端套接字
	// addr: IP地址和端口信息
	// addrlen: addr长度
	//
	// accept函数返回一个新的套接字来和客户端通信 addr保存了客户端的IP地址和端口号信息
	// 而sock是服务端的套接字 后面和客户端通信时，要使用新的套接字而不是原来服务器端的
	// 套接字
	int clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

	// 向客户端发送数据
	// char str[] = "GET / HTTP/1.1\r\nHost: 119.28.83.146\r\n\r\n hahahahhahah";
	char str[] = "HTTP/1.1 200 OK\r\ncontent-type: text/html; charset=utf-8\r\n\r\nhahahahahaha";
	write(clnt_sock, str, sizeof(str));

	// 关闭套接字
	// 关闭当前请求
	close(clnt_sock);
	// 关闭服务端套接字
	close(serv_sock);
	return 0;
}
