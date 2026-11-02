/*
 *   Shell Geral Code
 *   Speak no to Vibecode
 */
#include <shell.h>
#include <gop.h>
void shell(void) {

  /*
  *Use strncmp, third argument is len of second parameter
  *Use else if
  * Example
  * else if(strncmp(teclas,"<command>",<len-of-command>)) == 0 {// YOUR CODE HERE}
  */
  if (strncmp(teclas , "help",4) == 0) {
    set_color(BLUE);
    kprintf("Now, it's first Command\n");
  }
  else if(strncmp(teclas, "fah",3) == 0)
  {
    set_color(BLUE);
    kprintf("FAHHHHHHHH\n");
  }
   else if(strncmp(teclas,"genux",5) == 0){
        set_color(RED);
        kprintf("You're using Genux OS by a person\n");
    }
    
  else
  {

    set_color(RED);
    kprintf("Unknown command\n");
  }
}
