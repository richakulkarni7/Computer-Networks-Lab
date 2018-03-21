#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define SA struct sockaddr

int main(int argc, char* argv[])
{
	int sockfd, len;
	char ip[30], mac[30];
	struct sockaddr_in servaddr;
	int choice;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[1]));
	servaddr.sin_addr.s_addr = inet_addr("172.17.0.34");

	printf("\nARP AND RARP SIMULATION\n");
	printf("Press 1 for ARP, 2 for RARP, 0 to quit\n");
	do
	{
		printf("\nEnter choice: ");
		scanf("%d",&choice);
		int l = snprintf(NULL, 0, "%d", choice);
		char c[l+1];
		snprintf(c, l+1, "%d", choice);
		sendto(sockfd, c, sizeof(c), 0, (SA*)&servaddr, sizeof(servaddr));
		if(choice==1)
		{
			printf("\nARP SIMULATION\n");
			printf("Enter IP address: ");
			scanf("%s", ip);
			sendto(sockfd, ip, sizeof(ip), 0, (SA*)&servaddr, sizeof(servaddr));
			len = sizeof(servaddr);
			recvfrom(sockfd, mac, sizeof(mac), 0, (SA*)&servaddr, &len);
			printf("MAC address is: %s\n", mac);
		}

		else if(choice==2)
		{
			printf("\nRARP SIMULATION\n");
			printf("Enter MAC address: ");
			scanf("%s", ip);
			sendto(sockfd, mac, sizeof(mac), 0, (SA*)&servaddr, len);
			recvfrom(sockfd, ip, sizeof(ip), 0, (SA*)&servaddr, &len);
			printf("IP address is: %s\n", ip);
		}
		bzero(mac, sizeof(mac));
	}while(choice);

	return 0;
}
