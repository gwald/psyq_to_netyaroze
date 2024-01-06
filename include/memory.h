
/*****************************************************************
 *
 * Copyright (c) 1996 Sony Computer Entertainment Inc.
 * All Rights Reserved.
 *
 *                                  Ver 1.00
 *
 *****************************************************************/

#ifndef _MEMORY_H
#define _MEMORY_H

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;  /* result type of the sizeof operator (ANSI) */
#endif

#ifndef NULL
#define NULL 0		       /* null pointer constant */
#endif

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif
/* To avoid conflicting */
void *memcpy ( unsigned char *, unsigned char *, int  ); 
void *memmove(unsigned char *, unsigned char *, int);
/* To avoid conflicting */
int   memcmp (/*  unsigned char *, unsigned char *, int  */);
void *memchr (unsigned char *, unsigned char, int);
void *memset (unsigned char *, unsigned char, int);

void *bcopy(unsigned char *, unsigned char *, int); /* src,dest */
void *bzero(unsigned char *, int);
int   bcmp (unsigned char *, unsigned char *, int);
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif
#endif  /* _MEMORY_H */





