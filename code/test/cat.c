/*Program to print data in source file to Console*/
#include "syscall.h"

int main() {
  int len, idIn, loop;
  char buffer[MAX_STR_LENGTH];
  PrintString("Enter name of the file which be shown (source file): ");
  ReadString(buffer, MAX_STR_LENGTH);
  idIn = Open(buffer, 1);
  if (idIn == -1) {
    PrintString("Source file name error!\n");
    return 0;
  }
  len = Seek(-1,idIn);
  Seek(0,idIn);
  loop = len/(MAX_STR_LENGTH - 1) + len % (MAX_STR_LENGTH - 1) > 0;
  while (loop--) {
    Read(buffer, MAX_STR_LENGTH - 1, idIn);
    PrintString(buffer);
  }
  PrintChar('\n');
  Close(idIn);
  return 0;
}
