#ifndef STD_I_O_H
#define STD_I_O_H

unsigned char inb ( int portnum )
{
    unsigned char data=0;
asm ( "inb %%dx, %%al" : "=a" ( data ) : "d" ( portnum ) );
    return data;
}

unsigned char rdp (unsigned short port) { //not remote desktop protocol...
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

unsigned short inw ( unsigned short portnum )
{
    unsigned short _v;
asm ( "inw %1,%0" : "=a" ( _v ) : "d" ( portnum ) );
    return _v;
}

void outb ( int portnum, int data )
{
    asm ( "outb %%al, %%dx" :: "a" ( data ),"d" ( portnum ) );
}

void outw ( unsigned short portnum, unsigned short data )
{
    asm ( "outw %%ax,%%dx" :: "a" ( data ), "d" ( portnum ) );
}

void io_wait ( void )
{
    asm ( "jmp 1f;1:jmp 1f;1:" );
}
#endif
