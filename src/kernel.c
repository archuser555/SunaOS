#include "../kernel/drivers/sounds/sound.h"
#include "../kernel/drivers/vga.h"
#include "../kernel/drivers/keyboard/keyboard.h"
#include "../kernel/drivers/timer/timer.h"
#define KEY_9 0x0A
#define KEY_A 0x41

int main(){
  init_vga(WHITE,CYAN);
  puts("a",1);
  char ch = 0;
  char keycode = 0;
  do{
    keycode = get_input_keycode();
     if(keycode == keycode){ch = keycode;print(ch);}
    sleep(0x3000000);
}while(ch < 0);
}
