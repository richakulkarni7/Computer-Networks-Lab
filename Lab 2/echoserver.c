#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	int sfd, newsfd, s, len, n, i,j;
	char buf[100];
	struct sockaddr_in servaddr, clientacc, client;
	
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd<0)
	{
		perror("socket() error!");	
		exit(-1);
	}
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[1]));	
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	s = bind(sfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	if(s<0)
	{
		perror("bind() error!");
		exit(-1);
	}

	s = listen(sfd, 5);
	
	if(s<0)
	{
		perror("listen() error!");
		exit(-1);
	}

	printf("\n---SERVER WAITING FOR CLIENT REQUEST---");
	newsfd = accept(sfd, (struct sockaddr*)&clientacc, &len);
	if(newsfd<0)
	{
		perror("accept() error!");
		exit(-1);
	}

	printf("\n---CONNECTED TO CLIENT---");
	for(j = 1; j<=10; j++)
	{
		
		n = recv(newsfd, &buf, 100, 0);
		buf[n] = '\0';
		printf("\nMESSAGE FROM CLIENT: %s", buf);
		for(i = 0; buf[i]!='\0' ; i++)
			buf[i] = toupper(buf[i]);
		send(newsfd, &buf, n, 0);
	}
	close(sfd);
	close(newsfd);
	
	return 0;	
}
