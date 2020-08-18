#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

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

//#define DEBUG_STR  "ttySC1 554433"
#define Mode_W    1
#define Mode_R    2
#define Mode_RW   3
#define Version   "V1.1"
//const char *default_str = "hello serial test";
int main(int argc ,char **argv)
{
	int fd_ttySAC1;
	int fd_ttySAC5;
	int fd_file_log;
	int nread,i;
	unsigned char buff_w[1024];
	int q;
	char a=48;
	char errcnt;
	unsigned char buff_r[1024];
	int nwrite;
	int setmode;
	char *wchr;
	int format = 1;
	int boudrate = 9600;
	int enter = 0;
	int loop = 0;
	int intervalMS = 100;
	int isr_ok=0;int isw_ok=0;
	int count=0;
	char j;char o=0;
	printf("\n=============================================\n");

	for(q=0;q<sizeof(buff_w);q++)
	{  
		buff_w[q]=a++;
		if(a==97)
			a=48;
		if(q==(sizeof(buff_w)-1))
			buff_w[q++]='\0';
	}


	if((fd_ttySAC1=open_port(fd_ttySAC1,"/dev/ttySAC1"))<0){
		perror("open_port /dev/ttySAC1 error");
		return -1;
	}
	if((i=set_opt(fd_ttySAC1,boudrate,8,'N',1))<0){
		perror("set_opt /dev/ttySAC1 error");
		return -2;
	}
	if((fd_ttySAC5=open_port(fd_ttySAC5,"/dev/ttySAC5"))<0){
		perror("open_port /dev/ttySAC5 error");
		return -1;
	}
	if((i=set_opt(fd_ttySAC5,boudrate,8,'N',1))<0){
		perror("set_opt /dev/ttySAC5 error");
		return -2;
	}
	if((fd_file_log=open("/root/test_utils/test_result.txt",O_RDWR|O_APPEND,0666))<0)
	{
		printf("open /root/test_utils/test_result.txt error\n");
		exit(-1);
	}
	nwrite = sizeof(buff_w);
	write(fd_ttySAC1,buff_w,nwrite);
	sleep(2);
	memset(buff_r,0,sizeof(buff_r));
	nread=read(fd_ttySAC5,buff_r,sizeof(buff_r));
	if(!strcmp(buff_w,buff_r))
	{
		memset(buff_r,0,sizeof(buff_r));
	}
	else
	{
		//printf("buff_r=%s\n",buff_r);
		//printf("buff_w=%s\n",buff_w);
		printf("-------------------serial_485_test Fail!! .Occur in ttySAC1 send,ttySAC5 receive\n");
		write(fd_file_log,"\r\n",2);
		write(fd_file_log,"UART_485=ERR, IN RS485 send,CON6 receive;",41);
		write(fd_file_log,"\r\n",2);
		close(fd_file_log);
		return -2;
	}
	write(fd_ttySAC5,buff_w,nwrite);
	sleep(2);
	memset(buff_r,0,sizeof(buff_r));
	nread=read(fd_ttySAC1,buff_r,sizeof(buff_r));
	if(!strcmp(buff_w,buff_r))
	{
		memset(buff_r,0,sizeof(buff_r));
		memset(buff_w,0,sizeof(buff_w));
	}
	else
	{
		//printf("buff_r=%s\n",buff_r);
		//printf("buff_w=%s\n",buff_w);
		printf("--------------------serial_485_test Fail!! .Occur in ttySAC5 send,ttySAC1 receive\n");
		write(fd_file_log,"\r\n",2);
		write(fd_file_log,"UART_485=ERR, IN CON6 send,RS485 receive;",41);
		write(fd_file_log,"\r\n",2);
		close(fd_file_log);
		return -2;
	}


	msdelay(intervalMS);
	close(fd_ttySAC1);
	close(fd_ttySAC5);
	printf("-----------------------------Serial_485_test OK!\n");
	write(fd_file_log,"\r\n",2);
	write(fd_file_log,"UART_485=OK;",12);
	write(fd_file_log,"\r\n",2);
	close(fd_file_log);
	return 0;
}
