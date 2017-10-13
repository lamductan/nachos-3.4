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
           case SC_Create:
           {
             int virtAddr;
             char* filename;
             DEBUG('a',"\n SC_Create call ...");
             DEBUG('a',"\n Reading virtual address of filename");
             // Lấy tham số tên tập tin từ thanh ghi r4
             virtAddr = machine->ReadRegister(4);
             DEBUG ('a',"\n Reading filename.");
             // MaxFileLength là = 32
             filename = machine->User2System(virtAddr,MaxFileLength+1);
             if (filename == NULL)
             {
               printf("\n Not enough memory in system");
               DEBUG('a',"\n Not enough memory in system");
               machine->WriteRegister(2,-1); // trả về lỗi cho chương
               // trình người dùng

               delete filename;
               break;
             }
            DEBUG('a',"\n Finish reading filename.");
             if (!fileSystem->Create(filename,0))
             {
               printf("\n Error create file '%s'",filename);
               machine->WriteRegister(2,-1);
               delete filename;
               break;
             }
             machine->WriteRegister(2,0); // trả về cho chương trình
             // người dùng thành công

             delete filename;
             break;
           }
           
           case SC_print:
           {          
             int virtAddr;
             char* str;
             // Lấy tham số chuoi từ thanh ghi r4
             virtAddr = machine->ReadRegister(4);
             str = machine->User2System(virtAddr,1000);
             if (str != NULL)
             {
               printf("%s", str);
               machine->WriteRegister(2,0); // trả về cho chương trình
             // người dùng thành công 
               break;
             }
             printf("");
             machine->WriteRegister(2,0); // trả về cho chương trình
             // người dùng thành công

             delete str;
             break;
           }

           case SC_ReadInt:
           {
             DEBUG('a', "\nRead an integer\n");
             int number = 0;
             int nDigits;
             bool isNumber = true;
             char* buffer = new char[MAX_INT_LENGTH];
             nDigits = gSynchConsole->Read(buffer, MAX_INT_LENGTH);
             int isNegative = 0;
             int i = 0;
             while (buffer[i] == '-') 
             {
               isNegative++;
               i++;
             }

             for(; i < nDigits; i++) 
             {
                if (buffer[i] == '\0' || buffer[i] == '\n')
                   break;

                if (buffer[i] < '0' || buffer[i] > '9')
                {
                  isNumber = false;
                  break;
                }
                else
                {
                  number = number*10 + buffer[i] - '0';
                }
             }

             if (!isNumber)
               machine->WriteRegister(2, 0);
             else
               {
                 if (isNegative & 1)
                   number = -number; 
                 machine->WriteRegister(2, number);
               }
             delete buffer;
             break;
           }

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
             do {
               buffer[nDigits++] = (number % 10) + '0';
               number /= 10;
             } while (number != 0);
             char* strInt = new char[nDigits + 2];
             int i = 0;
             if (isNegative) {
                strInt[i++] = '-';
                nDigits++;
             }
             for(; i < nDigits; i++)
               strInt[i] = buffer[nDigits - i - 1];
             strInt[nDigits] = '\0';
             gSynchConsole->Write(strInt, nDigits);
             delete buffer;
             delete strInt;
             break;
           }

           case SC_ReadChar:
           {
             char* buffer = new char[1];
             int nCharacters = gSynchConsole->Read(buffer, 1);
             machine->WriteRegister(2, buffer[0]);
             delete buffer;
             break;
           }
           
           case SC_PrintChar:
           {
             char c = machine->ReadRegister(4);
             gSynchConsole->Write(&c, 1);
             machine->WriteRegister(2, 0);
             break;
           }

           case SC_ReadString:
           {
             int virtAddr;
             char* str;
             int length;
             virtAddr = machine->ReadRegister(4);
             length = machine->ReadRegister(5);
             if (length < 0) {
               machine->WriteRegister(2, -1);
               break;
             }
             else {
               char* buffer = new char[length + 1];
               gSynchConsole->Read(buffer, length);
               int i = 0;
               while (buffer[i] != '\n' && i < length) i++;
               buffer[i] = '\0';
               machine->System2User(virtAddr, length, buffer);
               delete buffer;
               machine->WriteRegister(2, 0);
               break;
             }
           }

           case SC_PrintString:
           {
             int virtAddr;
             char* str;
             virtAddr = machine->ReadRegister(4);
             str = machine->User2System(virtAddr, MAX_STR_LENGTH);
             int i = 0;
             while (str[i])
             {
               gSynchConsole->Write(str + i++, 1); 
             }
             machine->WriteRegister(2,0);
             delete str;
             break;
           }          
         }
         machine->registers[PrevPCReg] = machine->registers[PCReg];
         machine->registers[PCReg] = machine->registers[NextPCReg];
         machine->registers[NextPCReg] += 4;
         break;	
    }
}
