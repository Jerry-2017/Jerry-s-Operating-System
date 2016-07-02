#include "include/common/common.h"
#include "include/common/mystring.h"
#include "include/device/com.h"

void printk(const char* format,...)
{
	va_list ap;   
	
	char ch;int tp;char *tp1;

	char rst[MAX_STRING];int rl=0;
	va_start(ap,format);
	int i=0;
	while (format[i]!='\0' && i<MAX_STRING)
	{
		switch (format[i])
		{
			case '%':
			{
				i++;
				switch(format[i])
				{
					case 'c':
					{
						ch=(char) va_arg(ap,int);
						rst[rl++]=ch;
						break;
					}
					case 'd':
					{
						tp= va_arg(ap,int);
						rl+=i2s(tp,rst+rl);
						break;
					}
					case 'x':
					{
						tp= va_arg(ap,int);
						rst[rl]='0';
						rst[rl+1]='x';
						rl+=2;
						rl+=x2s(tp,rst+rl);
						break;
					}		
					case 's':
					{
						tp1= va_arg(ap,char *);
						rl+=scopy(tp1,rst+rl);
						break;
					}
					case '%':
					default:
					{
						rst[rl++]=format[i];
						break;
					}
				}
				break;
			}
			default:
			{
				rst[rl++]=format[i];
				break;
			}
		}
		i++;
	}
	va_end(ap);
	rst[rl]='\0';
	output(rst);
	return;
}

void printk_test()
{
	output("the test of printk begins\n");
	printk("the string test: %s\n","i'm a string");
	printk("the integer test: %d\n",-12345);
	printk("the hex test: %x\n",0x1234);
	printk("test pass\n");
	return;
}
