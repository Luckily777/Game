#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//ifconfig 读取网卡的一些信息

int main(void){
	struct ifreq ir[5];//装设备的名字 并且可以装5个
	struct ifconf conf;//装所有设备的清单
	conf.ifc_len =sizeof(ir);//缓存的大小，是我们开始给的
	conf.ifc_req=ir;//把缓存放到ifconf的buf里

	int sfd =socket(AF_INET,SOCK_STREAM,0);//网络描述符
	ioctl(sfd,SIOCGIFCONF,&conf);//获取到接口的列表装入到conf里
	int cnt =conf.ifc_len/sizeof(struct ifreq);//实际缓存的大小有多大，就是实际的除以ir一个的大小
	printf("cnt =%d\n",cnt);//打印实际设备个数
	int i;
	for(i=0;i<cnt;i++){
		printf("%s\n",ir[i].ifr_name);//打印设备的名字
		struct ifreq iq;
		memcpy(iq.ifr_name,ir[i].ifr_name,sizeof(ir[i].ifr_name));//要获取ip需要按照设备名字去查找，所以我们将当前设备名字拷贝到iq结构体的name中即可
		ioctl(sfd,SIOCGIFDSTADDR,&iq);//获取ip地址
		struct sockaddr_in *addr =(struct sockaddr_in*)&iq.ifr_dstaddr;//是因为回来的地址信息是struct sockaddr类型，因此我们需要定义这样一个类型将其拉回来
		printf("\tip :%s\t",inet_ntoa(addr->sin_addr));//打印获取到的ip地址

		ioctl(sfd,SIOCGIFNETMASK,&iq);//获取子网掩码 通过不同的参数获取到的信息装到不同的联合体中
		addr =(struct sockaddr_in*)&iq.ifr_netmask;//把子网掩码也拉回去
		printf("\tnetmask :%s\t",inet_ntoa(addr->sin_addr));//打印子网掩码

		int ret=ioctl(sfd,SIOCGIFBRDADDR,&iq);//获取广播地址
		addr =(struct sockaddr_in*)&iq.ifr_netmask;//把广播地址也拉回去
		printf("\tbrdcast :%s\n",inet_ntoa(addr->sin_addr));//打印广播地址

		ioctl(sfd,0x8921,&iq);//获取MTU
		printf("\tMTU :%d\n",iq.ifr_mtu);//mtu不是ip地址，不需要转，直接打印即可

		ioctl(sfd,SIOCGIFHWADDR,&iq);//获取MAC地址
		char buf[6];
		memcpy(buf,iq.ifr_hwaddr.sa_data,6);//将它里面的六个拷贝到buf之中
		printf("\tHDaddr : %02X:%02X:%02X:%02X:%02X:%02X\n\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);//打印buf也就是mac的地址
	}
	printf("按任意键按继续...\n");
	getchar();
}



