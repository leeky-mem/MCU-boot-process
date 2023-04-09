#include <stdint.h>

#define LED1_PIN 13

/**
  * @brief GPIO Port 1 (P0) copied from nrf52840.h
  */
typedef struct {                                /*!< (@ 0x50000000) P0 Structure                                               */
	uint32_t  RESERVED[321];
	uint32_t  OUT;                          /*!< (@ 0x00000504) Write GPIO port                                            */
	uint32_t  OUTSET;                       /*!< (@ 0x00000508) Set individual bits in GPIO port                           */
	uint32_t  OUTCLR;                       /*!< (@ 0x0000050C) Clear individual bits in GPIO port                         */
	uint32_t  IN;                           /*!< (@ 0x00000510) Read GPIO port                                             */
	uint32_t  DIR;                          /*!< (@ 0x00000514) Direction of GPIO pins                                     */
	uint32_t  DIRSET;                       /*!< (@ 0x00000518) DIR set register                                           */
	uint32_t  DIRCLR;                       /*!< (@ 0x0000051C) DIR clear register                                         */
	uint32_t  LATCH;                        /*!< (@ 0x00000520) Latch register indicating what GPIO pins that
                                                                    have met the criteria set in the PIN_CNF[n].SENSE
                                                                    registers                                                  */
	uint32_t  DETECTMODE;                   /*!< (@ 0x00000524) Select between default DETECT signal behavior
                                                                    and LDETECT mode                                           */
	uint32_t  RESERVED1[118];
	uint32_t  PIN_CNF[32];                  /*!< (@ 0x00000700) Description collection: Configuration of GPIO
                                                                    pins                                                       */
} NRF_GPIO_Type;                                /*!< Size = 1920 (0x780)                                                       */

//copied from nrf52840.h
#define NRF_P0_BASE                 0x50000000UL
#define NRF_P0                      ((NRF_GPIO_Type*)          NRF_P0_BASE)

int main(void)
{
	NRF_P0->OUTSET = (1u << 13) | (1u << 14) | (1u << 15) | (1u << 16);
	NRF_P0->DIRSET = (1u << 13) | (1u << 14) | (1u << 15) | (1u << 16);

	while(1){
		NRF_P0->OUTCLR = 1u << 13;
		for(volatile uint32_t i = 0; i < 1000000; i++);
		NRF_P0->OUTSET = 1u << 13;
		for(volatile uint32_t i = 0; i < 1000000; i++);
	}
	return 0;
}
