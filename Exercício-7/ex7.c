#include <MKL25Z4.h>

int main(void){
	void delayMs(int n);

	SIM->SCGC5 |= 0x400; /*enable clock on port B*/
	PORTB->PCR[19] = 0x100; /*make PTB19 pin as GPIO*/
	PTB->PDDR |= 0x80000; /*make PTB19 as output pin*/

	while(1){
		PTB->PCOR = 0x80000;
		delayMs(2000);
		PTB->PSOR = 0x80000;
		delayMs(2000);
		PTB->PTOR = 0x80000;
		dilayMs(2000);
		PTB->PTOR = 0x80000;
                dilayMs(2000);
	}
}

/*delay n milliseconds*/
void delayMs(int n){
	int i;
	int j;
	for(i=0; i<n; i++){
		for(j=0; j< 7000; j++){}
	}
}
