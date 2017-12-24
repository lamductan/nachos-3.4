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

    OpenFile** fileEntry;
  public:
    Ptable();
    ~Ptable();
    int ExecUpdate(int argc, char** argv);
    //int ExitUpdate(int ec);
    int JoinUpdate(int id);
    int ExitUpdate(int exitcode);
    
    int insertFile(OpenFile * of);      //returns file descriptor
    OpenFile * returnFile(int fd);      //checks if given file descriptor exists
    bool removeFile(int fd) ;           //removes given file descriptor;
    //int getFreeSlot();
    //bool isExist(int pid);
    //void remove(int pid);
};

#endif
