#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "../../stdio.h"
#include "../memory/mem.h"

char get_input_keycode()
{
  char ch = 0;
  while((ch = inb(0x60)) != 0){
    if(ch > 0)
      return ch;
  }
  return ch;
}

#endif
