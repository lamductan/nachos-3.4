#include "syscall.h"
#include "copyright.h"
#define maxlen 32

int main() 
{
  char filename[MAX_STR_LENGTH];
  PrintString("Enter name of the file which be created: ");
  ReadString(filename, MAX_STR_LENGTH);
  Write("Create file ", 13, ConsoleOutput);
  if (CreateFile(filename) == 0)
  {
    PrintString(filename);
    Write(" success.\n", 10, ConsoleOutput);
  }
  else
  {
    PrintString(filename);
    Write(" failed.\n", 10, ConsoleOutput);
  }
  
  return 0;
}
