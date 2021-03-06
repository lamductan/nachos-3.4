#ifndef PCB_H
#define PCB_H

#include "copyright.h"
#include "filesys.h"
#include "synch.h"
#include "thread.h"

#ifndef MAX_PROCESS
#define MAX_PROCESS 10
#endif

#define MAX_PCB_NAME_SIZE 50

class Semaphore;

class PCB {
  private:
    Semaphore* joinsem;     // semaphore cho quá trình join
    Semaphore* exitsem;     // semaphore cho quá trình exit
    Semaphore* mutex;      // semaphore cho quá trình truy xuất đọc quyền
    Thread* thread;    
    int exitcode;
    int processID;
    int numwait;            // số tiến trình đã join
    OpenFile** fileEntry;
  public:
    int parentID;           // ID của tiến trình cha
    char filename[MAX_PCB_NAME_SIZE];
    PCB(int id);            // constructor
    ~PCB();                 // destructor
    // nạp chương trình có tên lưu trong biến filename và processID là pid
    int Exec(int argc, char **argv, int ProcessID);  // Tạo 1 thread mới có tên là filename và process là pid
    int GetID(); // Trả về ProcessID của tiến trình gọi thực hiện
    int GetNumWait(); // Trả về số lượng tiến trình chờ
    void IncNumWait(); // Tăng số tiến trình chờ
    void DecNumWait(); // Giảm số tiến trình chờ
    void JoinWait();  // 1. Tiến trình cha đợi tiến trình con kết thúc
    void ExitWait();  // 4. Tiến trình con kết thúc
    void JoinRelease(); // 2. Báo cho tiến trình cha thực thi tiếp
    void ExitRelease(); // 3. Cho phép tiến trình con kết thúc
    void SetExitCode(int ec); // Đặt exitcode của tiến trình
    int GetExitCode(); // Trả về exitcode
    //void SetFileName(char* fn); // Đặt tên của tiến trình
    //char* GetFileName(); // Trả về tên của tiến trình
    Thread* GetThread();
    void SetThread(Thread* t);
};

//void StartProcess_2(int);

#endif
