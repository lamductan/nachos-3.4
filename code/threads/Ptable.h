#ifndef PTABLE_H
#define PTABLE_H

#include "PCB.h"
#include "bitmap.h"
//#include "system.h"
//#include "synch.h"

#ifndef MAX_PROCESS
#define MAX_PROCESS 10
#endif

class Ptable {
  private:
    BitMap* bm;
    PCB* pcb[MAX_PROCESS];  
    //int psize;
    Semaphore* bmsem;
  public:
    Ptable();
    ~Ptable();
    int ExecUpdate(char* name);
    //int ExitUpdate(int ec);
    int JoinUpdate(int id);
    int ExitUpdate(int exitcode);
    //int getFreeSlot();
    //bool isExist(int pid);
    //void remove(int pid);
};

#endif
