void Reset_Handler(void)
{
	/*Copy initial values from data-section in flash 
	to data section in SRAM*/
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

	//Infinite loop, should never be reached
	while(1);
}