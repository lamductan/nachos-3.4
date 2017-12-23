#ifndef STABLE_H
#define STABLE_H

#include "Sem.h"
#include "bitmap.h"

#ifndef MAX_SEMAPHORE
#define MAX_SEMAPHORE 10
#endif

class Stable {
  private:
    BitMap* bm;
    Sem* semTab[MAX_SEMAPHORE];
  public:
    Stable();
    ~Stable();
    int Create(char* name, int init);
    int Wait(char* name);
    int Signal(char* name);
    //int FindFreeSlot(int id);
};
#endif

