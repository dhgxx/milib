# OpenBSD makefile for milib.

LIB=	  	mi

HDRS=		${.CURDIR}/{tree/bstree.h,tree/tree.h,list/dlist.h,stack/stack.h}
SRCS=		bstree.c dlist.c stack.c tree.c

SHLIB_MAJOR=	1
SHLIB_MINOR=	0

.PATH:		${.CURDIR}/tree ${.CURDIR}/list ${.CURDIR}/stack
LIBDIR=		/opt/local/lib
INCSDIR=	/opt/local/include

WARNS?=		2
NO_OBJ=		true
NOBINMODE=	0444

.if !defined(NOOBJ)
NOOBJ=		${NO_OBJ}
.endif

LDCONFIG=	/sbin/ldconfig

includes:
	@cd ${.CURDIR}; for i in $(HDRS); do \
		j="cmp -s $$i ${INCSDIR}/$$i || \
			${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${NOBINMODE} \
			$$i ${INCSDIR}"; \
		echo $$j; \
		eval "$$j"; \
	done

lib-config:
	${LDCONFIG} -m ${LIBDIR}

.include <bsd.lib.mk>
