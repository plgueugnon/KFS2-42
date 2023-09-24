#ifndef __MISC_H
#define __MISC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>


// https://www.intel.com/content/www/us/en/architecture-and-technology/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.html
// https://wiki.osdev.org/GDT_Tutorial

// Each define here is for a specific flag in the descriptor.
// Refer to the intel documentation for a description of what each one does.
#define SEG_DESCTYPE(x)  ((x) << 0x04) // Descriptor type (0 for system, 1 for code/data)
#define SEG_PRES(x)      ((x) << 0x07) // Present
#define SEG_SAVL(x)      ((x) << 0x0C) // Available for system use
#define SEG_LONG(x)      ((x) << 0x0D) // Long mode
#define SEG_SIZE(x)      ((x) << 0x0E) // Size (0 for 16-bit, 1 for 32)
#define SEG_GRAN(x)      ((x) << 0x0F) // Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB)
#define SEG_PRIV(x)     (((x) &  0x03) << 0x05)   // Set privilege level (0 - 3)
 
#define SEG_DATA_RD        0x00 // Read-Only
#define SEG_DATA_RDA       0x01 // Read-Only, accessed
#define SEG_DATA_RDWR      0x02 // Read/Write
#define SEG_DATA_RDWRA     0x03 // Read/Write, accessed
#define SEG_DATA_RDEXPD    0x04 // Read-Only, expand-down
#define SEG_DATA_RDEXPDA   0x05 // Read-Only, expand-down, accessed
#define SEG_DATA_RDWREXPD  0x06 // Read/Write, expand-down
#define SEG_DATA_RDWREXPDA 0x07 // Read/Write, expand-down, accessed
#define SEG_CODE_EX        0x08 // Execute-Only
#define SEG_CODE_EXA       0x09 // Execute-Only, accessed
#define SEG_CODE_EXRD      0x0A // Execute/Read
#define SEG_CODE_EXRDA     0x0B // Execute/Read, accessed
#define SEG_CODE_EXC       0x0C // Execute-Only, conforming
#define SEG_CODE_EXCA      0x0D // Execute-Only, conforming, accessed
#define SEG_CODE_EXRDC     0x0E // Execute/Read, conforming
#define SEG_CODE_EXRDCA    0x0F // Execute/Read, conforming, accessed

/* 
* Here we define each segment descriptor (present, privilege, type, type flags) 
* More explanations here : https://youtu.be/Wh5nPn2U_1w?feature=shared
*/

/* Kernel ring 0 */
// Kernel CS 0x9A
#define GDT_CODE_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_CODE_EXRD
 
// Kernel DS 0x92
#define GDT_DATA_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_DATA_RDWR

// Kernel Stack 0x96
#define GDT_STACK_PL0	SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
			SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
			SEG_PRIV(0)     | SEG_DATA_RDWREXPD

/* Kernel ring 3 */
// Userland CS 0xFA
#define GDT_CODE_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_CODE_EXRD
 
// Userland DS 0xF2
#define GDT_DATA_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_DATA_RDWR

// Userland Stack 0xF6
#define GDT_STACK_PL3	SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
			SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
			SEG_PRIV(3)     | SEG_DATA_RDWREXPD


/*
 * Global Descriptor Table Entry
 */
// __attribute__((packed)) = tells the compiler to minimize the memory required
typedef struct gdt_entry {
	/* Limits */
	unsigned short limit_low;
	/* Segment address */
	unsigned short base_low;
	unsigned char base_middle;
	/* Access modes */
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__((packed)) t_gdt_entry;

/*
 * GDT pointer
 */
typedef struct gdt_ptr {
	unsigned short limit; 	// The upper 16 bits of all selector limits.
	unsigned int base;		// The address of the first gdt_entry struct.
} __attribute__((packed)) t_gdt_ptr;

void	init_gdt(void);

// system
// 
void * memcpy(void * restrict dest, const void * restrict src, size_t count);
int max(int a, int b);
int min(int a, int b);
int abs(int a);
void swap(int *a, int *b);
void * memmove(void * restrict dest, const void * restrict src, size_t count);
int strcmp(const char * a, const char * b);
void * memset(void * b, int val, size_t count);
unsigned short * memsetw(unsigned short * dest, unsigned short val, int count);
uint32_t strlen(const char *str);
char * strcpy(char * dest, const char * src);
int atoi(const char * str);
void terminal_putchar(char c);
void terminal_itoa_base(int n, int base);

#endif