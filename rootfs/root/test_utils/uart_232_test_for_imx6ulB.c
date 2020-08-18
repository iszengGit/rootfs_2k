#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

char buff_w[1024];
char buff_r[1024];

int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio,oldtio;
	if  ( tcgetattr( fd,&oldtio)  !=  0) 
	{ 
		perror("SetupSerial 1");
		return -1;
	}
	bzero( &newtio, sizeof( newtio ) );
	newtio.c_cflag  |=  CLOCAL | CREAD; 
	newtio.c_cflag &= ~CSIZE; 

	switch( nBits )
	{
		case 7:
			newtio.c_cflag |= CS7;
			break;
		case 8:
			newtio.c_cflag |= CS8;
			break;
	}

	switch( nEvent )
	{
		case 'O':                     //奇校验
			newtio.c_cflag |= PARENB;
			newtio.c_cflag |= PARODD;
			newtio.c_iflag |= (INPCK | ISTRIP);
			break;
		case 'E':                     //偶校验
			newtio.c_iflag |= (INPCK | ISTRIP);
			newtio.c_cflag |= PARENB;
			newtio.c_cflag &= ~PARODD;
			break;
		case 'N':                    //无校验
			newtio.c_cflag &= ~PARENB;
			break;
	}

	switch( nSpeed )
	{
		case 300:
			cfsetispeed(&newtio, B300);
			cfsetospeed(&newtio, B300);
			break;	
		case 600:
			cfsetispeed(&newtio, B600);
			cfsetospeed(&newtio, B600);
			break;		
		case 1200:
			cfsetispeed(&newtio, B1200);
			cfsetospeed(&newtio, B1200);
			break;			
		case 2400:
			cfsetispeed(&newtio, B2400);
			cfsetospeed(&newtio, B2400);
			break;
		case 4800:
			cfsetispeed(&newtio, B4800);
			cfsetospeed(&newtio, B4800);
			break;
		case 9600:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
		case 19200:
			cfsetispeed(&newtio, B19200);
			cfsetospeed(&newtio, B19200);
			break;       
		case 38400:
			cfsetispeed(&newtio, B38400);
			cfsetospeed(&newtio, B38400);
			break;  
		case 57600:
			cfsetispeed(&newtio, B57600);
			cfsetospeed(&newtio, B57600);
			break;      
		case 115200:
			cfsetispeed(&newtio, B115200);
			cfsetospeed(&newtio, B115200);
			break;
		default:
			printf("sorry! [%d bps] is not support ,Set default 9600bps now!\n",nSpeed);
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
	}
	if( nStop == 1 )
	{
		newtio.c_cflag &=  ~CSTOPB;
	}
	else if ( nStop == 2 )
	{
		newtio.c_cflag |=  CSTOPB;
	}
	newtio.c_cc[VTIME]  = 0;
	newtio.c_cc[VMIN] = 0;
	tcflush(fd,TCIFLUSH);
	if((tcsetattr(fd,TCSANOW,&newtio))!=0)
	{
		perror("com set error");
		return -1;
	}
	printf("set done!\n");
	return 0;
}

int open_port(int fd,char *dev)
{
	//char *dev[]={"/dev/ttyO1","/dev/ttyO2","/dev/ttyO3"};
	long  vdisable;
	fd = open( dev, O_RDWR|O_NOCTTY); //open("/dev/tttyS0",O_RDWR | O_NOCTTY);  //O_NDELAY
	if (-1 == fd)
	{
		perror("Can't Open Serial Port");
		return(-1);
	}
	else 
	{
		printf("open %s ok\n",dev);
	}

	if(fcntl(fd, F_SETFL, 0)<0)
	{
		printf("fcntl failed!\n");
	}
	else
	{
		printf("fcntl=%d\n",fcntl(fd, F_SETFL,0));
	}
	if(isatty(STDIN_FILENO)==0)
	{
		printf("standard input is not a terminal device\n");
	}
	else
	{
		printf("isatty success!\n");
	}
	printf("fd-open=%d\n",fd);
	return fd;
}

