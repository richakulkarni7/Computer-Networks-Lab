long *bin_time_1_svc(NULL) //procedure to return time as binary string
{
	static long timeval; //variable to hold binary time value as seconds
	long time(); //function to get time as seconds
	timeval = time((long *) 0); //getting time as seconds
	return &timeval; //return time as seconds
}

char **str_datetime_1_svc(long *lresult) //procedure to return date and time in readable form
{
	static char* time; //variable to hold time in readable form
	char* ctime(); //function to get time in readable form
	time = ctime(lresult); //getting time in readable form
	return &time; //return time in readable form
}
