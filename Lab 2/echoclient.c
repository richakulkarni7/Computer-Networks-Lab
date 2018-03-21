#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	int sfd, newsfd, s, len, n, i,j=0;
	char buf[21];
	struct sockaddr_in servaddr, serveracc;
	
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd<0)
	{
		perror("socket() error!");	
//		exit();
	}
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[1]));	
	servaddr.sin_addr.s_addr = inet_addr("172.20.1.181");

	s = connect(sfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	if(s<0)
	{
		perror("connect() error!");
//		exit();
	}

	for(i = 1; i<=10; i++)
	{
//		for(j = 0; j!='\0'; j++)
//			buf[j] = "";
		write(1, "\nYOUR MESSAGE: ",14);
		n = read(0, &buf, 100);
		send(sfd, &buf, n, 0);
		n = recv(sfd, &buf, 20,0);
		write(1, "RECEIVED FROM SERVER: ", 22);
		write(1, &buf, n);
	}
	close(newsfd);
	
	return 0;	
}
