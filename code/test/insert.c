/* Program to copy data in source file and insert to the middle of dest file */

#include "syscall.h"

int main() {
  int len1, len2, i, idIn, idOut;
  char buffer[MAX_STR_LENGTH];
  PrintString("Enter name of the file which be copy (source file): ");
  ReadString(buffer, MAX_STR_LENGTH);
  idIn = Open(buffer, 1);
  if (idIn == -1) {
    PrintString("Source file name error!");
    PrintChar('\n');
    return 0;
  }
  PrintString("Enter name of the file which be inserted (dest file): ");
  ReadString(buffer, MAX_STR_LENGTH);
  idOut = Open(buffer, 0);
  if (idOut == -1) {
    CreateFile(buffer);
    PrintString("Create file successfully");
    PrintChar('\n');
    idOut = Open(buffer, 0);
  }
  
  len1 = Seek(-1,idIn);
  Seek(0,idIn);
  Read(buffer, len1, idOut);
  i = len1 - 1;
  while (buffer[i--] <= 10);
  i+=2;
  len2 = Seek(-1,idOut);
  Seek(len2/2,idOut);
  Read(buffer + i, len2 - len2/2, idOut);
  Seek(len2/2,idOut);
  Write(buffer, i + len2 - len2/2, idOut);
  //PrintString(buffer);
  PrintString("Insert done.\n");

  if (idIn >= 0) Close(idIn);
  if (idOut >= 0) Close(idOut);
  return 0;
}
