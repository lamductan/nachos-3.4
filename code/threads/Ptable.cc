#include "Ptable.h"
#include "system.h"

Ptable::Ptable() {
  bm = new BitMap(MAX_PROCESS);
  bmsem = new Semaphore("bmsem", 1);
  for(int i = 0; i < MAX_PROCESS; i++)
    pcb[i] = NULL;
}

Ptable::~Ptable() {
  delete bm;
  delete bmsem;
  for(int i = 0; i < MAX_PROCESS; i++)
    if (pcb[i] != NULL) delete pcb[i];
}

int Ptable::ExecUpdate(char* name) {
  bmsem->P();
  if (name == NULL) return -1;
  OpenFile* of = fileSystem->Open(name, 0);
  if (of == NULL) return -1;
  if (strcmp(currentThread->name, name) == 0) return -1;
  int freeSlotID;
  int ParentID = -1;
  
  if (bm->NumClear() == MAX_PROCESS) {
    freeSlotID = 0;
    bm->Mark(freeSlotID);
  }
  else {
    if (strcmp(currentThread->name, name) == 0) {
      bmsem->V();
      return -1;
    }
    for (int i = 0; i < MAX_PROCESS; i++)
      if (pcb[i] && pcb[i]->GetThread() == currentThread) {
        ParentID = i;
        break;
      }
    freeSlotID = bm->Find();
    if (ParentID == -1) {
      bmsem->V();
      return -1;
    }
  }

  int ProcessID = freeSlotID;
  pcb[ProcessID] = new PCB(ProcessID);
  pcb[ProcessID]->parentID = ParentID;
  int ret = pcb[ProcessID]->Exec(name, ProcessID);
  if (ret == -1) {
    bm->Clear(ProcessID);
    delete pcb[ProcessID];
  }
  bmsem->V();
  return ret;
}

int Ptable::JoinUpdate(int id) {
  if (id < 0 || id >= MAX_PROCESS) {
    printf("Illegal process id\n");
    return -1;
  }
  if (pcb[id] == NULL)
    return -1;
  if (pcb[id]->parentID != currentThread->pid) {
    printf("Join Process is not child of current Process\n");
    return -1;
  }
  PCB *currentProcess = pcb[currentThread->pid];
  currentProcess->IncNumWait();
  currentProcess->JoinWait();
  currentProcess->ExitRelease();
  return 0;
}

int Ptable::ExitUpdate(int exitcode) {
  if (currentThread->pid == 0) {
    interrupt->Halt();
    return exitcode;
  }

  PCB *currentProcess = pcb[currentThread->pid];
  PCB *parentProcess = pcb[currentProcess->parentID];
  currentProcess->SetExitCode(exitcode);
  parentProcess->JoinRelease();
  parentProcess->ExitWait();
  bm->Clear(currentProcess->GetID());
  delete currentProcess;
  currentProcess = NULL;
  delete currentThread->space;
  currentThread->Finish();
  return exitcode;
}

