/* Program to copy data in source file and write to dest file */
#include "syscall.h"

int main() {
  int len, idIn, idOut, loop;
  char buffer[MAX_STR_LENGTH];
  PrintString("Enter name of the file which be copy (source file): ");
  ReadString(buffer, MAX_STR_LENGTH);
  idIn = Open(buffer, 1);
  if (idIn == -1) {
    PrintString("Source file name error!");
    PrintChar('\n');
    return 0;
  }
  PrintString("Enter name of the file which saves result (dest file): ");
  ReadString(buffer, MAX_STR_LENGTH);
  idOut = Open(buffer, 0);
  if (idOut == -1) {
    CreateFile(buffer);
    PrintString("Create file successfully");
    PrintChar('\n');
    idOut = Open(buffer, 0);
  }
  
  len = Seek(-1,idIn);
  Seek(0,idIn);
  loop = len/(MAX_STR_LENGTH - 1) + len % (MAX_STR_LENGTH - 1) > 0;
  while (loop--) {
    Read(buffer, MAX_STR_LENGTH - 1, idIn);
    Write(buffer, MAX_STR_LENGTH - 1, idOut);
    PrintString(buffer);
    PrintString("\n");
  }

  PrintString("Copy file done.\n");  
  if (idIn >= 0) Close(idIn);
  if (idOut >= 0) Close(idOut);

  return 0;
}
