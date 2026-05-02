// density - v1.0.0 | open-source, license included
// made by westspray

// --headers--
#include "../HEADER_FILES/log.h"

// --macros--
#define CTRL_KEY(k) ((k) & 0x1f)

// --variables--
struct termios old, new1;

char d;
int space;

char draw_color[8][10] = {"\033[0;97m", "\033[0;90m", "\033[0;91m", "\033[0;94m", "\033[0;92m", "\033[0;93m", "\033[0;95m", "\033[0;96m"};
char draw_symbol[18] = {'#', '$', '-', '|', '/', '\'', '@', '%', '*', '~', '<', '>', '?', '!', '.', ':', ';'};
char draw_effect[6][10] = {"", "\033[5m", "\033[1m", "\033[3m", "\033[4m", "\033[9m"};

int color_iterator = 0;
int symbol_iterator = 0;
int effect_iterator = 0;

int space_iterator = 0;
int setup_iterator = 0;

int color_arr_size = sizeof(draw_color) / 10 - 1;
int symbol_arr_size = sizeof(draw_symbol) - 2;
int effect_arr_size = sizeof(draw_effect) / 10 - 1;

// --functions--
void reset_termios()
{
 tcsetattr(1, TCSAFLUSH, &old);
}

void init_termios()
{
 tcgetattr(1, &old);
 new1 = old;

 new1.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
 new1.c_lflag &= ~(IXON);
 
 tcsetattr(1, TCSANOW, &new1);
}

void read_check(char content)
{
 switch (content)
 {
  case CTRL_KEY('X'):
    clear_screen();
    reset_termios();
    exit(1);
    break;
  case CTRL_KEY('R'):
   clear_screen();
   break;

  case 80:
    if (color_iterator == color_arr_size)
    {
     color_iterator = 0;
    }
    else
    {
     color_iterator++;
     }
    break;
  case 81:
    if (symbol_iterator == symbol_arr_size)
    {
     symbol_iterator = 0;
    }
    else
    {
     symbol_iterator++;
    }
    break;
  case 82:
   if (effect_iterator == effect_arr_size)
    {
     effect_iterator = 0;
    }
    else
    {
     effect_iterator++;
    }
    break;

  case 0x77:
   space++;
   printf("%s%s%c", draw_color[color_iterator], draw_effect[effect_iterator], draw_symbol[symbol_iterator]);
   fflush(stdout);
   break;

  case 65:
   printf("\033[A");
   break;
  case 66:
   printf("\033[?25l");
   printf("\n");
   for (space_iterator = 0; space_iterator < space; space_iterator++)
   {
    printf("\033[1C");
    fflush(stdout);
   }
   printf("\033[?25h");
   break;
  case 67:
   space++;
   printf("\033[1C");
   break;
  case 68:
   space--;
   printf("\b");
   break;

  case 10:
   space_iterator = 0;
   space = 0;
   printf("\n");
   break;
  case 0x20:
   space++;
   printf(" ");
   fflush(stdout);
   break;
  case 127:
   space--;
   printf("\b");
   printf(" ");
   printf("\b");
   fflush(stdout);
   break;
 }
}

void main_screen()
{
 clear_screen();
 usleep(100);
 setbuf(stdout, NULL);
 init_termios();

 while (1)
 {
  read(0, &d, sizeof(d));
  read_check(d);
 }
}

// --main--
int main(int argc, char *argv[])
{
 if (argc <= 1)
 {
  warning("This software contain flashing light, use with awareness.");
  info("To disable this warning, use \"no_warning\".");
  sleep(5);
  main_screen();
 }
 else if (strcmp(argv[1], "no_warning") == 0)
 {
  main_screen();
 }
 else
 {
  unknown("Error encountered.");
  info("Possibly invalid or too much argument.");
 }
}
