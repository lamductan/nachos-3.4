#include "copyright.h"
#include "system.h"
#include "PCB.h"
#include <string>
#ifdef HOST_SPARC
#include <strings.h>
#endif

struct Args{
  int argc;
  char** argv;
  int userSpaceArgv;
};

void deleteArgs(int argc, char **tokens){
  for (int i = 0; i < argc; i++)
    delete[] tokens[i];
  delete[] tokens;
}


void StartProcess_2(int argPtr) {
  currentThread->space->InitRegisters();
  currentThread->space->RestoreState();
  Args* userSpaceArgs = (Args*) argPtr;

  currentThread->space->copyArguments(userSpaceArgs->argc,
				      userSpaceArgs->argv,
				      userSpaceArgs->userSpaceArgv);

  machine->WriteRegister(4,userSpaceArgs->argc);
  machine->WriteRegister(5,userSpaceArgs->userSpaceArgv);

  deleteArgs(userSpaceArgs->argc,userSpaceArgs->argv);

  machine->Run();
  ASSERT(FALSE);
}

PCB::PCB(int id) {
  joinsem = new Semaphore("join", 0);
  exitsem = new Semaphore("exit", 1);
  mutex = new Semaphore("mutex", 1);
  processID = id;
  parentID = -1;
  memset(filename, 0, MAX_PCB_NAME_SIZE);

    fileEntry = new OpenFile*[FileEntries];
    fileSystem->Create("stdin",0);
    fileSystem->Create("stdout",0);
    fileEntry[0] = fileSystem->Open("stdin");
    fileEntry[1] = fileSystem->Open("stdout");
    for(int i = 2; i < FileEntries; i++)
       fileEntry[i] = NULL;
}

PCB::~PCB() {
  delete joinsem;
  delete exitsem;
  delete mutex;
}

int PCB::Exec(int argc, char** argv, int ProcessID) {
  strncpy(filename, argv[0], MAX_PCB_NAME_SIZE - 1);
  mutex->P();
  if (filename == NULL || ProcessID < 0 || ProcessID >= MAX_PROCESS) {
    mutex->V();
    return -1;
  }
  OpenFile *executable = fileSystem->Open(filename, 0);
  if (executable == NULL) {
    mutex->V();
    deleteArgs(argc,argv);
    return -1;
  }
  
  delete executable;
  thread = new Thread(filename);
  if (thread == NULL) {
    printf("Not enough memory\n");
    mutex->V();
    return -1;
  }
  thread->pid = ProcessID;
  
  int userSpaceArgv;
  AddrSpace* addrSpace = new AddrSpace(filename, argc, argv, &userSpaceArgv);
  if (addrSpace == NULL) {
    delete executable;
    delete thread;
    deleteArgs(argc,argv);
    return -1;
  }
  thread->space = addrSpace;

  if (ProcessID == 0) {
    Thread* oldThread = currentThread;
    currentThread = thread;
    delete oldThread;
    thread->setStatus(RUNNING);
    thread->space->InitRegisters();
    thread->space->RestoreState();
  }
  else {
    Args* userSpaceArgs = new Args;
    userSpaceArgs->argc = argc;
    userSpaceArgs->argv = argv;
    userSpaceArgs->userSpaceArgv = userSpaceArgv;
    thread->Fork(StartProcess_2, (int)userSpaceArgs);
  }
  mutex->V();
  return ProcessID;  
}

int PCB::GetID() {return processID;}

int PCB::GetNumWait() {return numwait;}

void PCB::IncNumWait() {numwait++;}

void PCB::DecNumWait() {numwait--;}

void PCB::JoinWait() {
  joinsem->P();
}

void PCB::JoinRelease() {
  joinsem->V();
}

void PCB::ExitRelease() {
  exitsem->V();
}

void PCB::ExitWait() {
  exitsem->P();
}

int PCB::GetExitCode() {return exitcode;}

void PCB::SetExitCode(int ex) {exitcode = ex;}

//char* PCB::GetFileName() {return }

Thread* PCB::GetThread() {return thread;}

void PCB::SetThread(Thread* t) {thread = t;}

