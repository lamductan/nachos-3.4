#include "syscall.h"
#include "copyright.h"

int main()
{
  int number;
  print("Test ReadInt and PrintInt\n");
  number = ReadInt();
  PrintInt(number);
  print("\n");
  PrintInt(7052017);
  return 0; 
}
