#include <rpc/rpc.h>
#include "square.h"

main(int argc, char *argv[])
{
	CLIENT *cl;
	char *server;
	int n;
	int *result;

	server = argv[1];
	cl = clnt_create(server, SQUARE_PROG, SQUARE_VERS, "udp");
	
	printf("Enter a number: ");
	scanf("%d", &n);
	int *n_ptr = &n;
	*result = square_1_svc(n_ptr, cl);
	printf("Result: %d", *result);
	
}
