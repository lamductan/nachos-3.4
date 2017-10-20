#include "syscall.h"

int main() {
  char c[MAX_STR_LENGTH];
  PrintString("Enter your string: ");
  ReadString(c, MAX_STR_LENGTH);
  PrintString("\nYour string is: ");
  PrintString(c);
  PrintChar('\n');
  return 0;
}


