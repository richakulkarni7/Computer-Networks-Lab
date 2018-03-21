#include <iostream>
#include <string.h>
using namespace std;

int hextodeci (string);

void bigendian(string hexaddr)
{
	cout<<"\nBIG-ENDIAN";
	cout<<"\nHexadecimal format: "<<hexaddr;
	cout<<"\nDecimal format: "<<hextodeci(hexaddr);
}

void littleendian(string hexaddr)
{
	cout<<"\n\nLITTLE-ENDIAN";
	string target = "";
	int n = hexaddr.size();
	for(int i = n-2; i >= 0; i = i-2)
	{
		target += hexaddr[i];
		target += hexaddr[i+1];
	}	
	cout<<"\nHexadecimal format: "<<target;
	cout<<"\nDecimal format: "<<hextodeci(target)<<endl;
	
}

int hextodeci(string hexaddr)
{
	int sum = 0, p = 1;
	int n = hexaddr.size();
	int k = 1;
	for(int i = n-1; i >= 0; i--, k = k*16)
	{
		if (int(hexaddr[i])>=65)
		{
			sum += (int(hexaddr[i]) - 55) * k;
		}
		else
			sum += (int(hexaddr[i])-48) * k;
	}
	return sum;
}

int main()
{
	string hexaddr = "56AB";
	bigendian(hexaddr);
	littleendian(hexaddr);
	return 0;
}
