#include "syscall.h"

int main() {
  char buffer[MAX_STR_LENGTH];
  Read(buffer, MAX_STR_LENGTH, 0);
  Write(buffer, MAX_STR_LENGTH, 1);
  PrintChar('\n');
  return 0;
}
