
/*****************************************************************
 *
 * Copyright (c) 1996 Sony Computer Entertainment Inc.
 * All Rights Reserved.
 *
 *                                  Ver 1.00
 *
 *****************************************************************/

#ifndef _STDIO_H
#define _STDIO_H

#define	BUFSIZ 1024
#define EOF (-1)

#ifndef SEEK_SET
#define SEEK_SET 0
#endif
#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif
#ifndef SEEK_END
#define SEEK_END 2
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;  /* result type of the sizeof operator (ANSI) */
#endif

/* under constraction now */

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif
 int printf(char *fmt, ...); /**/
 int sprintf(char *buffer, char *fmt, ...);

 char getc(int);		/**/
 char getchar(void);
 char *gets(char *);
 void putc(char, int);	/**/
 void putchar(char);
 void puts(char *);
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif /* _STDIO_H */
