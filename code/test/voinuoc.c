#include "syscall.h"

int main(int argc, char** argv) {
  Wait("voinuoc");
  Wait("mutex");  
  Signal("mutex");
  Signal("sinhvien");
  Exit(0);
}
