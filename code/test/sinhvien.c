#include "system.h"

int main(int argc, char** argv) {  
  Wait("sinhvien");
  Wait("mutex");
  int fidSinhVien, i, v;
  char c;
  fidSinhVien = 0;
  i = 0;
  while (argv[0][i] >= '0' && argv[0][i] <= '9') fidSinhVien = fidSinhVien*10 + argv[0][i] - '0';
  PrintString("FIDSV ");
  printInt(fidSinhVien);
 
  v = 0;
  do {
    Read(c, 1, fidSinhVien);
    if (c >= '0' && c <= '9') v = 10*v + c - '0';
    else {
      printInt(v);
      print("\n");
      v = 0;
    }
  } while (c != '\n');

  Signal("mutex");
  //Signal("voinuoc");
  Exit(0);
}
