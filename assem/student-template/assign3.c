/**************************************************************

 *               Name: Blake Kershaw                          * 
                 Class: CDA 3101  
 *         Assignment: Asg 2(an assembler of a subset of the  * 
                             MIPS assembly language) 
 *                                                            *
           Compile: "gcc -std=c99 assign3.c"    
 *                                                            * 

 **************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINE 80
#define MAXREG  5

union{
  unsigned int x;
  struct{
      unsigned int func:6; 
      unsigned int shamt:5;
      unsigned int rd:5;
      unsigned int rt:5;
      unsigned int rs:5;      
      unsigned int opcode:6;
    } rformat;
  struct{
      unsigned int imm:16;
      unsigned int rt:5;
      unsigned int rs:5;
      unsigned int opcode:6;
    } iformat;
  struct{
      unsigned int pseudo_absolute:26;
      unsigned int opcode:6;
    } jformat;
  struct{
      unsigned int d:32;
    }data;
  }u;


int main()
{
  char line[9];
  int a = 0; 
  int ic = 0;
  int dc = 0;
  unsigned int storage[32768] = {0}; //store read in instructions

  while (fgets(line, MAXLINE, stdin)) {


    if( sscanf(line,"%d %d", &ic, &dc) == 2)
      printf("Instruction count: %d Data Count: %d\n", ic, dc); 

    else if( sscanf(line,"%x",&u.x ) == 1 ){
      storage[a] = u.x; //store numbers
      ++a; //increment a;
      //printf("read in number: %08x\n", u.x);
      //printf("opcode in decimal: %u\n", u.jformat.opcode); //look at opcode
    }// end elseif
      
  } //end of while loop


 return 0;
} //end main
