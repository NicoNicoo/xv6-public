#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

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

// return how many running process there is
int
sys_getprocs(void)
{

  struct proc *p;
  int cont= 0;
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->state != UNUSED || p->state !=ZOMBIE)
    {
      cont=cont+1;
    }
  }
  return cont;
}

int
sys_physicaladdress(void)
{
  char *viraddr;
  int physicaddr;
  viraddr=argv[1];
  pde_t *pagedir, *pagetab, *entry;

  printf(1,"introducir direccion virtual",viraddr);

  entry = &pagedir[PDX(viradd)];
  if(*entry & PTE_P)
  {
    pagetab=(pte_t*)P2V(PTE_ADDR(*entry));
  }
  else
  {
    cprintf("no existe esta direccion virtual");
    return 1;
  }
  pte_t *pte;
  pte= &pagetab[PTX(viraddr)];
  physicaddr=(char*)V2P(PTE_ADDR(*pte));

  cprintf("DIreccion fisica: %d\n", physicaddr);
  return 0;
}
