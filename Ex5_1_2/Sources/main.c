#include "derivative.h" /* include peripheral declarations */

void ADC0_init(void);
void LED_set(int s);
void LED_init(void);

int main(void)
{
	 short int result;

	 LED_init();
	 ADC0_init();

	 while (1)
	 {
	     ADC0_SC1A = 0x10; // inicia a conversao, single-ended, AD8 selecionado como input

	     while (!(ADC0_SC1A & 0x80)){} //aguarda a conversao acabar (faco um AND entre a flag COCO e 1, quando os 2 forem 1, retorna 1 e para o while)

	     result = ADC0_RA; // le o resultado da conversao na var result
	     LED_set(result >> 7); // seta o led com base no bit 7 do result
	        
	 }
}

void ADC0_init(void) {
    SIM_SCGC5 |= (1<<10); // enable clock PORTB (pg. 206)
    SIM_SCGC6 |= 0x8000000; // enable clock ADC0 (pg. 207)
    PORTE_PCR0 = 0; // enable PTB0 pin out
    ADC0_SC2 &= ~0x40; // software trigger
    ADC0_CFG1 = 0x54;
}

void LED_init(void) {
    SIM_SCGC5 |= 0x1000; // enable clock PORTD
    SIM_SCGC5 |= 0x400; // enable clock PORTB
    // posso dar enable nos dois clocks ao mesmo tempo? sim!
    PORTD_PCR1 = 0x100; // enable PTD1 as GPIO (pg. 183) (Blue LED)
    PORTB_PCR19 = 0x100; // enable PTB19 as GPIO (Green LED)
    PORTB_PCR18 = 0x100; // enable PTB18 as GPIO (Red LED)

    GPIOB_PDDR |= 0x80000; // make PTB19 (Green LED) as output (pg. 778) (bit relativo ao numero da porta)
    GPIOB_PDDR |= 0x40000; // make PTB18 as output (Red LED)
    GPIOB_PDDR |= 0x02; // make PTD1 as output (Blue LED)
}

void LED_set(int s) {
    // Red LED
    if (s & 1) { // usa BIT 0 de s
        GPIOB_PCOR = 0x40000; // turn on
    } else {
        GPIOB_PSOR = 0x40000; // turn off
    }
    // Green LED
    if (s & 2) { //usa BIT 1 do s
        GPIOB_PCOR = 0x80000; // turn on
    } else {
        GPIOB_PSOR = 0x40000; // turn off
    }
    // Blue LED
    if (s & 4) { //usa bit 2 do s
        GPIOD_PCOR = 0x02; // turn on
    } else {
        GPIOD_PSOR = 0x02; // turn off
    }
}
