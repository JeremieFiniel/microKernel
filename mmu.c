#include "mmu.h"
#include "kmem.h"

#ifdef vexpress_a9

/*
 * ARM Architecture Reference Manual
 * Table B4-1 First-level descriptor format page 727
 *
 * http://www.embedded-bits.co.uk/2011/mmucode/
 *
 * Bits 31:20 - Section base address
 * Bits 11:10 - Access permissions
 * Bits 8:5   - Domain
 * Bit  3:2   - Cachable / Bufferable
 * Bits 1:0   - Always 0b10 for a section page table entry / descriptor
 *
 * B5.3.1 Data and Instruction access permissions page 760
 * AP:
 * AP   Privileged User
 * 0b00 No access  No access
 * 0b01 Read/write No access
 * 0b10 Read/write Read only
 * 0b11 Read/write Read/write
 *
 * Domain:
 * reg 3
 */

static sectionPageTable *pageTables;

extern void _arm_ttrb(sectionPageTable*, uint32_t);
extern uint32_t _kpage_low;
extern uint32_t _kpage_high;

void mmu_init()
{
	pageTables = (uintptr_t)&_kpage_low;

	int i;
	for (i = 0; i < 0x1000; i ++)
	{
		sectionPageTable p;
		p = i << 20; //section base
		p |= 3 << 10; // AP
		p |= 0 << 4; // domaine 0
		p |= 0 << 2; // C B
		p |= 2 << 0; // section entry

		arm_mmio_write32(pageTables+i, 0, p);
	}

	_arm_ttrb(pageTables, 0x5555555F);
}

#endif
