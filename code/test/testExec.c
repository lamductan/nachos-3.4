#include "syscall.h"

int main() {
/*
  int a, c;
  CreateSemaphore("mutex", 1);
  CreateSemaphore("PrintA", 1);
  CreateSemaphore("PrintC", 0);
  a = Exec("./test/printA");
  c = Exec("./test/printC");

  Join(a);
  Join(c);
  print("\n");
*/
  int b;
  b = Exec("./test/printB ./test/sinhvien 12345");
  Join(b);
  Exit(0);
}
