#ifndef __MISC_H
#define __MISC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>

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

#endif