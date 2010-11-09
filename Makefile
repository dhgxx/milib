LIB=	mi
LIBDIR=	/opt/local/lib

SHLIB_MAJOR=	1
SHLIB_MINOR=	0

.PATH:	${.CURDIR}/btree ${.CURDIR}/stack
WARNS?=	2

SRCS=	bstree.c stack.c
INCS=	bstree.h stack.h
INCSDIR=	/opt/local/include

NO_PROFILE=	yes

.include <bsd.lib.mk>
