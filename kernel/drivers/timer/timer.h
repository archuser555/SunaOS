#ifndef TIMER_H
#define TIMER_H

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

void wait_for_io(uint32 timer_count)
{
  while(1){
    asm volatile("nop");
    timer_count--;
    if(timer_count <= 0)
      break;
    }
}
void sleep(uint32 timer_count)
{
  wait_for_io(timer_count);
}

#endif
