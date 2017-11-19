#include "syscall.h"

int main() {
  int l;
  char c;
  char filename[MAX_STR_LENGTH];
  PrintString("Enter name of the file which be reversed (source file): ");
  ReadString(filename, MAX_STR_LENGTH);
  if (Open(filename, 1) == -1) {
    PrintString("Source file name error!");
    PrintChar('\n');
    return 0;
  }
  PrintString("Enter name of the file which saves result (dest file): ");
  ReadString(filename, MAX_STR_LENGTH);
  if (Open(filename, 0) == -1) {
    CreateFile(filename);
    PrintString("Create file successfully");
    PrintChar('\n');
    Open(filename, 0);
  }

  l = Seek(-1, 2);
  while (--l >= 0) {
    Seek(l, 2);
    Read(&c, 1, 2);
    Write(&c, 1, 3);
  }
  PrintString("Reverse succesfully");
  PrintChar('\n');
  Close(2);
  Close(3);
  return 0;
}
