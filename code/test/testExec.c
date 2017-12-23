#include "syscall.h"

int main() {
  int a, c;
  CreateSemaphore("mutex", 1);
  CreateSemaphore("PrintA", 1);
  CreateSemaphore("PrintC", 0);
  a = Exec("./test/printA");
  c = Exec("./test/printC");

  Join(a);
  Join(c);
  print("\n");
  Exit(0);
}
