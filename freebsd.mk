# FreeBSD makefile for milib

LIB=		mi

SRCS=		bstree.c dlist.c stack.c
INCS=		bstree.h dlist.h stack.h

SHLIB_MAJOR=	1
SHLIB_MINOR=	0

.PATH:		${.CURDIR}/tree ${.CURDIR}/list ${.CURDIR}/stack
INCSDIR=	/opt/local/include
LIBDIR=		/opt/local/lib

WARNS?=		2
NO_OBJ=		true

.if !defined(NOOBJ)
NOOBJ=		${NO_OBJ}
.endif

LDCONFIG=	/sbin/ldconfig

lib-config:
	${LDCONFIG} -m ${LIBDIR}

.include <bsd.lib.mk>
