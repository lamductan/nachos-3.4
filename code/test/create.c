#include "syscall.h"
#include "copyright.h"
#define maxlen 32

int main() 
{
  /*int len;
  char filename[maxlen + 1];
 // print("Tang Y Phung\n");
  if (Create("ILoveYPhung.txt") == 0)
  {
    print("\Create file ~");
    print(filename);
    print("success.");
  }
  else
  {
    print("\Create file ~");
    print(filename);
    print("failed.~");
  }
  Halt();*/
  print("Create file\n");
  if (Create("ILoveYPhung.txt") == 0)
  {
    print("\Create file ~");
    //print(filename);
    print("success.");
  }
  else
  {
    print("\Create file ~");
    //print(filename);
    print("failed.~");
  }
  print("Success");
}
