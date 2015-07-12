# Makefile for program source directory in GNU NLS utilities package.
# Copyright (C) 1995, 1996, 1997 by Ulrich Drepper <drepper@gnu.ai.mit.edu>
#
# This file file be copied and used freely without restrictions.  It can
# be used in projects which are not available under the GNU Public License
# but which still want to provide support for the GNU gettext functionality.
# Please note that the actual code is *not* freely available.

PACKAGE = vice
VERSION = 2.4.9

SHELL = /bin/sh


srcdir = ../../po
top_srcdir = ../..
top_builddir = ..
builddir = .
VPATH = ../../po

prefix = /usr/local
exec_prefix = ${prefix}
datadir = $(DESTDIR)$(prefix)/share
localedir = $(DESTDIR)$(datadir)/locale
gnulocaledir = $(DESTDIR)$(prefix)/share/locale
gettextsrcdir = $(DESTDIR)$(prefix)/share/gettext/po
subdir = po

INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644
MKINSTALLDIRS = $(top_srcdir)/../mkinstalldirs

CC = gcc
GENCAT = 
GMSGFMT = PATH=../src:$$PATH /usr/bin/msgfmt
MSGFMT = /usr/bin/msgfmt
XGETTEXT = PATH=../src:$$PATH /usr/bin/xgettext
MSGMERGE = PATH=../src:$$PATH msgmerge

DEFS = -DHAVE_CONFIG_H
CFLAGS = -g -O3 -march=native -Wstrict-prototypes -Wall -W -Wno-unused-parameter -Wno-missing-field-initializers -Wno-sign-compare
CPPFLAGS =  

INCLUDES = -I.. -I$(top_srcdir)/intl

COMPILE = $(CC) -c $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS) $(XCFLAGS)

SOURCES = cat-id-tbl.c
POFILES =  da.po de.po es.po fr.po hu.po it.po ko.po nl.po pl.po ru.po sv.po tr.po
GMOFILES =  da.gmo de.gmo es.gmo fr.gmo hu.gmo it.gmo ko.gmo nl.gmo pl.gmo ru.gmo sv.gmo tr.gmo
DISTFILES = ChangeLog ChangeLog.1 Makefile.in.in POTFILES.in $(PACKAGE).pot \
stamp-cat-id $(POFILES) $(GMOFILES) $(SOURCES) po2tbl.sed intl2po.c \
gen_amiga_intl_c.c gen_translate_c.c gen_win32_rc.c po2table.c \
gen_win32_files.sh check_obsolete.sh translations-status.txt

