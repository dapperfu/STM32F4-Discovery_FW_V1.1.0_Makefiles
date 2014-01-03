/******************************************************************************/
/*                                                                            */
/*        Syscall support functions for newlib console I/O with stdio         */
/*                                                                            */
/******************************************************************************/

/* $Id: syscalls.c,v 1.4 2008/08/25 16:11:40 cvs Exp $ */
/* 20090508 Nemui Fixed   scanf consideration */
/* 20091220 Nemui Separated Device Independent Definitions */
/* 20101107 Nemui Added error handling in sbrk 
            Nemui Adopted to C99              */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <reent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

/* platform dependent definitions */
#include "syscalls_if.h"

/* new code for _read_r provided by Alexey Shusharin - Thanks */
_ssize_t _read_r(struct _reent *r, int file, void *ptr, size_t len)
{
  char c;
  int  i;
  unsigned char *p;

  p = (unsigned char*)ptr;
  for (i = 0; i < len; i++)
  {
	/* 20090521Nemui */
	do{		
		c = getch();
	}while(c == false);
	/* 20090521Nemui */
	
    *p++ = c;
	#ifdef ECHOBACK 
		putch(c);
	#endif
	
    if (c == '\r' && i <= (len - 2)) /* 0x0D */
    {
      *p = '\n';					 /* 0x0A */
	  #ifdef ECHOBACK 
		putch('\n');				 /* 0x0A */
	  #endif
      return i + 2;
    }
  }
  return i;
}

_ssize_t _write_r (
    struct _reent *r, 
    int file, 
    const void *ptr, 
    size_t len)
{
	int i;
	const unsigned char *p;
	
	p = (const unsigned char*) ptr;
	
	for (i = 0; i < len; i++) {
		if (*p == '\n' ) putch('\r');
		putch(*p++);
	}
	
	return len;
}

int _close_r(
    struct _reent *r, 
    int file)
{
	return 0;
}

_off_t _lseek_r(
    struct _reent *r, 
    int file, 
    _off_t ptr, 
    int dir)
{
	return (_off_t)0;	/*  Always indicate we are at file beginning.	*/
}


int _fstat_r(
    struct _reent *r, 
    int file, 
    struct stat *st)
{
	/*  Always set as character device.				*/
	st->st_mode = S_IFCHR;	
		/* assigned to strong type with implicit 	*/
		/* signed/unsigned conversion.  Required by 	*/
		/* newlib.					*/

	return 0;
}

#ifdef __GNUC__
int isatty(int file); /* avoid warning */
#endif
int isatty(int file)
{
	return 1;
}


void _exit(int n) {
label:  goto label; /* endless loop */
}

int _getpid(int file)
{
	return 1;
}

int _kill(int file)
{
	return 1;
}

/* "malloc clue function" */

/**** Locally used variables. ****/
extern char end[];              /*  end is set in the linker command 	*/
								/* file and is the end of statically 	*/
								/* allocated data (thus start of heap).	*/
extern char _heap_end[];        /* Bottom of HEAP region 	*/

static char *heap_ptr;			/* Points to current end of the heap.	*/

/************************** _sbrk_r *************************************/
/*  Support function.  Adjusts end of heap to provide more memory to	*/
/* memory allocator. Simple and dumb with no sanity checks.				*/
/*  struct _reent *r	-- re-entrancy structure, used by newlib to 	*/
/*			support multiple threads of operation.						*/
/*  ptrdiff_t nbytes	-- number of bytes to add.						*/
/*  Returns pointer to start of new heap area.							*/
/*  Note:  This implementation is not thread safe (despite taking a		*/
/* _reent structure as a parameter).  									*/
/*  Since _s_r is not used in the current implementation, the following	*/
/* messages must be suppressed.											*/

/* Register name faking - works in collusion with the linker.  */
/*register char * stack_ptr asm ("sp");
#define _heap_end stack_ptr*/

void * _sbrk_r(
    struct _reent *_s_r, 
    ptrdiff_t nbytes)
{
	char  *base;		/*  errno should be set to  ENOMEM on error	*/

	if (!heap_ptr) {	/*  Initialize if first time through.		*/
		heap_ptr = end;
	}
	base = heap_ptr;	/*  Point to end of heap.					*/
	
	if (heap_ptr + nbytes > _heap_end)
	{
			errno = ENOMEM;
			return (caddr_t) -1;
	}
	heap_ptr += nbytes;	/*  Increase heap.							*/
	
	return base;		/*  Return pointer to start of new heap area.	*/
}



void * _sbrk(ptrdiff_t incr)
{
  char  *base;

/* Initialize if first time through. */

  if (!heap_ptr) heap_ptr = end;

  base = heap_ptr;      /*  Point to end of heap.                       */

	if (heap_ptr + incr > _heap_end)
	{
			errno = ENOMEM;
			return (caddr_t) -1;
	}
  
  heap_ptr += incr;     /*  Increase heap.                              */

  return base;          /*  Return pointer to start of new heap area.   */
}

int _open(const char *path, int flags, ...)
{
  return 1;
}

int _close(int fd)
{
  return 0;
}

int _fstat(int fd, struct stat *st)
{
  st->st_mode = S_IFCHR;
  return 0;
}

int _isatty(int fd)
{
  return 1;
}


int _lseek(int fd, off_t pos, int whence)
{
  return 0;
}

int _read(int fd, char *buf, size_t cnt)
{
  *buf = getch();

  return 1;
}

int _write(int fd, const char *buf, size_t cnt)
{
  int i;

  for (i = 0; i < cnt; i++)
    putch(buf[i]);

  return cnt;
}

/* .ARM.exidx is sorted, so has to go in its own output section.  */
/* Nemui Changed */
extern char *__exidx_start;
extern char *__exidx_end;

/* Override fgets() in newlib with a version that does line editing */
/*
char *fgets(char *s, int bufsize, void *f)
{
  cgets(s, bufsize);
  return s;
}
*/