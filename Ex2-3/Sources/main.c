#define SIM_SCGC5   (*((volatile unsigned int*)0x40048038)) /* System Integration Module System Clock Gating Control Register 5 */
#define PORTB_PCR19 (*((volatile unsigned int*)0x4004A04C)) /* Port B Pin Control Register 19 */
#define GPIO_PDDR   (*((volatile unsigned int*)0x400FF054)) /* Port B Data Direction Register */
#define GPIO_PDOR   (*((volatile unsigned int*)0x400FF040)) /* Port B Data Output Register */
#define GPIOB_PTOR  (*((volatile unsigned int*)0x400FF04C)) /* Port B Toggle Output Register */

#define PORTB_PCR18 (*((volatile unsigned int*)0x4004A048)) /* Port B Pin Control Register 18 */

#define GREEN_PIN     (19)
#define GREEN_SHIFT   (1<<GREEN_PIN)
#define GREEN_TOGGLE  (GPIOB_PTOR |= GREEN_SHIFT)
#define RED_PIN       (18)
#define RED_SHIFT     (1<<RED_PIN)
#define RED_TOGGLE    (GPIOB_PTOR |= RED_SHIFT)

void delayMs(int n) {
	int i, j;
	for(i = 0 ; i < n; i++)
		for (j = 0; j < 7000; j++) {}
}

int main(void) {
	SIM_SCGC5 |= 0x400;

	PORTB_PCR19 |= 0x0100;
	PORTB_PCR18 |= 0x0100;

	GPIO_PDDR |= GREEN_SHIFT;
	GPIO_PDOR |= GREEN_SHIFT;
	
	GPIO_PDDR |= RED_SHIFT;
	GPIO_PDOR |= RED_SHIFT;
	
	
	// Tarefa 3)
	while(1) {
			GREEN_TOGGLE;
			delayMs(200);
			GREEN_TOGGLE;
			delayMs(500);
		}
	// Tarefa 5)
	while(1) {
		GREEN_TOGGLE;
		RED_TOGGLE;
		delayMs(200);
		GREEN_TOGGLE;
		RED_TOGGLE;
		delayMs(500);
	}
	return 0;
}
