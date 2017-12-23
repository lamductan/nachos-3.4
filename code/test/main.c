#include "syscall.h"

int main() {
  int svProg, vnProg, svId, vnId, n, i;
  char c;
  CreateSemaphore("mutex", 1);
  CreateSemaphore("sinhvien", 1);
  CreateSemaphore("voinuoc", 0);
  
  svId = Open("sinhvien.txt", 1);
  vnId = Open("voinuoc.txt", 0);
  if (svId == -1) Exit(-1);

  //Read number of test cases
  n = 0;
  do {
    Read(c, 1, svId);
    n = 10*n + c - '0';
  } while (c != 'n');
  printInt(n);
  PrintString("------");

 // svProg = Exec("./test/sinhvien", svId, n);
  //vnProg = Exec("./test/voinuoc", vnId, n);
 // Join(svProg);
  //Join(vnProg);

  Exit(0);
}
