.if defined(OSTYPE)
OSNAME=		${OSTYPE}
.else
OSNAME!=	uname -s
.endif

.if ${OSNAME} == "FreeBSD"
MKFILE=		Makefile.fbsd
.elif ${OSNAME} == "OpenBSD"
MKFILE=		Makefile.obsd
.endif

all: ${OSNAME}

install: ${OSNAME}-install

FreeBSD:
.include "${.CURDIR}/Makefile.fbsd"

FreeBSD-install:
	@${MAKE} -f ${MKFILE} install

OpenBSD:
.include "${.CURDIR}/Makefile.obsd"

OpenBSD-install:
	@${MAKE} -f ${MKFILE} install includes

