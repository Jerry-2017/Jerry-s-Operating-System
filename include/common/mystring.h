#ifndef __MYSTRING_H__
#define __MYSTRING_H__
uint8_t c2i(char c);
char i2c(uint32_t i);
char x2c(uint32_t i);

int scopy(const char *,char *);

// return the string length
int u2s(uint32_t, char *);
int i2s(int, char*);
int x2s(int, char*);
#endif
