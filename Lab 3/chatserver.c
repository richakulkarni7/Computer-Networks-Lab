#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int ser_sfd, nbytes, addr_len, len, i;
	char buf[1024];
	struct sockaddr_in sa, ca;	
	ser_sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(ser_sfd<0)
	{
		perror("socket() error!");
	}
	sa.sin_family = AF_INET;
	sa.sin_port = htons(atoi(argv[1]));	
	sa.sin_addr.s_addr = inet_addr("172.20.1.181");
	len = sizeof(sa);
	bind(ser_sfd, (struct sockaddr*)&sa,len);
	addr_len  = sizeof(ca);

	while(1)
	{
		
		nbytes = recvfrom(ser_sfd, &buf, 1024, 0, (struct sockaddr *)&ca, &addr_len);
		if(strcmp(buf, "bye\n")==0||strcmp(buf, "exit\n")==0)
			break;
		write(1, "\nCLIENT> ", 8);
		buf[nbytes] = '\0';
		printf("%s", buf);
		write(1, "\nSERVER> ", 8);
		fgets(buf, 1024, stdin);
		sendto(ser_sfd, &buf, nbytes, 0, (struct sockaddr *)&ca, addr_len);
		if(strcmp(buf, "bye\n")==0||strcmp(buf, "exit\n")==0)
			break;
	}
	
	return 0;	
}
