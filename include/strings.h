
/*****************************************************************
 *
 * Copyright (c) 1996 Sony Computer Entertainment Inc.
 * All Rights Reserved.
 *
 *                                  Ver 1.00
 *
 *****************************************************************/

#ifndef	_STRINGS_H
#define	_STRINGS_H

#define LMAX 256

#ifndef NULL
#define NULL 0		       /* null pointer constant */
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;  /* result type of the sizeof operator (ANSI) */
#endif

#include <memory.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif
 char *strcat (char *, char *);
 char *strncat(char *, char *, int);
 int   strcmp ( char *, char * );	/* To avoid conflicting */
 int   strncmp(char *, char *, int);
 char *strcpy ( char *, char * );	/* To avoid conflicting */
 char *strncpy(char *, char *, int);
 int   strlen (char *);		/* To avoid conflicting */
 char *strchr (char *, char);
 char *strrchr(char *, char);
 char *strpbrk(char *, char *);
 int   strspn (char *, char *);
 int   strcspn(char *, char *);
 char *strtok (char *, char *);
 char *strstr (char *, char *);
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#define strdup(p)	( strcpy(malloc(strlen(p)+1),p); )

#endif	/* _STRINGS_H */

