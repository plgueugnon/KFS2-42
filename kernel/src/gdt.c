#include "../include/misc.h"

t_gdt_entry gdt[7];
// set a pointer to the gdt at address 0x00000800
t_gdt_ptr	*gp = (t_gdt_ptr *)0x00000800;

/**
 * Set a GDT descriptor
 *
 * @param num The number for the descriptor to set.
 * @param base Base address
 * @param limit Limit
 * @param access Access permissions
 * @param gran Granularity
 */
void create_gdt_descriptor(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
	/* Base Address */
	gdt[num].base_low =		(base & 0xFFFF);
	gdt[num].base_middle =	(base >> 16) & 0xFF;
	gdt[num].base_high =	(base >> 24) & 0xFF;
	/* Limits */
	gdt[num].limit_low =	(limit & 0xFFFF);
	gdt[num].granularity =	(limit >> 16) & 0X0F;
	/* Granularity */
	gdt[num].granularity |= (gran & 0xF0); // bitwise OR + assignment
	/* Access flags */
	gdt[num].access = access;
}

/**
  * Source: http://www.osdever.net/bkerndev/Docs/gdt.htm
  * More explanations here: https://stackoverflow.com/questions/23978486/far-jump-in-gdt-in-bootloader
  * This will set up our new segment registers. We need to do
  * something special in order to set CS. We do what is called a
  * far jump. A jump that includes a segment as well as an offset.
*/
extern void _gdt_flush(t_gdt_ptr *gp)
{
    asm volatile(
        "lgdt %[gp]\n\t"				// Load the GDT with our '_gp' which is a special pointer
        "mov $0x10, %%ax\n\t"			// 0x10 is the offset in the GDT to our data segment
        "mov %%ax, %%ds\n\t"			// Load all data segment selectors
        "mov %%ax, %%es\n\t"
        "mov %%ax, %%fs\n\t"
        "mov %%ax, %%gs\n\t"
        "mov %%ax, %%ss\n\t"
        "ljmp $0x08, $.flush%=\n\t"		// 0x08 is the offset to our code segment: Far jump!
    	".flush%=:\n\t"
        "ret\n\t"
		:
		: [gp] "m" (*gp)
		: "eax"
    );
}


void init_gdt(void)
{
	gp->limit = (sizeof(t_gdt_entry) * 7) - 1;;
	gp->base = (unsigned int)&gdt;
    create_gdt_descriptor(0, 0, 0, 0, 0);	// Null
    create_gdt_descriptor(1, 0, 0x000FFFFF, (unsigned char)GDT_CODE_PL0, 0xCF); // Kernel code
    create_gdt_descriptor(2, 0, 0x000FFFFF, (unsigned char)GDT_DATA_PL0, 0xCF); // Kernel data
	create_gdt_descriptor(3, 0, 0x000FFFFF, (unsigned char)GDT_STACK_PL0, 0xCF); // Kernel stack

    create_gdt_descriptor(4, 0, 0x000FFFFF, (unsigned char)GDT_CODE_PL3, 0xCF); // User code
    create_gdt_descriptor(5, 0, 0x000FFFFF, (unsigned char)GDT_DATA_PL3, 0xCF); // User data
	create_gdt_descriptor(6, 0, 0x000FFFFF, (unsigned char)GDT_STACK_PL3, 0xCF); // User stack

	_gdt_flush(gp);
}

