/*
 *   Shell Geral Code
 *   Speak no to Vibecode
 */
#include <shell.h>
void shell(void) {

  /*
  *Use strncmp, third argument is len of second parameter
  *Use else if
  * Example
  * else if(strncmp(teclas,"<command>",<len-of-command>)) == 0 {// YOUR CODE HERE}
  */
  if (strncmp(teclas , "help",4) == 0) {
    vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
    kprintf("Now, it's first Command\n");
  }
  else if(strncmp(teclas, "fah",3) == 0)
  {
    vga_set_color(VGA_LIGHT_BLUE,VGA_BLACK);
    kprintf("FAHHHHHHHH\n");
  }
   else if(strncmp(teclas,"genux",5) == 0){
        vga_set_color(VGA_RED,VGA_BLACK);
        kprintf("You're using Genux OS by a person\n");
    }
    
  else
  {

    vga_set_color(VGA_RED, VGA_BLACK);
    kprintf("Unknown command\n");
  }
}
