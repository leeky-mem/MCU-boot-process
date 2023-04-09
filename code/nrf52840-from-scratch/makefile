#IDIR =../nrfx/hal ../nrfx/drivers ../nrfx/drivers/include ../nrfx/mdk
#INC=-I../nrfx -I../nrfx/templates -I../nrfx/hal -I../nrfx/drivers -I../nrfx/drivers/include -I../nrfx/mdk -Iinc
CC=arm-none-eabi-gcc
DUMP=arm-none-eabi-objdump
HEX=arm-none-eabi-objcopy
FLASH=nrfjprog
CFLAGS=-mcpu=cortex-m4 -mthumb -nostdlib -T nrf52840.ld -Wall
ODIR=obj
DEPS = nrf52840.ld main.c startup.c
OBJ = main.o nrf52840_startup.o

%.o: %.c $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

main.elf: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

main.hex: main.elf
	$(HEX) -O ihex $< $@

.PHONY: hex
hex: main.hex

.PHONY: flash
flash: main.hex
	$(FLASH) --eraseall
	$(FLASH) -f NRF52 --program main.hex

.PHONY: inspect
inspect: main.elf
	$(DUMP) -t main.elf

.PHONY: clean
clean:
	rm -f *.o *~ core $(INCDIR)/*~
	rm *.hex
	rm *.elf