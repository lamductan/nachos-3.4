#include "syscall.h"
#include "copyright.h"

int main() {
  Open("test0112.txt", 0);
  Open("test456.txt", 1);
  Open("test000", 0);
  Open("test0.txt", 0);
  Open("test1.txt", 0);
  Open("test2.txt", 0);
  Open("test0.txt", 0);
  Open("test3.txt", 0);
  Open("test4.txt", 0);
  Open("test5.txt", 0);
  Open("test6.txt", 0);
  Open("test7.txt", 0);
  Open("test8.txt", 0);
  Open("test9.txt", 0);
  Close(9);
  Open("test0112.txt", 0);
}