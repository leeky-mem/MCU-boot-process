#include <stdint.h>

/* These are defined in the linker script */
extern uint32_t _etext;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sstack;
extern uint32_t _estack;

/* Prototypes of Exception handlers*/
void Reset_Handler(void);
void NMI_Handler(void);
void HardFault_Handler(void);

/* Forward define main */
int main(void);

/*Definition of the vector table.
* It is an array of function pointers, while the first index is the initial 
* stack pointer which is not a function but we need to put it at the inning of 
* the vector table.
* The used attribute tells the linker not to remove this even if the variable 
* is not referenced in the code.
* The section attribute tell the compiler to put the vector table in the vectors
* section defined in the linker script.
*/
__attribute__ ((used, section(".vectors")))
void (* const vectors[])(void) =
{
	(void(*const)(void))&_estack,
	Reset_Handler,
	NMI_Handler,
	HardFault_Handler,
};

void Reset_Handler(void)
{
	/*Copy initial values from data section in flash to data section in SRAM*/
	uint32_t *init_values_ptr = &_etext;
	uint32_t *data_ptr = &_sdata;
	uint32_t *bss_ptr = &_sbss;
	if(init_values_ptr != data_ptr){
		while(data_ptr < &_edata){
			*data_ptr = *init_values_ptr;
			data_ptr++;
			init_values_ptr++;
		}
	}

	//init the bss-section to zero in RAM
	for(uint32_t i = 0; i < (&_ebss - &_sbss); i++){
		*bss_ptr = 0;
		bss_ptr++;
	}

	//Branch to main function
	main();

	/*here one would normally call a function like system init where errata 
	workarounds and similar things are done which the hardware vendor takes 
	care of for the end-user. I left the function call commented as placeholder.*/
	//SystemInit() //DO NOT UNCOMMENT!

	//Branch to main function
	main();

	//Infinite loop, should never be reached
	while(1);
}

/*NMI and Hardfault handers are just infinite loops*/
void NMI_Handler(void) {
	while(1);
}

void HardFault_Handler(void) {
	while (1);
}
