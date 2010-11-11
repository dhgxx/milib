.if defined(OSTYPE)
OSNAME=		${OSTYPE}
.else
OSNAME!=	uname -s
.endif

.if ${OSNAME} == "FreeBSD"
MKFILE=		Makefile.fbsd
INST=		install
.elif ${OSNAME} == "OpenBSD"
MKFILE=		Makefile.obsd
INST=		install includes
.endif

all:
	@${MAKE} -f ${MKFILE}

clean:
	@${MAKE} -f ${MKFILE} clean

install:
	@${MAKE} -f ${MKFILE} ${INST}

