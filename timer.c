#include "timer.h"
#include "board.h"

static uint32_t periph_base = 0x0;

void cortex_a9_timer_init()
{
	periph_base = cortex_a9_peripheral_base();
}

void cortex_a9_timer_enable_irq()
{
	uint32_t *control_register = periph_base + ARM_PWT_BASE_OFFSET + ARM_TIMER_CR;
	*control_register |= ARM_TIMER_CR_TE;
}

void cortex_a9_timer_disable_irq()
{
	uint32_t *control_register = periph_base + ARM_PWT_BASE_OFFSET + ARM_TIMER_CR;
	*control_register &= ~(ARM_TIMER_CR_TE);
}

void cortex_a9_timer_clear_irq()
{
	uint32_t *interrupt_register = periph_base + ARM_PWT_BASE_OFFSET + ARM_TIMER_ISR;
	// The event flag is cleared when written to 1.
	*interrupt_register = 1;
}

void cortex_a9_timer_set_timer(int t)
{
	uint32_t *load_register = periph_base + ARM_PWT_BASE_OFFSET + ARM_TIMER_LR;
	*load_register = t;
}

void cortex_a9_timer_set_auto_load(int s)
{
	uint32_t *control_register = periph_base + ARM_PWT_BASE_OFFSET + ARM_TIMER_CR;
	if (s)
		*control_register |= ARM_TIMER_CR_AR;
	else
		*control_register &= ~(ARM_TIMER_CR_AR);
}
