#include "syscall.h"
#include "copyright.h"

int main()
{
  int number;
  PrintString("Test ReadInt and PrintInt\n");
  PrintString("Enter a number: ");
  number = ReadInt();
  PrintString("\nYour number is: ");
  PrintInt(number);
  PrintChar('\n');
  return 0; 
}
