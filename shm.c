#include "param.h"
#include "types.h"
#include "defs.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

struct {
  struct spinlock lock;
  struct shm_page {
    uint id;
    char *frame;
    int refcnt;
  } shm_pages[64];
} shm_table;

void shminit() {
  int i;
  initlock(&(shm_table.lock), "SHM lock");
  acquire(&(shm_table.lock));
  for (i = 0; i< 64; i++) {
    shm_table.shm_pages[i].id =0;
    shm_table.shm_pages[i].frame =0;
    shm_table.shm_pages[i].refcnt =0;
  }
  release(&(shm_table.lock));
}

struct proc *curproc = myproc();
for (int i = 0; i <= 64; ++i) {
	if(id == shm_pages[i]) {
		mappages(curproc->pgdir, PGROUNDUP(sz), PGSIZE, V2P(shm_pages[i]->frame), PTE_W|PTE_U);
		refcnt++;
		*pointer = (char *)PGROUNDUP(sz);
		return 0;
	}
	for(int i = 0; i <= 64; ++i) {
		if(shm_pages[i] == 0) {
			shm_pages[i] = id;
			shm_pages[i]->frame = kalloc();
			refcnt = 1;
			mappages(curproc->pgdir, PGROUNDUP(sz), PGSIZE, V2P(shm_pages[i]->frame), PTE_W|PTE_U);
			*pointer = (char *)PGROUNDUP(sz);
}





return 0; //added to remove compiler warning -- you should decide what to return
}


int shm_close(int id) {
//you write this too!




return 0; //added to remove compiler warning -- you should decide what to return
}
