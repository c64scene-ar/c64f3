AM_CPPFLAGS = \
	@ARCH_INCLUDES@ \
	-I$(top_builddir)/src \
	-I$(top_srcdir)/src \
	-I$(top_srcdir)/src/prox1541 \
	-I$(top_srcdir)/src/drive \
	-I$(top_srcdir)/src/drive/iec/c64exp \
	-I$(top_srcdir)/src/raster \
	-I$(top_srcdir)/src/sid \
	-I$(top_srcdir)/src/tape \
	-I$(top_srcdir)/src/userport \
	-I$(top_srcdir)/src/viciisc \
	-I$(top_srcdir)/src/lib/p64 \
	-I$(top_srcdir)/src/video \
	-I$(top_srcdir)/src/rtc

noinst_LIBRARIES = libprox1541.a

libprox1541_a_SOURCES = \
	prox1541.c

#BUILT_SOURCES = psiddrv.h

EXTRA_DIST =
