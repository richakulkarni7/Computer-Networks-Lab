#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int cli_sfd, nbytes;
	char buf[1024];
	socklen_t addr_size;
	struct sockaddr_in sa, ca;
	
	cli_sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(cli_sfd<0)
	{
		perror("socket() error!");	
	}
	sa.sin_family = AF_INET;
	sa.sin_port = htons(atoi(argv[1]));	
	sa.sin_addr.s_addr = inet_addr("172.20.1.181");
	memset(sa.sin_zero, '\0', sizeof(sa.sin_zero));
	ca.sin_family = AF_INET;
	ca.sin_port = 0;	
	ca.sin_addr.s_addr = inet_addr("172.20.1.181");
	memset(ca.sin_zero, '\0', sizeof(ca.sin_zero));
	
	bind(cli_sfd, (struct sockaddr*)&ca, sizeof(ca));

	addr_size = sizeof(sa);
	while(1)
	{
		write(1, "\nCLIENT> ",8);
		fgets(buf, 1024, stdin);
		sendto(cli_sfd, &buf, sizeof(buf), 0, (struct sockaddr*)&sa, addr_size);
		if(strcmp(buf, "bye\n")==0||strcmp(buf, "exit\n")==0)
			break;
		nbytes = recvfrom(cli_sfd, &buf, 1024,0, (struct sockaddr*)&sa, &addr_size);
		buf[nbytes] = '\0';
		if(strcmp(buf, "bye\n")==0||strcmp(buf, "exit\n")==0)
			break;
		printf("\nSERVER> %s", buf);
	}	
	return 0;	
}
