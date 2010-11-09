.if !defined(OSTYPE)
OSTYPE=`uname`
.endif

.if ${OSTYPE} == FreeBSD
.include "${.CURDIR}/Makefile.freebsd"
.else
.if ${OSTYPE} == OpenBSD
.include "${.CURDIR}/Makefile.openbsd"
.endif
.endif
