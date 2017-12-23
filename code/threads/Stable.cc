#include "Stable.h"

Stable::Stable() {
  for(int i = 0; i < MAX_SEMAPHORE; i++)
    semTab[i] = NULL;
  bm = new BitMap(MAX_SEMAPHORE);
}

Stable::~Stable() {
  for(int i = 0; i < MAX_SEMAPHORE; i++)
    if (semTab[i]) delete semTab[i];
}

int Stable::Create(char* name, int init) {
  for(int i = 0; i < MAX_SEMAPHORE; i++)
    if (semTab[i] && strcmp(semTab[i]->getName(), name) == 0)
        return -1;
  int freeSlot = bm->Find();
  if (freeSlot == -1)
    return -1;
  bm->Mark(freeSlot);
  semTab[freeSlot] = new Sem(name, init);
  return 0;
}

int Stable::Wait(char *name) {
  for(int i = 0; i < MAX_SEMAPHORE; i++)
    if (semTab[i] && strcmp(semTab[i]->getName(), name) == 0) {
        semTab[i]->wait();
        return 0;
    }
  return -1;
}

int Stable::Signal(char *name) {
  for(int i = 0; i < MAX_SEMAPHORE; i++)
    if (semTab[i] && strcmp(semTab[i]->getName(), name) == 0) {
        semTab[i]->signal();
        return 0;
    }
  return -1;
}
