#include "devices.h"
#include "pl011.h"


#define UART_BUFFER_SIZE 16

struct UartBuffer{
	static char *buffer;
	static int start;
	static int end;
};

volatile struct UartBuffer uartBuffer;

extern struct Bottom_event* bottom_event_empty;
extern struct Bottom_event* bottom_event_to_handle;

void init_uart_device()
{
	uartBuffer.buffer = kmalloc(UART_BUFFER_SIZE);
	uartBuffer.start = 0;
	uartBuffer.end = 0;

}

void top_uart()
{
	char c;
	uart_receive(stdin, &c);
	if ((uartBuffer.end + 1) % UART_BUFFER_SIZE != uartBuffer.start && bottom_event_empty != NULL) 
	{
		uartBuffer.buffer[uartBuffer.end] = c;
		uartBuffer.end = (uartBuffer.end + 1) % UART_BUFFER_SIZE;

		bottom_event_empty->irq = UART0_IRQ;
		bottom_event_empty->bottom_func = &bottom_uart;

		struct Bottom_event* event;
		event = bottom_event_empty->next;
		bottom_event_empty->next = bottom_event_to_handle;
		bottom_event_empty = event;
	}

	//acknowledge the irq;
	uart_ack_irqs(stdin);
}

void bottom_uart()
{
	char c;
	
	/*
	 * Here we do not have problem of concurrency becose top modify end variable and bottom modify start variable. 
	 * What will be possible is to just consume one character but it means charachter will take more time to be consume.
	 */

	while (uartBuffer.start != uartBuffer.end)
	{
		c = uartBuffer.buffer[uartBuffer.start];
		uartBuffer.start ++; 
		if (c == 13) {
			uart_send(stdout, '\r');
			uart_send(stdout, '\n');
		} else {
			uart_send(stdout, c);
		}
	}
}

