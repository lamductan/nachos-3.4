#include "syscall.h"
#include "copyright.h"
#define maxlen 32

int main() 
{
  char* filename = "test0112.txt";
  if (CreateFile(filename) == 0)
  {
    print("\Create file ~");
    print(filename);
    print(" success.");
  }
  else
  {
    print("\Create file ~");
    print(filename);
    print(" failed.~");
  }
}