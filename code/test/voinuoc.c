#include "syscall.h"
#define TMP "tmp"

int Min(int a, int b) {
  return a < b ? a : b;
}

int openTmp(char* tmp) { 
  int fidTmp = Open(TMP, 0);
  if (fidTmp == -1) {
    if (CreateFile(TMP) == 0) 
      fidTmp = Open(TMP,0);
    fidTmp = -1;
  }
  return fidTmp;
}

int main(int argc, char** argv) {
  int fidSinhVien, fidOutput, fidTmp, v, servingTime1, servingTime2, minServingTime;
  char c = 'a';
  fidOutput = Atoi(argv[1]);
  fidTmp = -1;
  if (fidOutput < 0) Exit(-1);
  
  while (c != 'q') {
    servingTime1 = servingTime2 = 0;
    do {
      Wait("voinuoc");
      Wait("mutex");
      if (fidTmp == -1) fidTmp = openTmp(TMP);
      if (Read(&c, 1, fidTmp) != 1) {
          print("Error\n");
          Exit(123);
      }
      if (c == 'q') {
        Signal("mutex");
        Signal("sinhvien");
        break;
      }
      if (c >= '0' && c <= '9') {
        v = 10*v + c - '0';
        Signal("mutex");
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
        Signal("mutex");
        Signal("sinhvien");
        v = 0;
      }
    } while (c != '\n' && c != 'q');
    Write("\n",1,fidOutput);
  }
  Close(fidOutput);
  Exit(0);
}
