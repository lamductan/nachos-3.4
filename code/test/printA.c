#include "syscall.h"

void inc(int *x) {
  *x += 10;
}

void write(int x) {
    Write("x = ", 4, ConsoleOutput);
    printInt(x);
    Write("\n", 1, ConsoleOutput);
}

int main(int argc, char* argv[]) {
  int i, x;
  for(i = 0; i < 20; ++i) {
    Wait("PrintA");
    Write("a", 1, ConsoleOutput);
    Signal("PrintC");
  }

/*  x = *((int*) Atoi(argv[1]));
  for(i = 0; i < 10; i++) {
    Wait("mutex");
    Write("Process A\n", 10, ConsoleOutput); 
    inc(&x);
    write(x);
    Signal("mutex");
  }
*/
  return 0;
}
