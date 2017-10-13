#include "syscall.h"

int main() {
  char c[MAX_STR_LENGTH];
  ReadString(c, MAX_STR_LENGTH);
  PrintString(c);
  return 0;
}


