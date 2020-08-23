#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

enum{BEGIN,MYIFCONF,SCANHOST,SCANPORT,SHARK,DOS,QUIT,END};

struct proc_map{
	int id;
	char *proc_name;
}maps[]={
	{BEGIN,NULL},
	{MYIFCONF,"./myifconfig"},
	{SCANHOST,"./scanhost"},
	{SCANPORT,"./scanport"},
	{SHARK,"./shark"},
	{DOS,"./dos"},
	{END,NULL}
};//功能窗口

int menu(){
	int choose;
	do{
		system("clear");
		printf("\n\n\n\n\n");
		printf("\t\t\t###############################################\n");
		printf("\t\t\t# %d. myifconfig                               #\n",MYIFCONF);
		printf("\t\t\t# %d. scanhost                                 #\n",SCANHOST);
		printf("\t\t\t# %d. scanport                                 #\n",SCANPORT);
		printf("\t\t\t# %d. shark                                    #\n",SHARK);
		printf("\t\t\t# %d. dos                                      #\n",DOS);
		printf("\t\t\t# %d. quit                                     #\n",QUIT);
		printf("\t\t\t###############################################\n");

		printf("\t\t\t请输入您的选择 > ");
		scanf("%d%*c",&choose);
		if(choose<=BEGIN||choose>=END){//若越界，则提醒要么重新输入,要么退出
			printf("菜单选项输入错误，是否重新输入？[y/n]:");
			char c;//输入是否同意重新输入的选项
			scanf("%c",&c);
			if(c=='Y'||c=='y'){//若为y或Y的话，则重新循环进行输入
				continue;
			}
			exit(0);//若为n或其他的话，则直接进行离开
		}else{//除过越界之外则都属于正常输入，跳出do，while选项 
			break;
		}
	}while(1);

	return choose;//返回用户所输入的选项
}

void do_quit(){
	printf("谢谢使用！\n");
	exit(0);
}

void do_proc(int id){
	int i;
	for(i=BEGIN;i<END;i++){
		if(id==i){
			if(fork()==0){
				sigset_t set;//创建set信号集
				sigemptyset(&set);//清空set信号集
				sigaddset(&set,SIGINT);//将SIGINT（ctrl + c）信号赋给set信号，即该位设为1
				sigprocmask(SIG_UNBLOCK,&set,NULL);//解除SIGINT信号的屏蔽

				execlp(maps[i].proc_name,maps[i].proc_name,NULL);//从所指的目录之中执行该文件
				//不使用exec是因为如果使用exec会将当前进程给替换掉，就没有办法继续进行了，所以使用execlp
				perror("execlp");//若执行错误则报错
				exit(0);//子进程执行exec出问题
			}else{
				wait(NULL);//父进程在这里等着，在子进程没有结束之前阻塞自己，直到子进程结束变为僵尸子进程
			}
		}
	}
}


int main(void){
	sigset_t set;//信号集初始化
	sigemptyset(&set);//清空信号集
	sigaddset(&set,SIGINT);//将SIGINT信号加入到set信号集之中
	sigprocmask(SIG_BLOCK,&set,NULL);//改变set信号处理函数状态，使得堵塞SIGINT信号
	//使用信号屏蔽是因为在抓包时只有crtl+c可以结束，但是这时候父子进程都收到信号了，因此只需要在父进程这里屏蔽掉SIGINT信号，而子进程要收到SIGINT信号

	while(1){//进行功能选项
		int choose =menu();
		switch(choose){
			case QUIT://若选择退出
				do_quit();
			break;
			default:
				do_proc(choose);//功能实现
			break;
		}
	}
}
	



















