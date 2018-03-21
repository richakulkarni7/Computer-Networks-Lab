#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define SA struct sockaddr

struct IPmac
{
	char ip[100];
	char mac[100];
};

int main(int argc, char* argv[])
{
	int sockfd, len, i;
	struct sockaddr_in servaddr;
	char buff[30], temp[30], ip[30], mac[30];
	int choice;
	char c[2];

	struct IPmac in[3] =
	{
		{"10.1.1.8","44:dd:22:11:33"},
		{"127.0.0.1","33:aa:fe:4e:2d"},
		{"10.1.8.5","23:a3:5d:33:9d"}
	};

	printf("IP\t\tMAC\n");
	for(i = 0; i < 3; i++)
		printf("%s\t\t%s\n", in[i].ip, in[i].mac);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[1]));
	servaddr.sin_addr.s_addr = INADDR_ANY;

	bind(sockfd, (SA*)&servaddr, sizeof(servaddr))
;
	do
	{
	len = sizeof(servaddr);
	recvfrom(sockfd, c, sizeof(c), 0, (SA*)&servaddr, &len);
	choice = atoi(c);
		if(choice==1)
		{
			printf("\nWaiting to receive IP...\n");
			recvfrom(sockfd, ip, sizeof(ip), 0, (SA*)&servaddr, &len);
			printf("Received IP: %s\n", ip);
			for(i = 0; i < strlen(ip); i++)
				temp[i] = ip[i];
			temp[i] = '\0';
			for(i = 0; i < 3; i++)
				if(strcmp(temp, in[i].ip)==0)
				{
					strcpy(mac, in[i].mac);
					break;
				}
			printf("MAC Address is: %s\n", mac);
			sendto(sockfd, mac, sizeof(mac), 0, (SA*)&servaddr, len);
			bzero(mac, sizeof(mac));
		}

		else if(choice==2)
		{
			printf("\nWaiting to receive MAC...\n");
			recvfrom(sockfd, mac, sizeof(mac), 0, (SA*)&servaddr, &len);
			printf("Received MAC: %s\n", mac);
			for(i = 0; i < strlen(mac); i++)
				temp[i] = mac[i];
			temp[i] = '\0';
			for(i = 0; i < 3; i++)
				if(strcmp(temp, in[i].mac)==0)
				{
					strcpy(ip, in[i].ip);
					break;
				}
			printf("IP Address: %s\n", ip);
			sendto(sockfd, ip, sizeof(ip), 0, (SA*)&servaddr, len);
			bzero(mac, sizeof(mac));
		}
	}while(choice);
	return 0;

}