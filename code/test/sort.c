#include "syscall.h"

int
main()
{
    int A[500];	
    int i, j, tmp, n;
    PrintString("Enter number of integer: ");
    n = ReadInt();
    
    for (i = 0; i < n; i++)		
        A[i] = ReadInt();

    for(i = 0; i < n; i++) {
      PrintInt(A[i]);
      PrintChar(' ');
    }
    PrintChar('\n');

    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
	   if (A[j] > A[j + 1]) {	
	      tmp = A[j];
	      A[j] = A[j + 1];
	      A[j + 1] = tmp;
    	   }
    PrintString("Array after sorted: ");
    for(i = 0; i < n; i++) {
      PrintInt(A[i]);
      PrintChar(' ');
    }
    PrintChar('\n');
    return 0;
}
