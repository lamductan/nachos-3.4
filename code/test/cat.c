#include "syscall.h"
#include "copyright.h"

int main() {
  int len;
  char buffer[MAX_STR_LENGTH];
  PrintString("Enter name of the file which be shown (source file): ");
  ReadString(buffer, MAX_STR_LENGTH);
  if (Open(buffer, 1) == -1) {
    PrintString("Source file name error!");
    PrintChar('\n');
    return 0;
  }

  len = Seek(-1,2);
  Seek(0,2);
  Read(buffer, len, 2);
  PrintChar('\n');
  PrintString(buffer);
  PrintChar('\n');
}
