#include "syscall.h"
#include "copyright.h"
#define maxlen 32

int main() 
{
  char filename[MAX_STR_LENGTH];
  //PrintString("Enter name of the file which be created: ");
  //ReadString(filename, MAX_STR_LENGTH);
  if (CreateFile("2493859") == 0)
  {
    print("Create file ");
    print(filename);
    //PrintInt(23);
    print(" success.\n");
  }
  else
  {
    print("Create file ");
    print(filename);
    print(" failed.\n");
  }
  
  return 0;
}