POTFILES = \
	../../src/arch/unix/joy.c \
	../../src/arch/unix/mididrv.c \
	../../src/arch/unix/rs232.c \
	../../src/arch/unix/gui/c128ui.c \
	../../src/arch/unix/gui/c64dtvui.c \
	../../src/arch/unix/gui/c64scui.c \
	../../src/arch/unix/gui/c64ui.c \
	../../src/arch/unix/gui/cbm2ui.c \
	../../src/arch/unix/gui/petui.c \
	../../src/arch/unix/gui/plus4ui.c \
	../../src/arch/unix/gui/uiacia1.c \
	../../src/arch/unix/gui/uiattach.c \
	../../src/arch/unix/gui/uiautostart.c \
	../../src/arch/unix/gui/uic64_256k.c \
	../../src/arch/unix/gui/uic64cart.c \
	../../src/arch/unix/gui/uic64dtv.c \
	../../src/arch/unix/gui/uicmdline.c \
	../../src/arch/unix/gui/uicommands.c \
	../../src/arch/unix/gui/uicrtc.c \
	../../src/arch/unix/gui/uidatasette.c \
	../../src/arch/unix/gui/uidigimax.c \
	../../src/arch/unix/gui/uidqbb.c \
	../../src/arch/unix/gui/uidrive.c \
	../../src/arch/unix/gui/uidrivec128.c \
	../../src/arch/unix/gui/uidrivec64.c \
	../../src/arch/unix/gui/uidrivec64c128.c \
	../../src/arch/unix/gui/uidrivec64dtv.c \
	../../src/arch/unix/gui/uidrivec64vic20.c \
	../../src/arch/unix/gui/uidriveiec.c \
	../../src/arch/unix/gui/uidrivepetcbm2.c \
	../../src/arch/unix/gui/uidriveplus4.c \
	../../src/arch/unix/gui/uidrivevic20.c \
	../../src/arch/unix/gui/uieasyflash.c \
	../../src/arch/unix/gui/uiexpert.c \
	../../src/arch/unix/gui/uifliplist.c \
	../../src/arch/unix/gui/uifullscreen-menu.h \
	../../src/arch/unix/gui/uigeoram.c \
	../../src/arch/unix/gui/uiide64.c \
	../../src/arch/unix/gui/uiisepic.c \
	../../src/arch/unix/gui/uijoystick2.c \
	../../src/arch/unix/gui/uikeyboard.c \
	../../src/arch/unix/gui/uilightpen.c \
	../../src/arch/unix/gui/uimagicvoice.c \
	../../src/arch/unix/gui/uimidi.c \
	../../src/arch/unix/gui/uimmc64.c \
	../../src/arch/unix/gui/uimmcreplay.c \
	../../src/arch/unix/gui/uimouse.c \
	../../src/arch/unix/gui/uinetplay.c \
	../../src/arch/unix/gui/uipalette.c \
	../../src/arch/unix/gui/uiperipheral.c \
	../../src/arch/unix/gui/uiperipheraliec.c \
	../../src/arch/unix/gui/uiperipheralieee.c \
	../../src/arch/unix/gui/uipetcolour.c \
	../../src/arch/unix/gui/uipetdww.c \
	../../src/arch/unix/gui/uipetreu.c \
	../../src/arch/unix/gui/uiplus256k.c \
	../../src/arch/unix/gui/uiplus60k.c \
	../../src/arch/unix/gui/uiprinter.c \
	../../src/arch/unix/gui/uiprinteriec.c \
	../../src/arch/unix/gui/uiprinteriecplus4.c \
	../../src/arch/unix/gui/uiprinterieee.c \
	../../src/arch/unix/gui/uips2mouse.c \
	../../src/arch/unix/gui/uiramcart.c \
	../../src/arch/unix/gui/uiretroreplay.c \
	../../src/arch/unix/gui/uireu.c \
	../../src/arch/unix/gui/uiromset.c \
	../../src/arch/unix/gui/uirs232.c \
	../../src/arch/unix/gui/uirs232c64c128.c \
	../../src/arch/unix/gui/uirs232petplus4cbm2.c \
	../../src/arch/unix/gui/uirs232user.c \
	../../src/arch/unix/gui/uisettings.c \
	../../src/arch/unix/gui/uisid.c \
	../../src/arch/unix/gui/uisound.c \
	../../src/arch/unix/gui/uisoundexpander.c \
	../../src/arch/unix/gui/uited.c \
	../../src/arch/unix/gui/uitfe.c \
	../../src/arch/unix/gui/uitpi.c \
	../../src/arch/unix/gui/uiv364speech.c \
	../../src/arch/unix/gui/uivdc.c \
	../../src/arch/unix/gui/uivic.c \
	../../src/arch/unix/gui/uivicii.c \
	../../src/arch/unix/gui/vic20ui.c \
	../../src/arch/unix/gui/vsidui.c \
	../../src/arch/unix/x11/gnome/about.c \
	../../src/arch/unix/x11/gnome/uicartridge.c \
	../../src/arch/unix/x11/gnome/uiedisk.c \
	../../src/arch/unix/x11/gnome/uiedit.c \
	../../src/arch/unix/x11/gnome/uimenu.c \
	../../src/arch/unix/x11/gnome/uinetplay.c \
	../../src/arch/unix/x11/gnome/uipalcontrol.c \
	../../src/arch/unix/x11/gnome/uiscreenshot.c \
	../../src/arch/unix/x11/gnome/uisnapshot.c \
	../../src/arch/unix/x11/gnome/uivsidcontrol.c \
	../../src/arch/unix/x11/gnome/x11ui.c \
	../../src/arch/unix/x11/ui-cmdline-options.c \
	../../src/arch/unix/x11/xrandr.c \
	../../src/arch/unix/x11/xaw/about.c \
	../../src/arch/unix/x11/xaw/uicartridge.c \
	../../src/arch/unix/x11/xaw/uiedisk.c \
	../../src/arch/unix/x11/xaw/uimenu.c \
	../../src/arch/unix/x11/xaw/uiscreenshot.c \
	../../src/arch/unix/x11/xaw/uisnapshot.c \
	../../src/arch/unix/x11/xaw/uivsidcontrol.c \
	../../src/arch/unix/x11/xaw/x11ui.c \
	../../src/arch/unix/x11/xaw/x11video.c \
	../../src/arch/unix/macosx/joy.c \
	../../src/arch/unix/macosx/mididrv.c \
	../../src/arch/unix/macosx/cocoa/mousedrv.m \
	../../src/arch/unix/macosx/cocoa/ui-cmdline-options.c \
	../../src/arch/unix/macosx/cocoa/viceapplication.m \
	../../src/arch/unix/macosx/cocoa/video.m \
	../../src/arch/win32/res.rc.po.c \
	../../src/arch/win32/resacia.rc.po.c \
	../../src/arch/win32/resautostart.rc.po.c \
	../../src/arch/win32/resc128.rc.po.c \
	../../src/arch/win32/resc64.rc.po.c \
	../../src/arch/win32/resc64_256k.rc.po.c \
	../../src/arch/win32/resc64dtv.rc.po.c \
	../../src/arch/win32/rescbm2common.rc.po.c \
	../../src/arch/win32/rescbm2.rc.po.c \
	../../src/arch/win32/rescbm5x0.rc.po.c \
	../../src/arch/win32/rescia.rc.po.c \
	../../src/arch/win32/resdigimax.rc.po.c \
	../../src/arch/win32/resdqbb.rc.po.c \
	../../src/arch/win32/resdrivec128.rc.po.c \
	../../src/arch/win32/resdrivec64.rc.po.c \
	../../src/arch/win32/resdrivec64dtv.rc.po.c \
	../../src/arch/win32/resdrivepetcbm2.rc.po.c \
	../../src/arch/win32/resdriveplus4.rc.po.c \
	../../src/arch/win32/resdrivevic20.rc.po.c \
	../../src/arch/win32/resds12c887rtc.rc.po.c \
	../../src/arch/win32/reseasyflash.rc.po.c \
	../../src/arch/win32/resexpert.rc.po.c \
	../../src/arch/win32/resgeoram.rc.po.c \
	../../src/arch/win32/reside64.rc.po.c \
	../../src/arch/win32/resisepic.rc.po.c \
	../../src/arch/win32/reslightpen.rc.po.c \
	../../src/arch/win32/resmagicvoice.rc.po.c \
	../../src/arch/win32/resmidi.rc.po.c \
	../../src/arch/win32/resmmc64.rc.po.c \
	../../src/arch/win32/resmmcreplay.rc.po.c \
	../../src/arch/win32/resmouse.rc.po.c \
	../../src/arch/win32/respet.rc.po.c \
	../../src/arch/win32/respetcolour.rc.po.c \
	../../src/arch/win32/respetdww.rc.po.c \
	../../src/arch/win32/respetreu.rc.po.c \
	../../src/arch/win32/resplus256k.rc.po.c \
	../../src/arch/win32/resplus4.rc.po.c \
	../../src/arch/win32/resplus60k.rc.po.c \
	../../src/arch/win32/resramcart.rc.po.c \
	../../src/arch/win32/resretroreplay.rc.po.c \
	../../src/arch/win32/resreu.rc.po.c \
	../../src/arch/win32/resrs232user.rc.po.c \
	../../src/arch/win32/resscpu64.rc.po.c \
	../../src/arch/win32/ressid.rc.po.c \
	../../src/arch/win32/ressidcart.rc.po.c \
	../../src/arch/win32/ressiddtv.rc.po.c \
	../../src/arch/win32/ressoundexpander.rc.po.c \
	../../src/arch/win32/ressoundsampler.rc.po.c \
	../../src/arch/win32/rested.rc.po.c \
	../../src/arch/win32/restfe.rc.po.c \
	../../src/arch/win32/resv364speech.rc.po.c \
	../../src/arch/win32/resvic.rc.po.c \
	../../src/arch/win32/resvic20.rc.po.c \
	../../src/arch/win32/resvicii.rc.po.c \
	../../src/arch/win32/resvsid.rc.po.c \
	../../src/arch/amigaos/intl_text.c.po.c \
	../../src/translate_text.c.po.c 

