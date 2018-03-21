#include<rpc/rpc.h> //header file for RPC
#include"datetime.h" //user-generated header file for time and date functions
main(int argc, char *argv[])
{
	CLIENT *cl; //client handle variable
	char *server; //variable to hold server address
	char **sresult; //variable to hold time in readable form
	long *lresult; //variable to hold time as seconds	

	server = argv[1]; //assigning server IP
	cl = clnt_create(server, DATETIME_PROG, DATETIME_VERS, "udp"); //create client handle

	lresult = bin_time_1(NULL, cl);	//getting time as seconds from server
	sresult = str_datetime_1(lresult,cl); //getting time in readable form from server

	printf("Time: %ld seconds\n", *lresult); //printing time as seconds
	printf("Date: %s\n", *sresult); //printing time in readable form
}
