#include "syscall.h"

int main() {
  int len;
  char buffer[MAX_STR_LENGTH];
  PrintString("Enter name of the file which be copy (source file): ");
  ReadString(buffer, MAX_STR_LENGTH);
  if (Open(buffer, 1) == -1) {
    PrintString("Source file name error!");
    PrintChar('\n');
    return 0;
  }
  PrintString("Enter name of the file which saves result (dest file): ");
  ReadString(buffer, MAX_STR_LENGTH);
  if (Open(buffer, 0) == -1) {
    CreateFile(buffer);
    PrintString("Create file successfully");
    PrintChar('\n');
    Open(buffer, 0);
  }
  
  len = Seek(-1,2);
  Seek(0,2);
  Read(buffer, len, 2);
  Write(buffer, len, 3);

  PrintString("Copy file done");
  PrintString("\n");

  return 0;
}
