NO_OBJ=true
NOBINMODE=0444

LIB=	mi
LIBDIR=	/opt/local/lib

SHLIB_MAJOR=	1
SHLIB_MINOR=	0

.PATH:	${.CURDIR}/btree ${.CURDIR}/list ${.CURDIR}/stack
WARNS?=	2

SRCS=	bstree.c dlist.c stack.c
INCS=	bstree.h dlist.h stack.h
INCSDIR=	/opt/local/include

.if !defined(NOOBJ)
NOOBJ=${NO_OBJ}
.endif

.if !defined(OSTYPE) || ${OSTYPE} != "FreeBSD"
install: libs incs

# don't install pic if there's any.
libs:
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m ${NOBINMODE} \
		${.CURDIR}/lib${LIB}.{a,so.${SHLIB_MAJOR}.${SHLIB_MINOR}} ${LIBDIR}
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m ${NOBINMODE} \
		${.CURDIR}/lib${LIB}_{p,pic}.a ${LIBDIR}

incs:
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m ${NOBINMODE} \
		${.CURDIR}/btree/bstree.h ${INCSDIR}
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m ${NOBINMODE} \
		${.CURDIR}/list/dlist.h ${INCSDIR}
	${INSTALL} -C -o ${BINOWN} -g ${BINGRP} -m ${NOBINMODE} \
		 ${.CURDIR}/stack/stack.h ${INCSDIR}
.endif

.include <bsd.lib.mk>