void msdelay(int val){
	while(val--)usleep(1000);
}
int rw_test(int fd)
{

	int nwrite;
	int nread,i;
	char a=48;
	int q;
	memset(buff_w,0,1024);
	for(q=0;q<1021;q++)
	{  buff_w[q]=a++;
		if(a==97)
			a=48;
	}
	buff_w[q++] = 0x0d;
	buff_w[q++] = 0x0a;
	memset(buff_r,0,1024);

	nwrite = strlen(buff_w);
	write(fd,buff_w,nwrite);
	msdelay(100);
	nread=read(fd,buff_r,nwrite);
	//printf("nread=%d\n",nread);
	//printf("buff_r=%s\n",buff_r);
	if(nread>0)
	{

		buff_r[nread] = '\0';
		//printf("%s\n",buff_r);
		if(!strcmp(buff_w,buff_r))
		{
			memset(buff_r,0,1024);
			return 0;
		}
		else
		{
			printf("err:   rec and send buff diff!!!\n");
			return -1;
		}
	}
	else
	{
		printf("err:   receive nothing !!!\n");
		return -1;
	}
	

}

//#define DEBUG_STR  "ttySC1 554433"
#define Mode_W    1
#define Mode_R    2
#define Mode_RW   3
#define Version   "V1.1"
//const char *default_str = "hello serial test";
int main(int argc ,char **argv)
{
	int fd;
	char buff[1024];
	int i;
	char errcnt=0;
	char *is_ASS[3]={"/dev/ttySAC2","/dev/ttySAC3","/dev/ttySAC4"};
	char err_port[512];
	int setmode;
	char *wchr;
	int format = 0;
	int boudrate = 115200;
	int enter = 0;
	int loop = 0;
	int intervalMS = 100;
	int isr_ok=0;int isw_ok=0;
	int count=0;
	memset(err_port,'\0',sizeof(err_port));

	printf("boudrate = %d\n",boudrate);
	printf("interval : %d ms\n",intervalMS);
	loop = 1;
	format = 1;
	char j=0;
	char k=0;
	while(loop){
		if(j==3)
		{
			printf("test finish !\n");
			return 0;
		}
		if((fd=open_port(fd,is_ASS[j]))<0){
			perror("open_port error");
			return -1;
		}
		printf("fd=%d\n",fd);
		if((i=set_opt(fd,boudrate,8,'N',1))<0){
			perror("set_opt error");
			return -2;
		}
		for(count=0; rw_test(fd)==0; count++)
		{
			if(count>=10)
			{
				printf("--------------------------------%s--test ok!!!!!!!!\n",is_ASS[j]);
				close(fd);
				j++;
				if(j>=3)loop=0;
				break;
			}
		}
		if(count<10)
		{
			char tmp_buff[10];
			errcnt++;
			printf("err:  timeout!------%s not alive !!!\n",is_ASS[j]);
			if(0==strcmp("/dev/ttySAC2",is_ASS[j]))
				sprintf(err_port,"%s CON3",err_port,is_ASS[j]);
			else if(0==strcmp("/dev/ttySAC3",is_ASS[j]))
				sprintf(err_port,"%s CON4",err_port,is_ASS[j]);
			else if(0==strcmp("/dev/ttySAC4",is_ASS[j]))
				sprintf(err_port,"%s CON5",err_port,is_ASS[j]);
			close(fd);
			j++;
			if(j>=3)loop=0;
		}
	}
	printf("err_port=%s\n",err_port);
	if(errcnt!=0)
	{
		int fd_file,len;
		char buff[100];
		//if((fd=open("/root/test_utils/test_result.txt",O_CREAT|O_APPEND,O_RDWR))<0)
		if((fd_file=open("/root/test_utils/test_result.txt",O_RDWR|O_APPEND,0666))<0)
		{
			printf("open /root/test_utils/test_result.txt error\n");
			exit(-1);
		}
		//len=strlen(err_port);
		//printf("len=%d\n",len);
		write(fd,"\r\n",2);
		write(fd,"UART_232=ERR,",12);
		write(fd,err_port,strlen(err_port));
		write(fd,";",1);
		write(fd,"\r\n",2);
		//read(fd,buff,sizeof(buff));
		//printf("buff=%s\n",buff);
		close(fd_file);
		
		
	}
	return 0;
}
