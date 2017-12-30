#include "syscall.h"
#define OUTPUT "output.txt"

int main(int argc, char** argv) {
  int svProg, vnProg, fidSinhVien, n;
  char c = 'a';
  char* cmdSV = "./test/sinhvien", *cmdVN;
 
  CreateSemaphore("sinhvien", 1);
  CreateSemaphore("voinuoc", 0);
  
  fidSinhVien = Open("test/input.txt", 1);
  if (fidSinhVien == -1) {
    Exit(-1);
  }

  //Read number of test cases
  n = 0;
  while (1) {
    Read(&c, 1, fidSinhVien);
    if (c != '\n') n = 10*n + c - '0';
    else break;
  }

  CatI2Str(cmdSV, fidSinhVien);
  CatI2Str(cmdSV, n);
 
  cmdVN = "./test/voinuoc";
 
  vnProg = Exec(cmdVN);
  svProg = Exec(cmdSV);

  Join(svProg);
  Join(vnProg);

  Close(fidSinhVien);
  return 0;
}
