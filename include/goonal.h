#ifndef GOONAL_H
#define GOONAL_H
#include <stdint.h>
#include <stddef.h>
#include "limine.h"
#include "serial.h"

// important functions that are needed (apparently)

void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

// actual functions that matter 

void hcf(void);
void kerror(char *msg);

// functions that don't matter and i don't know why they are in the kernal 

#endif

