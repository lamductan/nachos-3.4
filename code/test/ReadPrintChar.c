#include "syscall.h"

int main() {
  char c;
  PrintString("Enter a character: ");
  c = ReadChar();
  PrintString("\nYour character is: ");
  PrintChar(c);
  PrintChar('\n');
  return 0;
}


