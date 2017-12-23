#include "syscall.h"

int main() {
  int a, i;
  for(i = 0; i < 100; i++) {
    Wait("PrintC");
    Wait("mutex");
    print("c");
    Signal("mutex");
    Signal("PrintA");
  }
  return 0;
}

