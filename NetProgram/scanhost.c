#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/time.h>
// 扫描主机号，看看那个是开的
#define PACK_LEN 72


void make_icmp_packet(struct icmp* picmp,int len,int n);
u_short checksum(u_short *data,int len);
void tvsub(struct timeval *out,struct timeval *in);


int main(void){
	char buf[32]="39.99.249";
	printf("请输入你想要扫描的网段（xxx.xxx.xxx）：");
	scanf("%s",buf);
	int i,j;
	char ip_addr[32];

	int sfd=socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);//创建原始套接字，专门接收icmp报文
	//原始套接字，不需要三次握手，因此和udp一样，直接使用sendto
	if(sfd==-1)perror("socket"),exit(1);

	for(i =1; i <255 ;i++){//不ping 0是因为0是广播包，所以从1开始
		memset(ip_addr,0x00 ,32);
		sprintf(ip_addr,"%s.%d", buf, i);//拼出来的ip地址，前面的是网段，后面的是主机号
		printf("正在扫描：%s\n",ip_addr);
		char send_buf[PACK_LEN];//定义传送数据
		struct sockaddr_in addr;
		memset(&addr,0x00,sizeof(addr));
		addr.sin_family=AF_INET;
		inet_aton(ip_addr,&addr.sin_addr);//网络层是没有端口号的
		for(j=0;j<3;j++){
			make_icmp_packet((struct icmp*)send_buf,PACK_LEN,j);//组装icmp报文
			if(sendto(sfd,send_buf,PACK_LEN,0,(struct sockaddr*)&addr,sizeof(addr))==-1){//发送  因需要发送到目标地址，因此创建addr
				perror("sendto"),exit(1);
			}
			fd_set rest;//df_set类型的数据
			FD_ZERO(&rest);
			FD_SET(sfd,&rest);
			struct timeval tv;///超时结构体
			tv.tv_sec =0;
			tv.tv_usec= 200*1000;//定义超时的时间
			while(1){
				int ready;
				if((ready=select(sfd+1,&rest,NULL,NULL,&tv))<=0) {//小于等于零超时，则离开这个循环，如果没收到，则跳出循环重新进行，收到之后再进行recvfrom操作
					break;//用select的主要目的是为了超时
				}
				char recv_buf[2048];//收数据的空间
				if(recvfrom(sfd,recv_buf,2048,0,NULL,NULL)==-1)exit(0);//收数据  如果指定从那个地方的数据来，则将后面的NULL进行修改，这里不需要则不进行改
				//因为避免recvfrom出现没收到或者超时的现象，在前面使用select
				struct ip *pip=(struct ip*)recv_buf;//  icmp缺省头部里面包含着ip 而tcp不包含，因此会使用int op= 1;setsockopt(sfd,IPPROTO,ip_hdrincl,&op,sizeof(op));将ip头部加入到套接字里面
				int len=pip->ip_hl<<2;//获取首部长度 ，因此ip里的首部长度只能够是1或者是0，而hdlen是四个字节，所以取出来ip首部大小需要乘以4
				if(pip->ip_src.s_addr==addr.sin_addr.s_addr){//看别人发给我们的源ip和我们的目标ip相等，相等在进行处理，不相等则不进行处理
					struct icmp *picmp=(struct icmp*)(recv_buf+len);//取出icmp报文，指针向后移动ip头部大小的距离
					if(picmp->icmp_type==ICMP_ECHOREPLY){//对方收到给我们返回的应答的宏 是ICM_ECHOREPLY
						printf("\t%s   ",inet_ntoa(pip->ip_src));//对方机器的ip
						struct timeval curt;//定义时间
						gettimeofday(&curt,NULL);//获取当前时间
						tvsub(&curt,(struct timeval*)(picmp->icmp_data));//计算往返的时间，参数是（当前的时间，对方给我们应答的时间（也就是我们发送的时间icmp里的时间））
						printf("\tttl:%hhu rrt:%d\n",pip->ip_ttl,curt.tv_sec+curt.tv_usec/1000);//把相差的时间给打印出来
					}
					goto lab;//走到ip相等这里面后表示成功并且完成了操作我们则需要直接跳出最上面for循环 goto
				}
			}
		}
	lab:;//目的是一个空语句，目的不让lab报错
	}
}

void make_icmp_packet(struct icmp* picmp,int len,int n){ //组装icmp报文
	memset(picmp,0x00,len);
	gettimeofday((struct timeval*)(picmp->icmp_data),NULL);//数据里面装的是当前的时间
	picmp->icmp_type=ICMP_ECHO;//报的类型，（发送请求的宏 ICMP_ECHO）
	picmp->icmp_code=0;//编号
	picmp->icmp_cksum=0;//检验和 先清空后面使用校验和算法来进行计算
	picmp->icmp_id =getpid();//标识符，也就是当前进程的进程id
	picmp->icmp_seq=n;//序号
	picmp->icmp_cksum=checksum((u_short*)picmp,len);//算法
}


u_short checksum(u_short *data,int len){
	u_long sum=0;

	for(;len>1;len-=2){//算法核心思想:以16位为单位进行相加，之后再求反码
		sum+=*data++;
		if(sum&0x80000000){//溢出的处理方式
			sum=(sum&0xffff)+(sum>>16);
		}
	}

	if(len==1){//最后剩下一个
		u_short i=0;
		*(u_char*)&i=*(u_char*)data;
		sum+=i;
	}

	while(sum>>16){//高16位如果有1，继续计算，因为我们只需要低的16位
		sum=(sum&0xffff)+(sum>>16);
	}
	return (sum==0xffff)?sum:~sum;
}

void tvsub(struct timeval *out, struct timeval *in){
	out->tv_sec-=in->tv_sec;
}

















