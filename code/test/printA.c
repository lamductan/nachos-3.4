#include "syscall.h"

int main() {
  int i;
  for(i = 0; i < 100; ++i) {
    Wait("PrintA");
    Wait("mutex");
    print("a");
    Signal("mutex");
    Signal("PrintC");
  }
  return 0;
}
