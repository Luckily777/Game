#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
//扫描到主机号之后，看看那些端口是打开的核心思想：(全连接)直接使用connet连接，能够连上是开的，不能则是关的
int tcp_connet(char *ip,int i){
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(i);//将本地字节序转换为网络字节序 端口
	inet_aton(ip,&addr.sin_addr);
	if(connect(sfd,(struct sockaddr*)&addr,sizeof(addr))==-1){
		return 0;//若连接失败，则返回
	}else{
		close(sfd);//连接成功则代表扫描到端口， 关闭sfd套接字
	}
	return 1;
}

int main(void){
	char ip[32]={};
	int start_port;
	int end_port;
	printf("ip:");
	scanf("%s",ip);
	printf("start:");
	scanf("%d",&start_port);
	printf("end:");
	scanf("%d",&end_port);

	int i;
	for(i=start_port;i<=end_port;i++){
		if(tcp_connet(ip,i)==1){//等于1表示端口是通的
			struct servent *ps=getservbyport(htons(i),"tcp");//每个端口所对应的服务 ，getservbyport()给一个端口是要端口的tcp还是udp，就会返回这样一个结构体,这个结构体之中就有名字，别名，端口号
			printf("%d,%s",i,(ps==NULL)?"unkown":ps->s_name);//把对应的端口和名字打印出来
		}
	}
}

