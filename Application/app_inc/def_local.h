#ifndef _DEF_LOCAL_INCLUDED
#define _DEF_LOCAL_INCLUDED

#ifdef ISO_BOOL
typedef _Bool bool;	
#else
typedef signed char bool;
#endif

#ifdef DEBUG
	#define STATIC
#else
	#define STATIC	static
#endif

#define TRUE	1
#define FALSE	0

#endif
    

