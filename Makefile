.if defined(OSTYPE)
OSNAME=		${OSTYPE}
.else
OSNAME!=	uname -s
.endif

LIBCONFIG=	lib-config

.if ${OSNAME} == "FreeBSD"
MKFILE=		freebsd.mk
INST=		install
.elif ${OSNAME} == "OpenBSD"
MKFILE=		openbsd.mk
INST=		install includes
.endif

all:
	@${MAKE} -f ${MKFILE}

clean:
	@${MAKE} -f ${MKFILE} clean

install:
	@${MAKE} -f ${MKFILE} ${INST}
	@${MAKE} -f ${MKFILE} ${LIBCONFIG}

