/*
 * about.c - Simple Xaw(3d)-based graphical user interface.  It uses widgets
 * from the Free Widget Foundation and Robert W. McMullen.
 *
 * Written by
 *  Ettore Perazzoli <ettore@comm2000.it>
 *  Andre Fachat <fachat@physik.tu-chemnitz.de>
 *
 * Support for multiple visuals and depths by
 *  Teemu Rantanen <tvr@cs.hut.fi>
 *
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */

#include "vice.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <X11/Intrinsic.h>

/* Xaw or Xaw3d */
#ifdef USE_XAW3D
#include <X11/Xaw3d/Paned.h>
#include <X11/Xaw3d/Form.h>
#include <X11/Xaw3d/Box.h>
#include <X11/Xaw3d/Label.h>
#include <X11/Xaw3d/Command.h>
#else
#include <X11/Xaw/Paned.h>
#include <X11/Xaw/Form.h>
#include <X11/Xaw/Box.h>
#include <X11/Xaw/Label.h>
#include <X11/Xaw/Command.h>
#endif

#include "info.h"
#include "platform_discovery.h"
#include "uiapi.h"
#include "version.h"
#include "videoarch.h"
#include "vsync.h"

#ifdef USE_SVN_REVISION
#include "svnversion.h"
#endif

static UI_CALLBACK(info_dialog_close_callback)
{
    *((ui_button_t *)UI_MENU_CB_PARAM) = 1;
}
/* ------------------------------------------------------------------------- */

static UI_CALLBACK(info_dialog_license_callback)
{
    ui_show_text(_("VICE is FREE software!"), info_license_text, -1, -1);
}

static UI_CALLBACK(info_dialog_no_warranty_callback)
{
    ui_show_text(_("No warranty!"), info_warranty_text, -1, -1);
}

static UI_CALLBACK(info_dialog_contrib_callback)
{
    ui_show_text(_("Contributors to the VICE project"), info_contrib_text, -1, -1);
}

static Widget build_info_dialog(Widget parent, int *return_flag, ...)
{
    Widget shell, pane, info_form, button_form, tmp, prevlabel = NULL;
    va_list arglist;
    String str;

    shell = ui_create_transient_shell(parent, "infoDialogShell");
    pane = XtVaCreateManagedWidget("infoDialog",
                                   panedWidgetClass, shell,
                                   NULL);
    info_form = XtVaCreateManagedWidget("textForm",
                                        formWidgetClass, pane,
                                        NULL);
    button_form = XtVaCreateManagedWidget("buttonBox",
                                          boxWidgetClass, pane,
                                          XtNshowGrip, False,
                                          XtNskipAdjust, True,
                                          XtNorientation, XtorientHorizontal,
                                          NULL);
    va_start(arglist, return_flag);
    while ((str = va_arg(arglist, String))) {
        tmp = XtVaCreateManagedWidget("infoString",
                                      labelWidgetClass, info_form,
                                      XtNlabel, str,
                                      XtNjustify, XtJustifyCenter,
                                      XtNresize, False,
                                      XtNwidth, 220,
                                      NULL);
        if (prevlabel) {
            XtVaSetValues(tmp, XtNfromVert, prevlabel, NULL);
        }
        prevlabel = tmp;
    }
    va_end(arglist);
    tmp = XtVaCreateManagedWidget("closeButton",
                                  commandWidgetClass, button_form,
                                  NULL);
    XtAddCallback(tmp, XtNcallback, info_dialog_close_callback, (XtPointer)return_flag);
    tmp = XtVaCreateManagedWidget("licenseButton",
                                  commandWidgetClass, button_form,
                                  XtNfromHoriz, tmp,
                                  NULL);
    XtAddCallback(tmp, XtNcallback, info_dialog_license_callback, NULL);
    tmp = XtVaCreateManagedWidget("noWarrantyButton",
                                  commandWidgetClass, button_form,
                                  XtNfromHoriz, tmp,
                                  NULL);
    XtAddCallback(tmp, XtNcallback, info_dialog_no_warranty_callback, NULL);
    tmp = XtVaCreateManagedWidget("contribButton",
                                  commandWidgetClass, button_form,
                                  XtNfromHoriz, tmp,
                                  NULL);
    XtAddCallback(tmp, XtNcallback, info_dialog_contrib_callback, NULL);
    return pane;
}

UI_CALLBACK(ui_about)
{
    static Widget info_dialog;
    static int is_closed;

    if (!info_dialog) {
        info_dialog = build_info_dialog(_ui_top_level, &is_closed,
                                        "",
                                        "V I C E",
                                        "",
#ifdef USE_SVN_REVISION
#ifdef USE_XAW3D
                                        "Version " VERSION " rev " VICE_SVN_REV_STRING " (XAW3D " PLATFORM_CPU " " PLATFORM_OS " " PLATFORM_COMPILER ")",
#else
                                        "Version " VERSION " rev " VICE_SVN_REV_STRING " (XAW " PLATFORM_CPU " " PLATFORM_OS " " PLATFORM_COMPILER ")",
#endif
#else
#ifdef USE_XAW3D
                                        "Version " VERSION " (XAW3D " PLATFORM_CPU " " PLATFORM_OS " " PLATFORM_COMPILER ")",
#else
                                        "Version " VERSION " (XAW " PLATFORM_CPU " " PLATFORM_OS " " PLATFORM_COMPILER ")",
#endif
#endif
#ifdef UNSTABLE
                                        "(unstable)",
#endif
                                        "",
                                        "Copyright C 1998-2014 Dag Lem",
                                        "Copyright C 1999-2014 Andreas Matthies",
                                        "Copyright C 1999-2014 Martin Pottendorfer",
                                        "Copyright C 2005-2014 Marco van den Heuvel",
                                        "Copyright C 2006-2014 Christian Vogelgsang",
                                        "Copyright C 2007-2014 Fabrizio Gennari",
                                        "Copyright C 2007-2014 Daniel Kahlin",
                                        "Copyright C 2008-2014 Antti S. Lankila",
                                        "Copyright C 2009-2014 Groepaz",
                                        "Copyright C 2009-2014 Ingo Korb",
                                        "Copyright C 2009-2014 Errol Smith",
                                        "Copyright C 2009-2014 Olaf Seibert",
                                        "Copyright C 2011-2014 Marcus Sutton",
                                        "Copyright C 2011-2014 Ulrich Schulz",
                                        "Copyright C 2011-2014 Stefan Haubenthal",
                                        "Copyright C 2011-2014 Thomas Giesel",
                                        "Copyright C 2011-2014 Kajtar Zsolt",
                                        "Copyright C 2012-2014 Benjamin 'BeRo' Rosseaux",
                                        "",
                                        _("Official VICE homepage:"),
                                        "http://vice-emu.sourceforge.net/",
                                        "",
                                        NULL);
    }
    vsync_suspend_speed_eval();
    ui_popup(XtParent(info_dialog), _("VICE Information"), False);

    is_closed = 0;
    while (!is_closed) {
        ui_dispatch_next_event();
    }
    ui_popdown(XtParent(info_dialog));
}
