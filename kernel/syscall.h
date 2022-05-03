#ifndef SYSCALLS_H
#define SYSCALLS_H
#include "stdio.h"


void reboot(void)
{
  unsigned char good = 0x02;
  while (good & 0x02)
  {
    good = inb(0x64);
  }
  outb(0x64, 0xFE);
 loop:
  asm volatile ("hlt");
  goto loop;
}

#endif
