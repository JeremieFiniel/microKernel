#ifndef MMU_H_
#define MMU_H_

#include "board.h"

#ifdef vexpress_a9

typedef uint32_t sectionPageTable; 

void mmu_init();

#endif
#endif
