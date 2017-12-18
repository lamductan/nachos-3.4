#include "copyright.h"
#include "system.h"
#include "PCB.h"
#ifdef HOST_SPARC
#include <strings.h>
#endif

PCB::PCB(int id) {
  joinsem = new Semaphore("join", id);
  exitsem = new Semaphore("exit", id);
  mutex = new Semaphore("multex", id);
  pid = id;
}

PCB::~PCB() {
  delete joinsem;
  delete exitsem;
  delete mutex;
}

void PCB::StartProcess(int value) {
  //Thread* thread = (Thread*) value;
  currentThread->space->InitRegisters();
  currentThread->space->RestoreState();
  machine->Run();
  ASSERT(FALSE);
}

int PCB::Exec(char *filename, int pid) {
  mutex->P();
  thread = new Thread(filename);
  AddrSpace* space = new AddrSpace(filename);
  if (thread == NULL) {
    printf("Not enough memory\n");
    mutex->V();
    return -1;
  }
  thread->pid = pid;
  thread->space = space;
  strcpy(thread->name, filename);
  this->pid = pid;
  if (pid != 0)
    parentID = currentThread->pid;
  thread->Fork((void(*)(int)) (&PCB::StartProcess), (int)thread);
  //thread->Fork(StartProcess, (int)thread);
  return pid;  
}

int PCB::GetID() {return pid;}

int PCB::GetNumWait() {return numwait;}

//void PCB::IncNumWait() {numwait++;}

//void PCB::DecNumWait() {numwait--;}

int PCB::GetExitCode() {return exitcode;}

void PCB::SetExitCode(int ex) {exitcode = ex;}

//char* PCB::GetFileName() {return }

Thread* PCB::GetThread() {return thread;}

void PCB::SetThread(Thread* t) {thread = t;}

