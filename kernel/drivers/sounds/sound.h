#include "../timer/timer.h"
#include "../../stdio.h"
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
short freq;

void sound(short freq)
{

    unsigned short int freqdiv;
    unsigned char tmp;
    freqdiv = 1193180 / freq;
    outb(0x43, 0xB6);
    outb(0x42, (char) freqdiv);       /* first bits 0-7 */
    outb(0x42, (char) (freqdiv >> 8));/* then bits 8-15 */
    tmp = inb(0x61);
    if (tmp != (tmp | 3))   /* only output if bits are not correctly set */
        outb(0x61, tmp | 3);
}

void nosound()
{
    unsigned char tmp;
    tmp = inb(0x61);  /* KB controller port B */
    tmp &= 0xFC;      /* disable speaker + clock 2 gate */
    outb(0x61, tmp);  /* output */
}

void beep()
{
    sound(1000);
    sleep(10000);
    nosound();
}
