struct bottom_event{
	irq_id_t irq;
	void (*bottom_func)(void *);
};

#define UART_BUFFER_SIZE 16


struct UartBuffer{
	static char *buffer;
	static int nb;
};

volatile struct UartBuffer uartBuffer;

void init_uart_device()
{
	uartBuffer.buffer = kmalloc(UART_BUFFER_SIZE);
	uartBuffer.nb = 0;

}

void top_uart()
{
	
}

void bottom_uart()
{

}
