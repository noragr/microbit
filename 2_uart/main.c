#include "uart.h"
#include "gpio.h"
#include <stdio.h>

ssize_t _write(int fd, const void *buf, size_t count);

int main(){
	uart_init();
	
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;

	int sleep = 0;
	int toggle = 1;
	while(1){
		// send A om A trykkes 
		if (!(GPIO->IN & (1 <<17))){
			uart_send('A');
		}
		// send B om B trykkes 
		if (!(GPIO->IN & (1<<26))){
			uart_send('B');
		}
		// skru av og på led-matrise om bokstav sendes. 
		if (uart_read() != '\0') {

			if (toggle) {
				for(int i = 13; i <= 15; i++) {
					GPIO -> OUTCLR = (1<<i);
				}
				toggle = 0;
				iprintf("Norway has %d counties.\n\r",18);
			}else {
				for(int i = 13; i <= 15; i++){
					GPIO->OUTSET = (1 << i);
				}

				toggle = 1;
			}
		}
		sleep = 10000;
		while(--sleep);
	}
	ssize_t _write(int fd, const void *buf, size_t count) {
		char * letter = (char *)(buf);
		for (int i = 0; i < count; i++) {
			uart_send(*letter);
			letter++;
		}
		return count;
	}

	return 0;
}