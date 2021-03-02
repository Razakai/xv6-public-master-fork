#include "types.h"
#include "stat.h"
#include "user.h"

//From proc.h Proc structure
// Per-process state
//enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };
const char* procstate[] = { "UNUSED", "EMBRYO", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE" };
struct uproc {
int pid;
int ppid;
int state;
uint sz;
char name[16];
};

#define MAX_PROC 10
extern int  getprocs(int,struct uproc[10]);
int
main(int argc, char *argv[]){  
  struct uproc ptable[MAX_PROC];
  int err;
  
  err = getprocs(10, ptable);
  if(err <= 0)
    printf(1,"Error getting ptable");
  
  /* TODO output the process details */
  for(int i = 0; i < err; i++){
      printf(1, "process id : %d parent process id: %d state: %s size: %d name: %s\n", ptable[i].pid, ptable[i].ppid, procstate[ptable[i].state], ptable[i].state, ptable[i].name);
  }
  
  exit();
}
