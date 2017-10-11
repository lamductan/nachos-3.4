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
  int res;
  if (Create("ILoveYPhung.txt") == 0)
  {
    res = Sub(43, 23);
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
