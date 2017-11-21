// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);

    switch (which)
    {
       case NoException:
         return;
       case PageFaultException:
         printf("No valid translation found %d %d\n", which, type);
         break;
       case ReadOnlyException:     
         printf("Write attempted to page marked %d %d\n", which, type);
         break;
       case BusErrorException:
         printf("Translaion resulted in an %d %d\n", which, type);
         break;
       case AddressErrorException: 
         printf("Unaligned reference or one that %d %d\n", which, type);
         break;
       case OverflowException:
         printf("Integer overflow %d %d\n", which, type);
         break;
       case IllegalInstrException:
         printf("Unimplemented or reserved instr %d %d\n", which, type);
         break;
       case SyscallException:
         switch (type)
         {
           // System call Halt
           case SC_Halt:
             DEBUG('a', "\n Shutdown, initiated by user program.");
             printf ("\n Shutdown, initiated by user program.");
             interrupt->Halt();
             break;

           case SC_Sub:
           {
             int op1;
             op1 = machine->ReadRegister(4); 
             int op2;
             op2 = machine->ReadRegister(5);
             int result;
             result = op1 - op2;
             machine->WriteRegister(2, result);
             break;
           }

           case SC_CreateFile:
           {
             int virtAddr;
             char* filename;
             DEBUG('a',"\n SC_Create call ...");
             DEBUG('a',"\n Reading virtual address of filename");
             virtAddr = machine->ReadRegister(4);
             DEBUG ('a',"\n Reading filename.");
             filename = machine->User2System(virtAddr,MaxFileLength+1);
             if (filename == NULL)
             {
               printf("\n Not enough memory in system");
               DEBUG('a',"\n Not enough memory in system");
               machine->WriteRegister(2,-1); 
               delete[] filename;
               break;
             }
             DEBUG('a',"\n Finish reading filename.");
             if (!fileSystem->Create(filename,0))
             {
               printf("\n Error create file '%s'",filename);
               machine->WriteRegister(2,-1);
               delete[] filename;
               break;
             }
             machine->WriteRegister(2,0); 
             delete[] filename;
             break;
           }
           
           case SC_print:
           {          
             int virtAddr;
             char* str;
             virtAddr = machine->ReadRegister(4);
             str = machine->User2System(virtAddr,1000);
             if (str != NULL)
             {
               printf("%s", str);
               machine->WriteRegister(2,0); 
               break;
             }
             printf("");
             machine->WriteRegister(2,0); 
             delete[] str;
             break;
           }
           
           // System call ReadInt: read an integer from user's input
           case SC_ReadInt:
           {
             DEBUG('a', "\nRead an integer\n");
             int number = 0;
             int nDigits;
             bool isNumber = true;
             char* buffer = new char[MAX_INT_LENGTH];
             // Read number string to buffer
             nDigits = gSynchConsole->Read(buffer, MAX_INT_LENGTH);
             int isNegative = 0;
             int i = 0;
             // Count number of '-' to determine whether number is positive or negative
             while (buffer[i] == '-') 
             {
               isNegative++;
               i++;
             }

             // Calculate absolute value of nunber
             // Use by call: int x = ReadInt()
             for(; i < nDigits; i++) 
             {
                // Break if find terminated character
                if (buffer[i] == '\0' || buffer[i] == '\n')
                   break;

                // Break if find a non-digit character
                // Set isNumber false
                if (buffer[i] < '0' || buffer[i] > '9')
                {
                  isNumber = false;
                  break;
                }
                // Update number's value
                else
                {
                  number = number*10 + buffer[i] - '0';
                }
             }
 
             // return to register
             if (!isNumber)
               machine->WriteRegister(2, 0);
             else
               {
                 if (isNegative & 1)
                   number = -number; 
                 machine->WriteRegister(2, number);
               }
             delete[] buffer;
             break;
           }

           // Syscall PrintInt: print an integer to console.
           // Use by call: PrintInt(x), x is an int-type variable
           case SC_PrintInt:
           {
             DEBUG('a', "Print an integer to console.\n");
             int number;
             int nDigits = 0;
             bool isNegative = false;
             number = machine->ReadRegister(4);
             char* buffer = new char[MAX_INT_LENGTH];
             if (number < 0)
             {
               isNegative = true;
               number = -number;
             }

             // store digits in reverse order
             do {
               buffer[nDigits++] = (number % 10) + '0';
               number /= 10;
             } while (number != 0);

             // store digits in right order
             char* strInt = new char[nDigits + 2];
             int i = 0;
             if (isNegative) {
                strInt[i++] = '-';
                nDigits++;
             }
             for(; i < nDigits; i++)
               strInt[i] = buffer[nDigits - i - 1];
             strInt[nDigits] = '\0';

             // print string to console
             gSynchConsole->Write(strInt, nDigits);
             delete[] buffer;
             delete[] strInt;

             // return number of written characters
             machine->WriteRegister(2, nDigits);
             break;
           }

           // Syscall ReadChar: read a character from user's input
           // Use by call: char c = ReadChar()
           case SC_ReadChar:
           {
             char* buffer = new char[MAX_STR_LENGTH];
             int nCharacters = gSynchConsole->Read(buffer, MAX_STR_LENGTH);
             machine->WriteRegister(2, buffer[nCharacters -1]);
             delete[] buffer;
             break;
           }
           
           // Syscall PrintChar: print a character to console
           // Use by call: PrintChar(c), c is a char-type variable
           case SC_PrintChar:
           {
             char c = machine->ReadRegister(4);
             gSynchConsole->Write(&c, 1);
             machine->WriteRegister(2, 0);
             break;
           }

           // Syscall ReadString: read a string from user's input
           // Used by call ReadString(str, STR_LENGTH), str: char[], STR_LENGTH: integer
           case SC_ReadString:
           {
             int virtAddr;
             int length;
             virtAddr = machine->ReadRegister(4);
             length = machine->ReadRegister(5);
             if (length < 0) {
               machine->WriteRegister(2, -1);
               break;
             }
             else {
               char* buffer = new char[length + 1];
               // Read string to buffer
               int res = gSynchConsole->Read(buffer, length);
               if (res == -1) {
                 machine->WriteRegister(2, -1);
                 break;
               }

               int i = 0;
               // Find the terminated character
               while (buffer[i] != '\n' && i < length) i++;
               // Set terminated character to '\0'
               buffer[i] = '\0';
               // Transfer data from kernelspace to userspace
               machine->System2User(virtAddr, length, buffer);
               delete[] buffer;
               machine->WriteRegister(2, 0);
               break;
             }
           }

           // Syscall PrintString: print a string to console
           // Use by call: PringString(str), str: char[]
           case SC_PrintString:
           {
             int virtAddr;
             char* str;
             virtAddr = machine->ReadRegister(4);
             // Transfer data from userspace to kernelspace
             str = machine->User2System(virtAddr, MAX_STR_LENGTH);
             int i = 0;
             // Print each character to console respectively
             while (str[i])
             {
               gSynchConsole->Write(str + i++, 1); 
             }
             machine->WriteRegister(2,0);
             delete[] str;
             break;
           }

           // Syscall Open file:
           case SC_Open:
           {
             int virtAddr;
             char* filename;
             int openFileType;
             virtAddr = machine->ReadRegister(4);
             filename = machine->User2System(virtAddr, MaxFileLength+1);
             openFileType = machine->ReadRegister(5);
             if (openFileType != 0 && openFileType != 1) {
               printf("Open file type can only equal 0 or 1\n");
               machine->WriteRegister(2,-1);
               break;
             } 
             if (filename == NULL) {
               printf("Not enough memory in system\n");
               machine->WriteRegister(2,-1);
               break;
             }
             else {
               OpenFile* of = fileSystem->Open(filename, openFileType);
               if (of != NULL) {
                 int res = currentThread->space->insertFile(of);
                 if (res == -1)
                   printf("Not enough memory\n");
                 else printf("Open file successfully\n");
                 machine->WriteRegister(2,res);
                 break;
               }       
               else {
                 printf("Open file failed\n");
                 machine->WriteRegister(2,-1);
                 break;
               }
             }
           }
           
           // Syscall Close file:
           case SC_Close:
           {
             int id = machine->ReadRegister(4);
             if (id < 0 || id >= FileEntries) {
               printf("Wrong Parameter\n");
               machine->WriteRegister(2,-1);
               break;
             }
             if (currentThread->space->removeFile(id)) {
               printf("Close file successfully\n");
             }
             else {
               printf("File is not opened\n");
             }
             machine->WriteRegister(2,0);
             break;
           }          
           
           // Syscall Read from file:
           case SC_Read:
           {
             int virtAddr;
             int charcount;
             int id;
             virtAddr = machine->ReadRegister(4);
             charcount = machine->ReadRegister(5); 
             id = machine->ReadRegister(6);

             if (charcount < 0) {
                printf("Wrong charcount\n");
                machine->WriteRegister(2,-1);
                break;
             }
  
             if (id == ConsoleInput) {
               if (charcount < 0) {
                 machine->WriteRegister(2, -1);
                 break;
               }
               else {
                 char* buffer = new char[charcount + 1];
                 // Read string to buffer
                 int res = gSynchConsole->Read(buffer, charcount);
                 if (res == -1) {  // End of stream
                   machine->WriteRegister(2, -2); // return -2
                   break;
                 }
                 int i = 0;
                 // Find the terminated character
                 while (buffer[i] != '\n' && i < charcount) i++;
                 // Set terminated character to '\0'
                 buffer[i] = '\0';
                 // Transfer data from kernelspace to userspace
                 machine->System2User(virtAddr, charcount, buffer);
                 delete[] buffer;
                 machine->WriteRegister(2, res);
                 break;
               }
             }
             else if (id == ConsoleOutput) {
               // cannot read from Console Output
               printf("cannot read from Console Output\n");
               machine->WriteRegister(2,-1);
               break;
             }
             // Read from file
             else {
               if (id < 0 || id >= FileEntries) {
                  printf("Wrong id\n");
                  machine->WriteRegister(2,-1);
                  break;
               } 
               OpenFile* of = currentThread->space->returnFile(id);
               if (of == NULL) {
                 printf("File id is not opened\n");
                 machine->WriteRegister(2,-1);
                 break;
               }
               int i = 0;
               char* buffer = new char[charcount + 1];
               buffer[0] = 'a';
               int r = 1;
               while (i < charcount && r) {
                 r = of->Read(buffer + i,1);
                 i++;
               }
               buffer[i] = '\0';
               machine->System2User(virtAddr, charcount, buffer);
               if (r == 0) {
                  machine->WriteRegister(2,-2);
                  delete[] buffer;
                  break;
               }
               machine->WriteRegister(2,i);
               delete[] buffer;
               break;
             }
           }

           // Syscall Write to file
           case SC_Write:
           {
             int virtAddr;
             int charcount;
             int id;
             virtAddr = machine->ReadRegister(4);
             charcount = machine->ReadRegister(5); 
             id = machine->ReadRegister(6);
             if (charcount < 0) {
                printf("Wrong charcount\n");
                machine->WriteRegister(2,-1);
                break;
             }  
             // Transfer data from userspace to kernelspace
             char* buffer = machine->User2System(virtAddr, charcount + 1);
             //int len = 0;
             //while (len < charcount && buffer[len]) len++;
             //buffer[len] = '\0';
             if (id == ConsoleOutput) {
               int i = 0;
               // Print each character to console respectively
               while (i < charcount && buffer[i])
               {
                 gSynchConsole->Write(buffer + i++, 1); 
               }
               machine->WriteRegister(2,i);
               delete[] buffer;
               break;
             }
             else if (id == ConsoleInput) {
               // cannot write to Console Input
               printf("cannot write to Console Input\n");
               machine->WriteRegister(2,-1);
               break;
             }
             // Write to file
             else {
               if (id < 0 || id >= FileEntries) {
                  printf("Wrong id\n");
                  machine->WriteRegister(2,-1);
                  break;
               } 
               OpenFile* of = currentThread->space->returnFile(id);
               if (of == NULL) {
                 printf("File id is not opened\n");
                 machine->WriteRegister(2,-1);
                 break;
               }
               if (of->isReadOnly()) {
                 printf("Cannot write to this file. File is read-only.\n");
                 machine->WriteRegister(2,-1);
                 break;                                   
               }

               int l = 0;
               while (l < charcount && buffer[l]) of->Write(buffer + l++, 1);
               machine->WriteRegister(2,l);
               delete[] buffer;
               break;
             }
           }

           // Seek cursor to pos
           case SC_Seek:
           {
             int pos = machine->ReadRegister(4);
             int id = machine->ReadRegister(5);
             if (id == ConsoleInput || id == ConsoleOutput) {
               printf("Cannot seek in console mode\n");
               machine->WriteRegister(2,-1);
               break;
             }
             if (id < 0 || id >= FileEntries) {
               printf("File id is not valid\n");
               machine->WriteRegister(2,-1);
               break;
             } 
             OpenFile* of = currentThread->space->returnFile(id);
             if (of == NULL) {
               printf("File id is not opened");
               machine->WriteRegister(2,-1);
               break;
             }
             int len = of->Length();
             if (pos == -1 || pos >= len) {
               of->Seek(len);
               machine->WriteRegister(2,len);
               break;
             }
             of->Seek(pos);
             machine->WriteRegister(2,pos);
             break;
           }

           default:
             interrupt->Halt();
         }

         // Update program counters
         machine->registers[PrevPCReg] = machine->registers[PCReg];
         machine->registers[PCReg] = machine->registers[NextPCReg];
         machine->registers[NextPCReg] += 4;
         break;	
    }
}
