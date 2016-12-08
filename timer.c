#include "timer.h"
#include "board.h"

#ifdef vexpress_a9
static uint32_t periph_base = 0x0;
static uint32_t timer_cr = 0x0;

void cortex_a9_timer_init()
{
	periph_base = cortex_a9_peripheral_base();
}

void cortex_a9_timer_enable()
{

	timer_cr |= ARM_TIMER_CR_TE;
	arm_mmio_write32(periph_base + ARM_PWT_BASE_OFFSET, ARM_TIMER_CR, timer_cr);
}

void cortex_a9_timer_disable()
{
	timer_cr &= ~(ARM_TIMER_CR_TE);
	arm_mmio_write32(periph_base + ARM_PWT_BASE_OFFSET, ARM_TIMER_CR, timer_cr);
}

void cortex_a9_timer_enable_irq()
{
	timer_cr |= ARM_TIMER_CR_IE;
	arm_mmio_write32(periph_base + ARM_PWT_BASE_OFFSET, ARM_TIMER_CR, timer_cr);
}

void cortex_a9_timer_disable_irq()
{
	timer_cr &= ~(ARM_TIMER_CR_IE);
	arm_mmio_write32(periph_base + ARM_PWT_BASE_OFFSET, ARM_TIMER_CR, timer_cr);
}

void cortex_a9_timer_clear_irq()
{
	// The event flag is cleared when written to 1.
	arm_mmio_write32(periph_base + ARM_PWT_BASE_OFFSET, ARM_TIMER_ISR, 1);
}

void cortex_a9_timer_set_timer(int t)
{
	arm_mmio_write32(periph_base + ARM_PWT_BASE_OFFSET, ARM_TIMER_LR, t);
}

void cortex_a9_timer_set_auto_load(int s)
{
	if (s)
		timer_cr |= ARM_TIMER_CR_AR;
	else
		timer_cr &= ~(ARM_TIMER_CR_AR);
	arm_mmio_write32(periph_base + ARM_PWT_BASE_OFFSET, ARM_TIMER_CR, timer_cr);
}
#endif
