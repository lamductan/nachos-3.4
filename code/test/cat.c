/*Program to print data in source file to Console*/
#include "syscall.h"

int main() {
  int len, idIn;
  char buffer[MAX_STR_LENGTH];
  PrintString("Enter name of the file which be shown (source file): ");
  ReadString(buffer, MAX_STR_LENGTH);
  idIn = Open(buffer, 1);
  if (idIn == -1) {
    PrintString("Source file name error!");
    PrintChar('\n');
    return 0;
  }
  len = Seek(-1,idIn);
  Seek(0,idIn);
  Read(buffer, len, idIn);
  PrintChar('\n');
  PrintString(buffer);
  PrintChar('\n');

  if (idIn >= 0) Close(idIn);
  return 0;
}
