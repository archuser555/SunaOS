#include "kernel.h"
//The Good old Pi, Its Only Sin(e), Nothing Else!
#define Pi 3.14159265359
//detect what shell the user use
int SOSH = 2;
int SCLC = 0;
//pepsi mannnn give pepsi to everyone, pepsi maaaaan, its the gentelman, pepsi maaaaan, its a pepsi but a man, its pepsi pepsi pepsi pepsi, pepsimaaaaaaaaan.
bool pepsi_man = false;
//index for video buffer array
int num1=0,num2=0,num3=0,num4=0,num5=0,num6=0,num7=0,num8=0,num9=0,num10=0,num11=0,num12=0,num13=0,num14=0,num15=0,num16=0;
int nim1=0,nim2=0,nim3=0,nim4=0,nim5=0,nim6=0,nim7=0,nim8=0,nim9=0,nim10=0,nim11=0,nim12=0;
uint32 vga_index;

#define NULL 0
//for detect how much words and ENTER was printed, to detect how to restart SASH

unsigned int ENTER_times = 0;
unsigned int another_click = 0;
unsigned int click_times = 0;
//detect what theme the user use, 1 for powershell theme, 2 for matrix, 3 for cmd.exe, come open github issue if u want add new theme, fell free...
int theme = 2; // default theme is matrix
//i havent found a good name to this variable.

bool impostor = false;

//some bools to detect if user write some words aka commands, read the init_keyboard() to understand more.
bool u = false;
bool y = false;
bool h = false;
bool e = false;
bool l = false;
bool p = false;
bool s = false;
bool c = false;
bool o = false;
bool r = false;
bool t = false;
bool x = false;
bool b = false;
bool g = false;
bool d=false;bool f=false;bool i=false;bool j=false;bool k=false;bool m=false;bool n=false;bool q=false;bool w=false;bool v=false;bool z= false;bool space = false;
//total words typed

unsigned int total_click = 0;

//store new lines
static uint32 next_line_index = 1;

//fore & back color values

uint8 g_fore_color = WHITE, g_back_color = BLUE;

//digit ascii code for printing integers

int digit_ascii_codes[10] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};

/*
16 bit video buffer elements(register ax)
8 bits(ah) higher : 
  lower 4 bits - forec olor
  higher 4 bits - back color

8 bits(al) lower :
  8 bits : ASCII character to print
*/
uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color) 
{
  uint16 ax = 0;
  uint8 ah = 0, al = 0;

  ah = back_color;
  ah <<= 4;
  ah |= fore_color;
  ax = ah;
  ax <<= 8;
  al = ch;
  ax |= al;

  return ax;
}

//clear video buffer array
void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color)
{


  uint32 i;
  for(i = 0; i < BUFSIZE; i++){
    (*buffer)[i] = vga_entry(NULL, fore_color, back_color);
  }
  next_line_index = 1;
  vga_index = 0;
}

//initialize vga buffer
void init_vga(uint8 fore_color, uint8 back_color)
{
  vga_buffer = (uint16*)VGA_ADDRESS;
  clear_vga_buffer(&vga_buffer, fore_color, back_color);
  g_fore_color = fore_color;
  g_back_color = back_color;
}

/*
increase vga_index by width of row(80)
*/
void print_new_line()
{
  if(next_line_index >= 55){
    next_line_index = 0;
    clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);
  }
  vga_index = 80*next_line_index;
  next_line_index++;
}

//assign ascii character to video buffer
void print_char(char ch)
{
  vga_buffer[vga_index] = vga_entry(ch, g_fore_color, g_back_color);
  vga_index++;
}


uint32 strlen(const char* str)
{
  uint32 length = 0;
  while(str[length])
    length++;
  return length;
}

uint32 digit_count(int num)
{
  uint32 count = 0;
  if(num == 0)
    return 1;
  while(num > 0){
    count++;
    num = num/10;
  }
  return count;
}

void itoa(int num, char *number)
{
  int dgcount = digit_count(num);
  int index = dgcount - 1;
  char x;
  if(num == 0 && dgcount == 1){
    number[0] = '0';
    number[1] = '\0';
  }else{
    while(num != 0){
      x = num % 10;
      number[index] = x + '0';
      index--;
      num = num / 10;
    }
    number[dgcount] = '\0';
  }
}

