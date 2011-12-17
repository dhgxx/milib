# FreeBSD makefile for milib

LIB=		mi

SRCS=		bstree.c dlist.c stack.c tree.c
INCS=		bstree.h dlist.h stack.h tree.h

SHLIB_MAJOR=	1
SHLIB_MINOR=	1

.PATH:		${.CURDIR}/tree ${.CURDIR}/list ${.CURDIR}/stack
INCSDIR=	/opt/local/include/mi
LIBDIR=		/opt/local/lib

WARNS?=		2
NO_OBJ=		true
NO_PROFILE=	true

NOOBJ?=		${NO_OBJ}
NOPROFILE?=	${NO_PROFILE}

.if exists(/usr/bin/clang)
CC=			clang
CFLAGS=		-O2 -pipe
.endif

LDCONFIG=	/sbin/ldconfig

lib-config:
	${LDCONFIG} -m ${LIBDIR}

.include <bsd.lib.mk>
