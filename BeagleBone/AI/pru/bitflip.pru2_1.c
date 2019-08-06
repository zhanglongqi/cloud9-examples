////////////////////////////////////////
//	flipbit.pru2_1.c
//	Demo of shared memory
//	Usage:	This takes the first word of SHARED_RAM and flips every other bit
//				over and over.
//	Wiring:	None
//	Setup:	Run this on a PRU and run bitflip.arm.c on the ARM using /dev/uio1
//	See:	 
//	PRU:	pru2_0 or pru2_1
////////////////////////////////////////
#include <stdint.h>
#include <pru_cfg.h>
#include <pru_ctrl.h>
#include <stddef.h>
#include <rsc_types.h>
#include "resource_table_empty.h"
#include "init_pins_empty.h"

#define SHARED_RAM_ADDRESS 0x10000
unsigned int volatile __far * const SHARED_RAM = (unsigned int *) (SHARED_RAM_ADDRESS);

void main(void) {
	unsigned int value = 0;

	/* Set the SHARED_RAM value to 0 */
	*SHARED_RAM = 0;

	while(1) {
		/* Look for the ARM to modify the SHARED_RAM value */
		if(value != *SHARED_RAM) {
			/* Flip every other bit and write the value back */
			value = *SHARED_RAM;
			value ^= 0x55555555;
			*SHARED_RAM = value;
		}
	}
}
