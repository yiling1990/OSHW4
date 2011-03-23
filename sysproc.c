#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
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
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
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
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
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
sys_nice(void)
{
	// To be implemented.
	int incr;

	if(argint(0, &incr) < 0)
	  return -1;
	return nice(incr);
}

int
sys_getpriority(void)
{
	// To be implemented.
	int pid;

	if(argint(0, &pid) < 0)
	  return -1;
	return getpriority(pid);
}

int
sys_setpriority(void)
{
	// To be implemented.
	int pid;
	int new_priority;

	if(argint(0, &pid) < 0)
	  return -1;
	if(argint(1, &new_priority) < 0)
	  return -1;
	return setpriority(pid, new_priority);
}

int
sys_getaffinity(void)
{
	int pid;
	
	if(argint(0, &pid) < 0)
	  return -1;
	return getaffinity(pid);
}

int
sys_setaffinity(void)
{
	int pid;
	int new_affinity;
	
	if(argint(0, &pid) < 0)
	  return -1;
	if(argint(1, &new_affinity) < 0)
	  return -1;
	return setaffinity(pid, new_affinity);
}
