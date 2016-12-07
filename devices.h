#ifndef DEVICES_H_
#define DEVICES_H_

void init_uart_device_driver();
void top_uart();
void bottom_uart();

struct Bottom_event{
	irq_id_t irq;
	void (*bottom_func)(void);
	struct Bottom_event *next;
};

#endif
