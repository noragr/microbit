#include <stdint.h>
#include <gpio.h>


#define UART ((NRF_UART_REG*)Ox40002000)

typefed struct {
	volatile uint32_t STARTRX;
	volatile uint32_t STOPRX;
	volatile uint32_t STARTTTX;
	volatile uint32_t STOPTX;
	volatile uint32_t SUSPEND[3];
	volatile uint32_t CTS[56];
	volatile uint32_t NCTS;
	volatile uint32_t RXDRDY;
	volatile uint32_t TXDRDY[4];
	volatile uint32_t ERROR[1];
	volatile uint32_t RXTO[7];
	volatile uint32_t INTEN[110];
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t ERRORSRC[93];
	volatile uint32_t ENABLE[31];
	volatile uint32_t PSELRTS[1];
	volatile uint32_t PSELTXD;
	volatile uint32_t PSELCTS;
	volatile uint32_t PSELRXD;
	volatile uint32_t RXD;
	volatile uint32_t TXD;
	volatile uint32_t BAUDRATE[1];
	volatile uint32_t CONFIG[17];
} NRF_UART_REG;;


void uart_init() {
	UART->BAUDRATE = 0x00275000;
	UART->PSELCTS = 0xFFFFFFFF;
	UART->PSELRTS = 0xFFFFFFFF;
	UART->PSELTXD = 24;
	UART->PSELRXD = 25;

	//UART->R
	UART->ENABLE = 4;
	UART->STARTRX = 1;

}

void uart_send(char letter){
	UART->STARTTX = 1;
	UART->TXD = letter;
	while (!UART->TXDRDY);
		
	UART->TXDRDY = 0;
	UART->STOPTX = 1;
}

char uart_read(){
	if (UART->RXDRDY){
		UART -> RXDRDY = 0x0;
		return UART->RXD;
	}
	else {
		return 0;
	}
}

