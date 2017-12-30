#include "syscall.h"
#define TMP "tmp"
#define OUTPUT "output.txt"

int Min(int a, int b) {
  return a < b ? a : b;
}

int openTmp(char* tmp) { 
  int fidTmp = Open(TMP, 0);
  return fidTmp;
}

int main(int argc, char** argv) {
  int fidSinhVien, fidOutput, fidTmp, v, servingTime1, servingTime2, minServingTime;
  char c = 'a';
  fidTmp = -1;
  
  fidOutput = Open(OUTPUT, 0);
  if (fidOutput == -1) {
    Write("Create output file\n", 20, ConsoleOutput);
    if (CreateFile(OUTPUT) == 0) {
      fidOutput = Open(OUTPUT,0);
    }
    else Exit(2);
  }
  if (fidOutput < 0) Exit(-1);
  
  while (c != 'q') {
    servingTime1 = servingTime2 = 0;
    do {
      Wait("voinuoc");
      if (fidTmp == -1) fidTmp = openTmp(TMP);
      if (fidTmp == -1) {
        PrintString("Cannot open tmp file.\n");
        Exit(-2);
      }

      if (Read(&c, 1, fidTmp) != 1) {
          print("Error\n");
          Exit(123);
      }
      if (c == 'q') {
        Signal("sinhvien");
        break;
      }
      if (c >= '0' && c <= '9') {
        v = 10*v + c - '0';
        Signal("voinuoc");
      }
      else {
        if (servingTime1 == 0) {
          Write("1 ",2,fidOutput);
          servingTime1 = v;
        }
        else {
          Write("2 ",2,fidOutput);
          servingTime2 = v;
        }
        minServingTime = Min(servingTime1, servingTime2);
        servingTime1 -= minServingTime;
        servingTime2 -= minServingTime;

        Close(fidTmp);
        fidTmp = -1;
        Signal("sinhvien");
        v = 0;
      }
    } while (c != '\n' && c != 'q');
    Write("\n",1,fidOutput);
  }

  Close(fidOutput);
  Exit(0);
}
