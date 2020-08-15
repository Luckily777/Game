//抓包测试

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
// 如果使用库的ip头部，则需要加上#include <netinet/ip.h> 这个头文件
//id头部

struct iphdr {
	unsigned int ihl : 4;
	unsigned int version : 4;
	u_int8_t tos;
	u_int16_t tot_len;
	u_int16_t id;
	u_int16_t frag_off;
	u_int8_t ttl;
	u_int8_t protocol;
	u_int16_t check;
	u_int32_t saddr;
	u_int32_t daddr;
};

int main(void) {
	int sfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	int op = 1;
	setsockopt(sfd, IPPROTO_IP, IP_HDRINCL, &op, sizeof(op));
	char buf[1501] = {};
	while (1) {
		memset(buf, 0x00, sizeof(buf));
		int r = read(sfd, buf, 1500);
		struct iphdr* p = (struct iphdr*)(buf);
		printf("version: %x\n", p->version);
		struct in_addr ad;
		ad.s_addr = p->saddr;
		printf("\t%s<=>", inet_ntoa(ad));
		ad.s_addr = p->daddr;
		printf("%s\n", inet_ntoa(ad));
	}
}
