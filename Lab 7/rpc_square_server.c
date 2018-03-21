int *square_1_svc(int n)
{
	static int result;	
	result = n*n;
	return &result;
}
