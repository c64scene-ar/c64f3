/*
 * ui-threads.h 
 *
 * Written by
 *  pottendo <pottendo@gmx.net>
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

#ifndef __ui_threads_h
#define __ui_threads_h

void mbuffer_init(void *widget, int w, int h, int depth, int shell);
unsigned char *mbuffer_get_buffer(struct timespec *ts, int shell);

void dthread_init(void);
void dthread_lock();
void dthread_unlock();
int dthread_ui_init(int *argc, char **argv);
int dthread_ui_init_finish(void);
void dthread_build_screen_canvas(video_canvas_t *c);
int dthread_ui_open_canvas_window(video_canvas_t *c, const char *t, int wi, int he, int na);
void dthread_ui_dispatch_events(void);
void dthread_ui_trigger_resize(void);
void dthread_ui_trigger_window_resize(video_canvas_t *c);
int dthread_configure_callback_canvas(void *w, void *e, void *cd);
void dthread_shutdown(void);

int ui_init2(int *argc, char **argv);
int ui_init_finish2(void);
void build_screen_canvas2(video_canvas_t *c);
void build_screen_canvas_widget2(video_canvas_t *c);
int ui_open_canvas_window2(video_canvas_t *c, const char *t, int wi, int he, int na);
void ui_dispatch_events2(void);
void ui_trigger_resize2(void);
void ui_trigger_window_resize2(video_canvas_t *c);
#ifdef USE_GNOMEUI
int configure_callback_canvas2(GtkWidget *w, GdkEvent *e, gpointer cd);
void gl_render_canvas(GtkWidget *w, video_canvas_t *canvas, 
		      struct s_mbufs *buffers, int from, int to, int do_s);
#else
#warning "ui-threads configured, but arch isn't ported to use ui-threads."
#endif
#endif /* __ui_threads_h */
