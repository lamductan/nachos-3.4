/* Program to copy data in source file and insert to the middle of dest file */

#include "syscall.h"

int main() {
  int len1, len2, i;
  char buffer[MAX_STR_LENGTH];
  PrintString("Enter name of the file which be copy (source file): ");
  ReadString(buffer, MAX_STR_LENGTH);
  if (Open(buffer, 1) == -1) {
    PrintString("Source file name error!");
    PrintChar('\n');
    return 0;
  }
  PrintString("Enter name of the file which be inserted (dest file): ");
  ReadString(buffer, MAX_STR_LENGTH);
  if (Open(buffer, 0) == -1) {
    CreateFile(buffer);
    PrintString("Create file successfully");
    PrintChar('\n');
    Open(buffer, 0);
  }
  
  len1 = Seek(-1,2);
  Seek(0,2);
  Read(buffer, len1, 2);
  i = len1 - 1;
  while (buffer[i--] <= 10);
  i+=2;
  len2 = Seek(-1,3);
  Seek(len2/2,3);
  Read(buffer + i, len2 - len2/2, 3);
  Seek(len2/2,3);
  Write(buffer, i + len2 - len2/2, 3);
  //PrintString(buffer);
  PrintString("Insert done.\n");

  return 0;
}