//print string by calling print_char
void print_string(char *str,int a)
{
  uint32 index = 0;
  while(str[index]){
    print_char(str[index]);
    index++;
  }
  if(a == 0){}
  if(a == 1){
	ENTER_times = ENTER_times + 1;    
	print_new_line();
  }}

//print int by converting it into string
//& then printing string, idk 90% there a bug here, but im not sure...
void print_int(int num,int v)
{
  char str_num[digit_count(num)+1];
  itoa(num, str_num);
  print_string(str_num,v);
}

uint8 inb(uint16 port)
{
  uint8 ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
  return ret;
}

void outb(uint16 port, uint8 data)
{
  asm volatile("outb %0, %1" : "=a"(data) : "d"(port));
}

char get_input_keycode()
{
  char ch = 0;
  while((ch = inb(KEYBOARD_PORT)) != 0){
    if(ch > 0)
      return ch;
  }
  return ch;
}

void wait_for_io(uint32 timer_count)
{
  while(1){
    asm volatile("nop");
    timer_count--;
    if(timer_count <= 0)
      break;
    }
}
char* detect_theme(int theme){
if(theme == 3){
return "Suna OS Default Theme";
}
if(theme == 2){
return "Hacker Man Theme";
}
if(theme == 1){
return "MS-DOS 1.25 Theme";
}
else{
return "What The Fuk? your theme is unknow, if you get this message, please report it to Suna Os github page";
}
}
void sleep(uint32 timer_count)
{
  wait_for_io(timer_count);
}

int add(int value1,int value2){
int a = value1;
int b = value2;
return a+b;
}
int minus(int value1,int value2){
int a = value1;
int b = value2;
return a-b;
}
int div(int value1,int value2){
int a = value1;
int b = value2;
return a/b;
}
int mul(int value1,int value2){
int a = value1;
int b = value2;
return a*b;
}