CATALOGS = $(POFILES:%.po=%$(CATOBJEXT))
CATOBJEXT = .gmo
INSTOBJEXT = .mo

.SUFFIXES:
.SUFFIXES: .c .o .po .pox .gmo .mo .msg .cat .rc .rc.po.c .c.po.c

.c.o:
	$(COMPILE) $<

.po.pox:
	$(MAKE) $(PACKAGE).pot
	$(MSGMERGE) $< $(builddir)/$(PACKAGE).pot -o $*.pox

.po.mo:
	$(MSGFMT) -o $@ $<

.po.gmo:
	file=$(srcdir)/`echo $* | sed 's,.*/,,'`.gmo \
	  && rm -f $$file && $(GMSGFMT) -o $$file $<

.po.cat:
	sed -f $(srcdir)/po2msg.sed < $< > $*.msg \
	  && rm -f $@ && $(GENCAT) $@ $*.msg

.rc.rc.po.c:
	./intl2po win32 $< $@ $(top_srcdir) $(top_builddir)

.c.c.po.c:
	./intl2po intl $< $@ $(top_srcdir) $(top_builddir)

all: all-yes

all-yes: cat-id-tbl.c $(CATALOGS)
all-no:

$(builddir)/$(PACKAGE).pot: $(POTFILES)
	$(XGETTEXT) --default-domain=$(PACKAGE) --directory=$(top_srcdir) --directory=$(top_builddir) \
	  --add-comments --keyword=_ --keyword=N_ \
	  --files-from=$(srcdir)/POTFILES.in \
	  -o $(builddir)/vice.pot

