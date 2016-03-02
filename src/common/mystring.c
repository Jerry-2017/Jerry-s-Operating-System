#include "include/common/common.h"

uint8_t c2i(char c)
{
	if (c>='0' && c<='9') return c-'0';
	else return -1;
}

char i2c(uint32_t i)
{
	if (i>=0 && i<=9) return i+'0';
	else return 0;
}

char x2c(uint32_t i)
{
	if (i>=0 && i<=9) return i+'0';
	else if (i>=10 && i<=15) return i+'a'-10;
	else return 0;
}

int u2s(uint32_t val, char * string)
{
	int i=0;
	int s=i;
	while (val!=0 && i<MAX_STRING)
	{
		int j=val%10;
		string[i++]=i2c(j);
		val/=10;
	}
	int e=i-1;
	while (s<e)
	{
		int t=string[s];
		string[s]=string[e];
		string[e]=t;
		s++;
		e--;
	}
	string[i]='\0';
	return i;
}

int i2s(int val, char * string)
{
	int i=0;
	if (val<0) {
		string[i++]='-';
		val=-val;
	}
	int s=i;
	while (val!=0 && i<MAX_STRING)
	{
		int j=val%10;
		string[i++]=i2c(j);
		val/=10;
	}
	int e=i-1;
	while (s<e)
	{
		int t=string[s];
		string[s]=string[e];
		string[e]=t;
		s++;
		e--;
	}
	string[i]='\0';
	return i;
}

int x2s(int val, char * string)
{
	int i=0;
	int s=i;
	while (val!=0 && i<MAX_STRING)
	{
		int j=val%16;
		string[i++]=x2c(j);
		val/=16;
	}
	int e=i-1;
	while (s<e)
	{
		int t=string[s];
		string[s]=string[e];
		string[e]=t;
		s++;
		e--;
	}
	string[i]='\0';
	return i;
}

int s2i(char *string)
{
	int i=0;
	int j=1,k=0;
	if (string[0]=='-')
	{
		j=-1;
		i++;
	}
	while (string[i]!='\0' && i<MAX_STRING)
	{
		k=k*10+c2i(string[i]);
		i++;
	}
	k=k*j;
	return k;
}

int scopy(const char * src, char *dst)
{
	int i=0;
	while (i<MAX_STRING && src[i]!='\0')
	{
		dst[i]=src[i];
		i++;
	}
	dst[i]='\0';
	return i;
}