void init_keyboard()
{
  char ch = 0;
  char keycode = 0;
  do{
    keycode = get_input_keycode();
    if(keycode == KEY_ENTER){
	if(SOSH == 2){
	SOSH = 1;}
        print_new_line();
        if(h == true && e == true && l == true && p == true && click_times == 4){
	print_string("SunaOS version 0.1 (https://github.com/archuser555/sunaos)",1);
	print_string("CopyRight (c) 2021-2022 Archuser555",1);
	print_string("Usage:",1);
	print_string("  help: brief help message",1);
	print_string("  cls: clear the screen",1);
	print_string("  sclc: Suna Calculator, Support + and - and / and * and nothing only.",1);
	print_string("  color: change color theme",1);
	print_string("Thanks To Mohamed For The Logo, GalaxyNova for testing , And To You For Use!",1);
        }
        if(s == true && c == true && l == true && click_times == 4){
		SOSH = 0;SCLC = 1;		
		print_string("SCALC version 0.1, A Tool To Do Math Stuffs In SUNA OS",1);
		print_string("CopyRight (c) 2021-2022 Archuser555",1);
		print_string("Usage:",1);
		//print_string("  cos: calculat cos of value.",1); In The Near Future...
		print_string("  dd: calculate with the symbol +, Ex: 1+1,5+9...",1);
		print_string("  min: calculate with the symbol -, Ex: 1-1,5-9...",1);
		print_string("  div: calculate with the symbol /, Ex: 1/1,5/9...",1);
		print_string("  mul: calculate with the symbol *, Ex: 1*1,5*9...",1);
	}
	if(pepsi_man == true && d == true && click_times == 2){
	print_string("result: ",0);
	print_int(num1+num2+num3+num4+num5+num6+num7+num8+num9+num10,1);
	}
if(e == true && x == true && i == true && t == true && click_times == 4){
SOSH = 1;
}
	if(c == true && o == true && l == true && r == true && click_times == 5){
		print_string("Color version 0.1, a tool to change color theme in SUNA OS",1);
		print_string("You now Using the Following Theme:",0);
		print_string(detect_theme(theme),1);
		print_string("Usage:",1);
		print_string("  color suos: its the suna theme, yes, a theme like powershell...",1);
		print_string("  color hoker: it gonna let your freinds think you are hacker, but later you ca",1);print_string("n be a real hacker,when the http gonna be supported in suna Os...",1);
		print_string("  color cmd: it gonna let you return to 1990 days, msdos...",1);
		print_string("if you like other themes, feel free to open a issue in the Suna Os github page",1);
	}
else if(c == true && o == true && l == true && r == true && s == true && u == true && o == true && s == true && click_times == 10){init_vga(WHITE,CYAN);theme = 3;}
else if(c == true && o == true && l == true && r == true && h == true && o == true && k == true && e == true && click_times == 11){init_vga(GREEN,BLACK);theme = 2;}
else if(c == true && o == true && l == true && r == true && m == true && d == true && click_times == 9){init_vga(WHITE,BLACK);theme = 1;}
	if(s == true && l == true && c == true && click_times == 3){clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);impostor=true;}
	ENTER_times = ENTER_times + 1;
	if(ENTER_times >= 25){
		  clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);
		  ENTER_times = 0;
		  impostor = true;
	}
	if(ENTER_times >= 27 && impostor){
		  clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);
		  ENTER_times = 0;
	}
      h=false;e=false;l=false;p=false;click_times=0;s=false;c=false; d=false; f=false; i=false; j=false; k=false; m=false; n=false; p=false; q=false; s=false; w=false; v=false; z= false; space = false;
      if(SCLC == 1){
	print_string("SCLC>",0);
	pepsi_man = true;
	}
	if(SOSH == 1){
	print_string("SOSH>",0);
	}
}
    if(keycode == KEY_B){
      ch = 'b';
      print_char(ch);
      click_times = click_times + 1;
	b = true;
    }
    if(keycode == KEY_C){
      ch = 'c';
      print_char(ch);
      click_times = click_times + 1;
      c = true;
    }
    if(keycode == KEY_D){
      ch = 'd';
      print_char(ch);
      click_times = click_times + 1;
d = true;
    }
    if(keycode == KEY_E){
      ch = 'e';
      print_char(ch);
      click_times = click_times + 1;
      e = true;
    }
    if(keycode == KEY_F){
      ch = 'f';
      print_char(ch);
      click_times = click_times + 1;

    }
    if(keycode == KEY_G){
      ch = 'g';
      print_char(ch);
      click_times = click_times + 1;

    }
    if(keycode == KEY_H){
      ch = 'h';
      print_char(ch);
      click_times = click_times + 1;
      h = true;
    }
    if(keycode == KEY_I){
      ch = 'i';
      print_char(ch);
      click_times = click_times + 1;
i = true;
    }
    if(keycode == KEY_J){
      ch = 'j';
      print_char(ch);
      click_times = click_times + 1;
j = true;
    }
    if(keycode == KEY_K){
      ch = 'k';
      print_char(ch);
      click_times = click_times + 1;
k = true;
    }
    if(keycode == KEY_L){
      ch = 'l';
      print_char(ch);
      click_times = click_times + 1;
      l = true;
    }
    if(keycode == KEY_M){
      ch = 'm';
      print_char(ch);
      click_times = click_times + 1;
m = true;
    }
    if(keycode == KEY_N){
      ch = 'n';
      print_char(ch);
      click_times = click_times + 1;
n = true;
    }
    if(keycode == KEY_O){
      ch = 'o';
      print_char(ch);
      click_times = click_times + 1;
o = true;
    }
    if(keycode == KEY_P){
      ch = 'p';
      print_char(ch);
      click_times = click_times + 1;
      p = true;
    }
    if(keycode == KEY_Q){
      ch = 'q';
      print_char(ch);
      click_times = click_times + 1;
q = true;
    }
    if(keycode == KEY_R){
      ch = 'r';
      print_char(ch);
      click_times = click_times + 1;
r = true;
    }
    if(keycode == KEY_S){
      ch = 's';
      print_char(ch);
      click_times = click_times + 1;
      s = true;
    }
    if(keycode == KEY_T){
      ch = 't';
      print_char(ch);
      click_times = click_times + 1;
t =true;
    }
    if(keycode == KEY_U){
      ch = 'u';
      print_char(ch);
      click_times = click_times + 1;
u = true;
    }
    if(keycode == KEY_V){
      ch = 'v';
      print_char(ch);
      click_times = click_times + 1;
v= true;
    }
    if(keycode == KEY_W){
      ch = 'w';
      print_char(ch);
      click_times = click_times + 1;
w = true;
    }
    if(keycode == KEY_X){
      ch = 'x';
      print_char(ch);
      click_times = click_times + 1;
x = true;
    }
    if(keycode == KEY_Y){
      ch = 'y';
      print_char(ch);
      click_times = click_times + 1;
y = true;
    }
    if(keycode == KEY_Z){
      ch = 'z';
      print_char(ch);
      click_times = click_times + 1;
z = true;
    }
    
    
 if(keycode == KEY_1){
      ch = '1';
      print_char(ch);
      click_times = click_times + 1;
     /* if(num1 == 0){
	 num1 = 1;
}if(num1 != 0 && num2 != 0){
num1 = 1;
}
if(num2 != 0 && num3 != 0){
num2 = 1;
}
if(num3 != 0 && num4 != 0){
num3 = 1;
}
if(num4 != 0 && num5 != 0){
num4 = 1;
}
if(num5 != 0 && num6 != 0){
num5 = 1;
}
if(num6 != 0 && num7 != 0){
num6 = 1;
}
if(num7 != 0 && num8 != 0){
num7 = 1;
}
if(num8 != 0 && num9 != 0){
num8 = 1;
}
if(num9 != 0 && num10 != 0){
num9 = 1;
}
if(num10 != 0 && num11 != 0){
num10 = 1;
}
if(num11 != 0 && num12 != 0){
num11 = 1;
}
if(num12 != 0 && num13 != 0){
num12 = 1;
}
if(num13 != 0 && num14 != 0){
num13 = 1;
}
if(num14 != 0 && num15 != 0){
num14 = 1;
}
if(num15 != 0 && num16 != 0){
num15 = 1;
*/}
    
 if(keycode == KEY_2){
      ch = '2';
      print_char(ch);
      click_times = click_times + 1;
      /*if(num1 == 0){
	 num1 = 1;
}if(num1 != 0 && num2 != 0){
num1 = 2;
}
if(num2 != 0 && num3 != 0){
num2 = 2;
}
if(num3 != 0 && num4 != 0){
num3 = 2;
}
if(num4 != 0 && num5 != 0){
num4 = 2;
}
if(num5 != 0 && num6 != 0){
num5 = 2;
}
if(num6 != 0 && num7 != 0){
num6 = 2;
}
if(num7 != 0 && num8 != 0){
num7 = 2;
}
if(num8 != 0 && num9 != 0){
num8 = 2;
}
if(num9 != 0 && num10 != 0){
num9 = 2;
}
if(num10 != 0 && num11 != 0){
num10 = 2;
}
if(num11 != 0 && num12 != 0){
num11 = 2;
}
if(num12 != 0 && num13 != 0){
num12 = 2;
}
if(num13 != 0 && num14 != 0){
num13 = 2;
}
if(num14 != 0 && num15 != 0){
num14 = 2;
}
if(num15 != 0 && num16 != 0){
num15 = 2;
}*/}
    
 if(keycode == KEY_3){
      ch = '3';
      print_char(ch);
      click_times = click_times + 1;
      /*if(num1 == 0){
	 num1 = 1;
}if(num1 != 0 && num2 != 0){
num1 = 3;
}
if(num2 != 0 && num3 != 0){
num2 = 3;
}
if(num3 != 0 && num4 != 0){
num3 = 3;
}
if(num4 != 0 && num5 != 0){
num4 = 3;
}
if(num5 != 0 && num6 != 0){
num5 = 3;
}
if(num6 != 0 && num7 != 0){
num6 = 3;
}
if(num7 != 0 && num8 != 0){
num7 = 3;
}
if(num8 != 0 && num9 != 0){
num8 = 3;
}
if(num9 != 0 && num10 != 0){
num9 = 3;
}
if(num10 != 0 && num11 != 0){
num10 = 3;
}
if(num11 != 0 && num12 != 0){
num11 = 3;
}
if(num12 != 0 && num13 != 0){
num12 = 3;
}
if(num13 != 0 && num14 != 0){
num13 = 3;
}
if(num14 != 0 && num15 != 0){
num14 = 3;
}
if(num15 != 0 && num16 != 0){
num15 = 3;
}*/}
    
 if(keycode == KEY_4){
      ch = '4';
      print_char(ch);
      click_times = click_times + 1;
      /*if(num1 == 0){
	 num1 = 1;
}if(num1 != 0 && num2 != 0){
num1 = 4;
}
if(num2 != 0 && num3 != 0){
num2 = 4;
}
if(num3 != 0 && num4 != 0){
num3 = 4;
}
if(num4 != 0 && num5 != 0){
num4 = 4;
}
if(num5 != 0 && num6 != 0){
num5 = 4;
}
if(num6 != 0 && num7 != 0){
num6 = 4;
}
if(num7 != 0 && num8 != 0){
num7 = 4;
}
if(num8 != 0 && num9 != 0){
num8 = 4;
}
if(num9 != 0 && num10 != 0){
num9 = 4;
}
if(num10 != 0 && num11 != 0){
num10 = 4;
}
if(num11 != 0 && num12 != 0){
num11 = 4;
}
if(num12 != 0 && num13 != 0){
num12 = 4;
}
if(num13 != 0 && num14 != 0){
num13 = 4;
}
if(num14 != 0 && num15 != 0){
num14 = 4;
}
if(num15 != 0 && num16 != 0){
num15 = 4;
}*/}
    
 if(keycode == KEY_5){
      ch = '5';
      print_char(ch);
      click_times = click_times + 1;
      /*if(num1 == 0){
	 num1 = 1;
}if(num1 != 0 && num2 != 0){
num1 = 5;
}
if(num2 != 0 && num3 != 0){
num2 = 5;
}
if(num3 != 0 && num4 != 0){
num3 = 5;
}
if(num4 != 0 && num5 != 0){
num4 = 5;
}
if(num5 != 0 && num6 != 0){
num5 = 5;
}
if(num6 != 0 && num7 != 0){
num6 = 5;
}
if(num7 != 0 && num8 != 0){
num7 = 5;
}
if(num8 != 0 && num9 != 0){
num8 = 5;
}
if(num9 != 0 && num10 != 0){
num9 = 5;
}
if(num10 != 0 && num11 != 0){
num10 = 5;
}
if(num11 != 0 && num12 != 0){
num11 = 5;
}
if(num12 != 0 && num13 != 0){
num12 = 5;
}
if(num13 != 0 && num14 != 0){
num13 = 5;
}
if(num14 != 0 && num15 != 0){
num14 = 5;
}
if(num15 != 0 && num16 != 0){
num15 = 5;
}*/}
    
 if(keycode == KEY_6){
      ch = '6';
      print_char(ch);
      click_times = click_times + 1;
      /*if(num1 == 0){
	 num1 = 1;
}if(num1 != 0 && num2 != 0){
num1 = 6;
}
if(num2 != 0 && num3 != 0){
num2 = 6;
}
if(num3 != 0 && num4 != 0){
num3 = 6;
}
if(num4 != 0 && num5 != 0){
num4 = 6;
}
if(num5 != 0 && num6 != 0){
num5 = 6;
}
if(num6 != 0 && num7 != 0){
num6 = 6;
}
if(num7 != 0 && num8 != 0){
num7 = 6;
}
if(num8 != 0 && num9 != 0){
num8 = 6;
}
if(num9 != 0 && num10 != 0){
num9 = 6;
}
if(num10 != 0 && num11 != 0){
num10 = 6;
}
if(num11 != 0 && num12 != 0){
num11 = 6;
}
if(num12 != 0 && num13 != 0){
num12 = 6;
}
if(num13 != 0 && num14 != 0){
num13 = 6;
}
if(num14 != 0 && num15 != 0){
num14 = 6;
}
if(num15 != 0 && num16 != 0){
num15 = 6;
}*/}
    
 if(keycode == KEY_7){
      ch = '7';
      print_char(ch);
      click_times = click_times + 1;
      /*if(num1 == 0){
	 num1 = 1;
}if(num1 != 0 && num2 != 0){
num1 = 7;
}
if(num2 != 0 && num3 != 0){
num2 = 7;
}
if(num3 != 0 && num4 != 0){
num3 = 7;
}
if(num4 != 0 && num5 != 0){
num4 = 7;
}
if(num5 != 0 && num6 != 0){
num5 = 7;
}
if(num6 != 0 && num7 != 0){
num6 = 7;
}
if(num7 != 0 && num8 != 0){
num7 = 7;
}
if(num8 != 0 && num9 != 0){
num8 = 7;
}
if(num9 != 0 && num10 != 0){
num9 = 7;
}
if(num10 != 0 && num11 != 0){
num10 = 7;
}
if(num11 != 0 && num12 != 0){
num11 = 7;
}
if(num12 != 0 && num13 != 0){
num12 = 7;
}
if(num13 != 0 && num14 != 0){
num13 = 7;
}
if(num14 != 0 && num15 != 0){
num14 = 7;
}
if(num15 != 0 && num16 != 0){
num15 = 7;
}*/}
    
 if(keycode == KEY_8){
      ch = '8';
      print_char(ch);
      click_times = click_times + 1;
      /*if(num1 == 0){
	 num1 = 1;
}if(num1 != 0 && num2 != 0){
num1 = 8;
}
if(num2 != 0 && num3 != 0){
num2 = 8;
}
if(num3 != 0 && num4 != 0){
num3 = 8;
}
if(num4 != 0 && num5 != 0){
num4 = 8;
}
if(num5 != 0 && num6 != 0){
num5 = 8;
}
if(num6 != 0 && num7 != 0){
num6 = 8;
}
if(num7 != 0 && num8 != 0){
num7 = 8;
}
if(num8 != 0 && num9 != 0){
num8 = 8;
}
if(num9 != 0 && num10 != 0){
num9 = 8;
}
if(num10 != 0 && num11 != 0){
num10 = 8;
}
if(num11 != 0 && num12 != 0){
num11 = 8;
}
if(num12 != 0 && num13 != 0){
num12 = 8;
}
if(num13 != 0 && num14 != 0){
num13 = 8;
}
if(num14 != 0 && num15 != 0){
num14 = 8;
}
if(num15 != 0 && num16 != 0){
num15 = 8;
}*/}
    
 if(keycode == KEY_9){
      ch = '9';
      print_char(ch);
      click_times = click_times + 1;
      /*if(num1 == 0){
	 num1 = 1;
}if(num1 != 0 && num2 != 0){
num1 = 9;
}
if(num2 != 0 && num3 != 0){
num2 = 9;
}
if(num3 != 0 && num4 != 0){
num3 = 9;
}
if(num4 != 0 && num5 != 0){
num4 = 9;
}
if(num5 != 0 && num6 != 0){
num5 = 9;
}
if(num6 != 0 && num7 != 0){
num6 = 9;
}
if(num7 != 0 && num8 != 0){
num7 = 9;
}
if(num8 != 0 && num9 != 0){
num8 = 9;
}
if(num9 != 0 && num10 != 0){
num9 = 9;
}
if(num10 != 0 && num11 != 0){
num10 = 9;
}
if(num11 != 0 && num12 != 0){
num11 = 9;
}
if(num12 != 0 && num13 != 0){
num12 = 9;
}
if(num13 != 0 && num14 != 0){
num13 = 9;
}
if(num14 != 0 && num15 != 0){
num14 = 9;
}
if(num15 != 0 && num16 != 0){
num15 = 9;
}*/}
if(keycode == KEY_0){
      ch = '1';
      print_char(ch);
      click_times = click_times + 1;

    }
    if(keycode == KEY_MINUS){
      ch = '-';
      print_char(ch);
      click_times = click_times + 1;
      
    }
/*    if(click_times < 0){
      print_new_line();
      total_click = total_click + click_times;
      print_string("You Write ");
      print_int(click_times);
      print_string(" Words in The Last ENTER, Total words is:");
      print_int(total_click);
      print_new_line();

    }*/ //i plan to do something like analyz words writed per line, but nah...
    if(keycode == KEY_SPACE){
	ch = ' ';
	print_char(ch);
        click_times = click_times + 1;
        space = true;
    }
    sleep(0x3000000);
  }while(ch > 0);
}

void kernel_entry()
{
  //first init vga with fore & back colors
  init_vga(WHITE,CYAN);
theme = 3;
  print_string("Welcom To Suna OS, The Os Who Make Folks More Like Dogs, Write help 4 help",1);
  print_string("SOSH>",0);
  init_keyboard();
}
