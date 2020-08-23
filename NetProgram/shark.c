#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>//地址转换
#include <sys/socket.h>//socket编程
#include <netinet/in.h>
#include <linux/ip.h>//ip头部
#include <linux/if_arp.h>//arp头部
#include <linux/tcp.h>//tcp头部
#include <linux/udp.h>//udp头部
#include <linux/icmp.h>//icmp头部
#include <linux/if_ether.h>//以太网arp数据结构

void print_mac(struct ethhdr *p);
void parse_ip(char *buf);
void parse_arp(char *buf);

int main(void){
	int sfd=socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL));//套接字编程
	//AF_PACKET 走链路层   直接利用网络驱动发送和接收报文，这种情况下SOCKET发出的报文直接送到以太网卡接口，而接收到的任何报文将直接送到应用程序
	//SOCK_RAW 原始套接字编程
	//ETH_P_ALL抓链路层的包，不包含链路层头部，需要加上以太网的头部，所有的都要
	char buf[2000];//1500 +头部14 +尾部4 
	while(1){
		memset(buf,0x00,sizeof(buf));
		int r=read(sfd,buf,2000);//从buf中读取数据
		if(r<=0){//若读取到的小于等于零，则读取失败
			break;
		}
		struct ethhdr* peth=(struct ethhdr*)buf;//以太网的头部
		print_mac(peth);//打印mac
		printf("Type: %#x\n",ntohs(peth->h_proto));//以太网上层协议类型0800或者0806

		//使用ntohs是将网络字节序转换为本机字节序来进行比较
		if(ntohs(peth->h_proto)==ETH_P_IP){//若其头部为IP  
			parse_ip(buf+sizeof(struct ethhdr));//偏移掉链路层的帧头
		}else if(ntohs(peth->h_proto)==ETH_P_ARP){//若其为ARP广播包
			parse_arp(buf+sizeof(struct ethhdr));//便宜掉链路层的帧头  
		}
	}
}

//打印mac
void print_mac(struct ethhdr *p){
	printf("%02x:%02x:%02x:%02x:%02x:%02x",p->h_source[0],p->h_source[1],p->h_source[2],p->h_source[3],p->h_source[4],p->h_source[5]);//源mac地址
	printf("<==>  %02x:%02x:%02x:%02x:%02x:%02x \n",p->h_dest[0],p->h_dest[1],p->h_dest[2],p->h_dest[3],p->h_dest[4],p->h_dest[5]);//目标mac地址
}

//打印udp
void print_udp(char* buf){
	struct udphdr *pt=(struct udphdr*)buf;
	printf("%hu : %hu",ntohs(pt->source),ntohs(pt->dest));
	printf("\n\n");
}

//打印icmp
void print_icmp(char *buf){
	struct icmphdr *imp=(struct icmphdr*)buf;
	printf("icmp");
	//打起来需要进行类型判断，所这里不打 
	//如果想打的话，需要将其头部的类型和code取出来，之后判断使用联合体之中的那个结构体
	//printf("%hu   :  seq:%hu\n",imp->echo->id,imp->echo->sequence);
}

void print_tcp(char *buf){
	struct tcphdr *pt=(struct tcphdr*)buf;
	printf("source:%hu:dest: %hu seq :%u",ntohs(pt->source),ntohs(pt->dest),ntohl(pt->seq));//源端口，目标端口 ，序列号

	if(pt->ack){
		printf("\tack_seq : %u",ntohl(pt->ack_seq));//ack为1才会有应答号
	}
	if(pt->fin){//存在即打印
		printf("\tfin");
	}
	if(pt->syn){
		printf("\tsyn");
	}
	if(pt->ack){
		printf("\tack");
	}

	printf("\n\n");
}

void parse_ip(char *buf){
	struct iphdr *phdr=(struct iphdr*)buf;
	struct in_addr ad;//in_addr 结构体里只有s_addr 装ip
	ad.s_addr=phdr->saddr;//源地址
	printf("\t%s <==> ",inet_ntoa(ad));//将ip转换为字符串
	ad.s_addr =phdr->daddr;//目标地址
	printf("%s, protocol : %hhd, tll :%hhu ,tot_len:%hu",inet_ntoa(ad),phdr->protocol,phdr->ttl,phdr->tot_len);//prorocol八位协议，ttl生存时间tot_len16位总长度
	if(phdr->protocol==IPPROTO_TCP){
		printf("\n\t\t");
		print_tcp(buf+sizeof(struct iphdr));
	}else if(phdr->protocol==IPPROTO_UDP){
		printf("\n\t\t");
		print_udp(buf+sizeof(struct iphdr));
	}else if(phdr->protocol==IPPROTO_ICMP){
		printf("\n\t\t");
		print_icmp(buf+sizeof(struct iphdr));
	}
}

void parse_arp(char *buf){
	struct arphdr* phdr=(struct arphdr*)buf;
	printf("_be16:\t%x",phdr->ar_hrd);//打印硬件地址
}	
























