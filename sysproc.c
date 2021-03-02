#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_trace(void)
{
  int num;

  if(argint(0, &num) < 0)
    return -1;
  myproc()->tracing = num;
  return 22;
  //return trace(num);
}

//Processes || Copy elements from the kernel ptable to user space
extern struct proc * getptable_proc(void);
struct uproc {
int pid;
int ppid;
int state;
uint sz;
char name[16];
};

int sys_getprocs(void){
  int size;
  struct uproc *buf;
  struct proc *p = '\0';
  char *pbuf;
  if (argint(0, &size) <0){
    return -1;
  }
  if (argptr(1, &pbuf,size*sizeof(struct uproc)) <0){
    return -1;
  }

  buf = (struct uproc *)pbuf;
// need to write the getptable_proc function

  p = getptable_proc();

  int count = 0;

//copy from the p table to buf
  for(int i = 0; i < size; i++){
    if (p[i].state == UNUSED)
      break;
    count = count + 1;
    for(int s = 0; s < 16; s++) {
      buf[i].name[s] = p[i].name[s];
    }
    buf[i].pid = p[i].pid;
    buf[i].ppid = p[i].parent->pid;
    buf[i].state = p[i].state;
    buf[i].sz = p[i].sz;
  }

  if (count == 0)
    return -1;
  return count;
}
