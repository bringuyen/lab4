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

int shm_open(int id, char ** pointer) {
	struct proc *curproc = myproc();
	int i;
	char *va;
	va = (char*)PGROUNDUP(curr->sz);
	
	acquire(&(shm_table.lock));
	for (i = 0; i <= 64; ++i) {
		if(shm_table.shm_pages[i].id == id) {
			mappages(curproc->pgdir, va, PGSIZE, V2P(sdhm_table.shm_pages[i]->frame), PTE_W|PTE_U);
			shm_table.shm_pages[i].refcnt++;
			*pointer = (char *)va;
			release(&(shm_table.lock));
			return shm_table.shm_pages[i].refcnt;
		}
	}
	for(i = 0; i < 64; ++i) {
		if(shm_table.shm_pages[i].id == 0) {
			struct shm_page *page = shm_table.shm_pages + i;
			page->id = id;
			page-<frame = kalloc();
			memset(page->frame,0,PGSIZE);
			page->refcnt += 1;
			mappages(curproc->pgdir, va, PGSIZE, V2P(page->frame), PTE_W|PTE_U);
			*pointer = (char *)va;
			curr->sz = (uint) va;
			page-refcnt += 1;
			release(&(shm_table.lock));
			return page->refcnt;
	}
}




return 0; //added to remove compiler warning -- you should decide what to return
}


int shm_close(int id) {
//you write this too!
	int i;
	acquire(&(shm_table.lock));
	for ( i = 0; i < 64; i++) {
		if (shm_table.shm_pages[i].id = id) {
			shm_table.shm_pages[i].refcnt -= 1;
				if (!shm_table.shm_pages[i].refcnt) {
					shm_table.shm_pages[i].id =0;
					shm_table.shm_pages[i].frame =0;
					shm_table.shm_pages[i].refcnt =0;
				}
		} 
	}
	release(&(shm_table.lock));

return 0; //added to remove compiler warning -- you should decide what to return
}
