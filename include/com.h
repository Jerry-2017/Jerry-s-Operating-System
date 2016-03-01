#ifndef __COM_H__
#define __COM_H__
#define COM_PORT 0x3f8   /* COM1 */
void init_serial();
int is_serial_idle();
void output(char* string);
#endif