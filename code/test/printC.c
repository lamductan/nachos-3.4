#include "syscall.h"

void dec(int *x) {
  *x -= 5;
}

void write(int x) {
    Write("x = ", 4, ConsoleOutput);
    printInt(x);
    Write("\n", 1, ConsoleOutput);
}

int main() {
  int i, x;
  for(i = 0; i < 20; i++) {
    Wait("PrintC");
    Write("c", 1, ConsoleOutput);
    Signal("PrintA");
  }

//  for(i = 0; i < 10; i++) {
//    Wait("mutex");
//    Write("Process B\n", 10, ConsoleOutput); 
//    dec(&x);
//    write(x);
//    Signal("mutex");
//  }
  return 0;
}