$(builddir)/cat-id-tbl.c: $(builddir)/stamp-cat-id; @:
$(builddir)/stamp-cat-id: $(builddir)/$(PACKAGE).pot
	rm -f cat-id-tbl.tmp
	sed -f $(srcdir)/po2tbl.sed $(builddir)/$(PACKAGE).pot \
		| sed -e "s/@PACKAGE NAME@/$(PACKAGE)/" > cat-id-tbl.tmp
	if cmp -s cat-id-tbl.tmp $(builddir)/cat-id-tbl.c; then \
	  rm cat-id-tbl.tmp; \
	else \
	  echo cat-id-tbl.c changed; \
	  rm -f $(builddir)/cat-id-tbl.c; \
	  mv cat-id-tbl.tmp $(builddir)/cat-id-tbl.c; \
	fi
	cd $(builddir) && rm -f stamp-cat-id && echo timestamp > stamp-cat-id


install: install-exec install-data
install-exec:
install-data: install-data-yes
install-data-no: all
install-data-yes: all
	if test -r "$(MKINSTALLDIRS)"; then \
	  $(MKINSTALLDIRS) $(datadir); \
	else \
	  $(SHELL) $(top_srcdir)/mkinstalldirs $(datadir); \
	fi
	@catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  case "$$cat" in \
	    *.gmo) destdir=$(gnulocaledir);; \
	    *)     destdir=$(localedir);; \
	  esac; \
	  lang=`echo $$cat | sed 's/\$(CATOBJEXT)$$//'`; \
	  dir=$$destdir/$$lang/LC_MESSAGES; \
	  if test -r "$(MKINSTALLDIRS)"; then \
	    $(MKINSTALLDIRS) $$dir; \
	  else \
	    $(SHELL) $(top_srcdir)/mkinstalldirs $$dir; \
	  fi; \
	  if test -r $$cat; then \
	    $(INSTALL_DATA) $$cat $$dir/$(PACKAGE)$(INSTOBJEXT); \
	    echo "installing $$cat as $$dir/$(PACKAGE)$(INSTOBJEXT)"; \
	  else \
	    $(INSTALL_DATA) $(srcdir)/$$cat $$dir/$(PACKAGE)$(INSTOBJEXT); \
	    echo "installing $(srcdir)/$$cat as" \
		 "$$dir/$(PACKAGE)$(INSTOBJEXT)"; \
	  fi; \
	  if test -r $$cat.m; then \
	    $(INSTALL_DATA) $$cat.m $$dir/$(PACKAGE)$(INSTOBJEXT).m; \
	    echo "installing $$cat.m as $$dir/$(PACKAGE)$(INSTOBJEXT).m"; \
	  else \
	    if test -r $(srcdir)/$$cat.m ; then \
	      $(INSTALL_DATA) $(srcdir)/$$cat.m \
		$$dir/$(PACKAGE)$(INSTOBJEXT).m; \
	      echo "installing $(srcdir)/$$cat as" \
		   "$$dir/$(PACKAGE)$(INSTOBJEXT).m"; \
	    else \
	      true; \
	    fi; \
	  fi; \
	done
	if test "$(PACKAGE)" = "gettext"; then \
	  if test -r "$(MKINSTALLDIRS)"; then \
	    $(MKINSTALLDIRS) $(gettextsrcdir); \
	  else \
	    $(SHELL) $(top_srcdir)/mkinstalldirs $(gettextsrcdir); \
	  fi; \
	  $(INSTALL_DATA) $(srcdir)/Makefile.in.in \
			  $(gettextsrcdir)/Makefile.in.in; \
	else \
	  : ; \
	fi

