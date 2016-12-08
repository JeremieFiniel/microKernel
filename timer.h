#ifndef TIMER_H_
#define TIMER_H_

#ifdef vexpress_a9
/*
 * Cortex_a9 MPCore, Thechnical Reference Manual
 * 4.2 Private timer and watchdog registers (page 64)
 */

#define ARM_TIMER_LR 0x0000		// load register
#define ARM_TIMER_COUR 0x0004	// counter register
#define ARM_TIMER_CR 0x0008 	// control register
#define ARM_TIMER_ISR 0x000C 	// interrupt state register

#define ARM_TIMER_CR_TE (1<<0)	// time enable
#define ARM_TIMER_CR_AR (1<<1)	// auto reload
#define ARM_TIMER_CR_IE (1<<2)	// irq enable

void cortex_a9_timer_init();
void cortex_a9_timer_enable();
void cortex_a9_timer_disable();

void cortex_a9_timer_enable_irq();
void cortex_a9_timer_disable_irq();
void cortex_a9_timer_clear_irq();
void cortex_a9_timer_set_timer(int t);
void cortex_a9_timer_set_auto_load(int s);
#endif

#endif
