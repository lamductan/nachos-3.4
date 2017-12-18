#include "Ptable.h"
#include "system.h"

Ptable::Ptable() {
  //bm = new BitMap(256);
  bmsem = new Semaphore("ptable", 0);
  pcb[0] = new PCB(0);
  //pcb[0]->thread = currentThread;
  pcb[0]->Exec("initThread", 0);
}

Ptable::~Ptable() {
  //delete bm;
  delete bmsem;
}

int Ptable::ExecUpdate(char* name) {
  bmsem->P();
  if (name == NULL) return -1;
  OpenFile* of = fileSystem->Open(name, 0);
  if (of == NULL) return -1;
  if (strcmp(currentThread->name, name) == 0) return -1;
  int freeSlotID = 0;
  for (int i = 1; i < MAX_PROCESS; i++)
    if (pcb[i] == NULL) {
      freeSlotID = i;
      break;
    }
  if (freeSlotID == 0) {
    printf("Ptable is full\n");
    return -1;
  }
  pcb[freeSlotID] = new PCB(freeSlotID);
  int ret = pcb[freeSlotID]->Exec(name, freeSlotID);
  bmsem->V();
  return ret;
}

