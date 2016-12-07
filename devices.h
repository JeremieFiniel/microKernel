#ifndef DEVICES_H_
#define DEVICES_H_

#include "board.h"
#include "pl011.h"
#ifdef vexpress_a9
#include "gic.h"
#else
#include "pl190.h"
#endif

void init_uart_device_driver();
void top_uart();
void bottom_uart();

struct Bottom_event{
	irq_id_t irq;
	void (*bottom_func)(void);
	struct Bottom_event *next;
};

#endif