# Define this as empty until I found a useful application.
installcheck:

uninstall:
	catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  lang=`echo $$cat | sed 's/\$(CATOBJEXT)$$//'`; \
	  rm -f $(localedir)/$$lang/LC_MESSAGES/$(PACKAGE)$(INSTOBJEXT); \
	  rm -f $(localedir)/$$lang/LC_MESSAGES/$(PACKAGE)$(INSTOBJEXT).m; \
	  rm -f $(gnulocaledir)/$$lang/LC_MESSAGES/$(PACKAGE)$(INSTOBJEXT); \
	  rm -f $(gnulocaledir)/$$lang/LC_MESSAGES/$(PACKAGE)$(INSTOBJEXT).m; \
	done
	rm -f $(gettextsrcdir)/po-Makefile.in.in

check: all

cat-id-tbl.o: ../intl/libgettext.h

dvi info tags TAGS ID:

mostlyclean:
	rm -f core core.* *.pox $(PACKAGE).po *.old.po cat-id-tbl.tmp intl2po
	rm -fr *.o $(top_srcdir)/src/arch/win32/*.po.c $(top_srcdir)/src/arch/amiga/*.po.c

clean: mostlyclean

distclean: clean
	rm -f Makefile Makefile.in POTFILES *.mo *.msg *.cat *.cat.m

maintainer-clean: distclean
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."
	rm -f $(GMOFILES)

distdir = ../$(PACKAGE)-$(VERSION)/$(subdir)
dist distdir: update-po $(DISTFILES)
	dists="$(DISTFILES)"; \
	for file in $$dists; do \
	  ln $(srcdir)/$$file $(distdir) 2> /dev/null \
	    || cp -p $(srcdir)/$$file $(distdir); \
	done

update-po: Makefile intl2po $(POTFILES)
	$(MAKE) $(PACKAGE).pot
	PATH=`pwd`/../src:$$PATH; \
	cd $(srcdir); \
	catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  lang=`echo $$cat | sed 's/\$(CATOBJEXT)$$//'`; \
	  mv $$lang.po $$lang.old.po; \
	  echo "$$lang:"; \
	  if $(MSGMERGE) $$lang.old.po $(PACKAGE).pot -o $$lang.po; then \
	    rm -f $$lang.old.po; \
	  else \
	    echo "msgmerge for $$cat failed!"; \
	    rm -f $$lang.po; \
	    mv $$lang.old.po $$lang.po; \
	  fi; \
	done

intl2po: intl2po.c
	$(CC) $(INCLUDES) $(CFLAGS) $(srcdir)/intl2po.c -o intl2po
#	gcc $(srcdir)/intl2po.c -o intl2po

po2table: po2table.c
	$(CC) $(INCLUDES) $(CFLAGS) $(srcdir)/po2table.c -o po2table
#	gcc $(srcdir)/po2table.c -o po2table

gen_amiga_intl_c: po2table po2table.c gen_amiga_intl_c.c
	$(CC) $(INCLUDES) $(CFLAGS) $(srcdir)/gen_amiga_intl_c.c -o gen_amiga_intl_c
#	gcc $(srcdir)/gen_amiga_intl_c.c -o gen_amiga_intl_c

gen_translate_c: po2table po2table.c gen_translate_c.c
	$(CC) $(INCLUDES) $(CFLAGS) $(srcdir)/gen_translate_c.c -o gen_translate_c
#	gcc $(srcdir)/gen_translate_c.c -o gen_translate_c

gen_win32_rc: po2table po2table.c gen_win32_rc.c
	$(CC) $(INCLUDES) $(CFLAGS) $(srcdir)/gen_win32_rc.c -o gen_win32_rc
#	gcc $(srcdir)/gen_win32_rc.c -o gen_win32_rc

po_table.h: da.po de.po es.po fr.po hu.po it.po ko.po nl.po pl.po ru.po sv.po tr.po po2table
	./po2table

trans-update:
	( if test 'x$(srcdir)' != 'x.'; then echo "make trans-update can only be done from the source tree"; exit; fi )
	$(MAKE) update-po
	rm -f sv_iso.po
	iconv -f UTF-8 -t ISO-8859-1 <sv.po >sv_iso.po
	rm -f nl_iso.po
	iconv -f UTF-8 -t ISO-8859-1 <nl.po >nl_iso.po
	rm -f pl_iso.po
	iconv -f UTF-8 -t ISO-8859-2 <pl.po >pl_iso.po
	rm -f po_table.h
	$(MAKE) po_table.h
	$(MAKE) gen_translate_c
	./gen_translate_c 
	rm -f ../src/translate_text.c
	mv ../src/temp_translate.h ../src/translate_text.c
	$(MAKE) gen_amiga_intl_c
	./gen_amiga_intl_c
	rm -f ../src/arch/amigaos/intl_text.c
	mv ../src/arch/amigaos/temp_intl.h ../src/arch/amigaos/intl_text.c
	$(MAKE) gen_win32_rc
	./gen_win32_files.sh $(POTFILES)
	( if test 'x0' = 'x1'; then cat >tmp_trans.txt ../src/translate.txt ../src/arch/amigaos/intl.txt; ./check_obsolete.sh $(POTFILES) <tmp_trans.txt; rm -f tmp_trans.txt; fi )

POTFILES: POTFILES.in intl2po
	( if test 'x$(srcdir)' != 'x.'; then \
	    posrcprefix='$(top_srcdir)/'; \
	  else \
	    posrcprefix="../"; \
	  fi; \
	  rm -f $@-t $@ \
	    && (sed -e '/^#/d' -e '/^[ 	]*$$/d' \
		    -e "s@.*@	$$posrcprefix& \\\\@" < $(srcdir)/$@.in \
		| sed -e '$$s/\\$$//') > $@-t \
	    && chmod a-w $@-t \
	    && mv $@-t $@ )

Makefile: Makefile.in.in ../config.status POTFILES
	cd .. \
	  && CONFIG_FILES=$(subdir)/$@.in CONFIG_HEADERS= \
	       $(SHELL) ./config.status

# Tell versions [3.59,3.63) of GNU make not to export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
