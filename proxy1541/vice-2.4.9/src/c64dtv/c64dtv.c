/*
 * c64dtv.c
 *
 * Written by
 *  Andreas Boose <viceteam@t-online.de>
 *  Ettore Perazzoli <ettore@comm2000.it>
 *  Teemu Rantanen <tvr@cs.hut.fi>
 *  Daniel Kahlin <daniel@kahlin.net>
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

#include <stdio.h>
#include <stdlib.h>

#include "attach.h"
#include "autostart.h"
#include "c64cia.h"
#include "c64dtv-cmdline-options.h"
#include "c64dtv-resources.h"
#include "c64dtv-snapshot.h"
#include "c64dtv.h"
#include "c64dtvmem.h"
#include "c64dtvmemsnapshot.h"
#include "c64fastiec.h"
#include "c64iec.h"
#include "c64keyboard.h"
#include "c64memrom.h"
#include "c64ui.h"
#include "cia.h"
#include "clkguard.h"
#include "debug.h"
#include "diskimage.h"
#include "drive-cmdline-options.h"
#include "drive-resources.h"
#include "drive-sound.h"
#include "drive.h"
#include "drivecpu.h"
#include "flash-trap.h"
#include "fliplist.h"
#include "fsdevice.h"
#include "gfxoutput.h"
#include "imagecontents.h"
#include "init.h"
#include "kbdbuf.h"
#include "keyboard.h"
#include "log.h"
#include "machine-drive.h"
#include "machine-printer.h"
#include "machine-video.h"
#include "machine.h"
#include "maincpu.h"
#include "mem.h"
#include "monitor.h"
#include "network.h"
#include "parallel.h"
#include "patchrom.h"
#include "printer.h"
#include "resources.h"
#include "rs232drv.h"
#include "screenshot.h"
#include "serial.h"
#include "sid-cmdline-options.h"
#include "sid-resources.h"
#include "sid.h"
#include "sound.h"
#include "tape.h"
#include "traps.h"
#include "types.h"
#include "userport_joystick.h"
#include "vice-event.h"
#include "vicii.h"
#include "video.h"
#include "video-sound.h"
#include "vsync.h"

#ifdef HAVE_MOUSE
#include "mouse.h"
#endif

machine_context_t machine_context;

#define NUM_KEYBOARD_MAPPINGS 3

static char *machine_keymap_res_name_list[NUM_KEYBOARD_MAPPINGS] = {
    "KeymapSymFile", "KeymapPosFile", "KeymapSymDeFile"
};

char *machine_keymap_file_list[NUM_KEYBOARD_MAPPINGS] = {
    NULL, NULL, NULL
};

char *machine_get_keymap_res_name(int val)
{
    if (val < 0 || val > NUM_KEYBOARD_MAPPINGS) {
        return NULL;
    }
    return machine_keymap_res_name_list[val];
}

const char machine_name[] = "C64DTV";
int machine_class = VICE_MACHINE_C64DTV;

static void machine_vsync_hook(void);

/* ------------------------------------------------------------------------- */

static const trap_t c64_serial_traps[] = {
    {
        "SerialListen",
        0xED24,
        0xEDAB,
        { 0x20, 0x97, 0xEE },
        serial_trap_attention,
        c64memrom_trap_read,
        c64memrom_trap_store
    },
    {
        "SerialSaListen",
        0xED37,
        0xEDAB,
        { 0x20, 0x8E, 0xEE },
        serial_trap_attention,
        c64memrom_trap_read,
        c64memrom_trap_store
    },
    {
        "SerialSendByte",
        0xED41,
        0xEDAB,
        { 0x20, 0x97, 0xEE },
        serial_trap_send,
        c64memrom_trap_read,
        c64memrom_trap_store
    },
    {
        "SerialReceiveByte",
        0xEE14,
        0xEDAB,
        { 0xA9, 0x00, 0x85 },
        serial_trap_receive,
        c64memrom_trap_read,
        c64memrom_trap_store
    },
    {
        "SerialReady",
        0xEEA9,
        0xEDAB,
        { 0xAD, 0x00, 0xDD },
        serial_trap_ready,
        c64memrom_trap_read,
        c64memrom_trap_store
    },
    {
        NULL,
        0,
        0,
        { 0, 0, 0 },
        NULL,
        NULL,
        NULL
    }
};

static log_t c64_log = LOG_ERR;
static machine_timing_t machine_timing;

/* ------------------------------------------------------------------------ */

static const trap_t c64dtv_flash_traps[] = {
    {
        "FlashSeekNext",
        0xF77F,
        0xF782,
        { 0x20, 0x79, 0xF8 },
        flash_trap_seek_next,
        c64memrom_trap_read,
        c64memrom_trap_store
    },
    {
        "FlashLoadBody",
        0xF7CF,
        0xF7D2,
        { 0x20, 0xE9, 0xF7 },
        flash_trap_load_body,
        c64memrom_trap_read,
        c64memrom_trap_store
    },
    {
        NULL,
        0,
        0,
        { 0, 0, 0 },
        NULL,
        NULL,
        NULL
    }
};

/* ------------------------------------------------------------------------ */

/* C64-specific resource initialization.  This is called before initializing
   the machine itself with `machine_init()'.  */
int machine_resources_init(void)
{
    if (traps_resources_init() < 0) {
        init_resource_fail("traps");
        return -1;
    }
    if (c64dtv_resources_init() < 0) {
        init_resource_fail("c64dtv");
        return -1;
    }
    if (c64dtvmem_resources_init() < 0) {
        init_resource_fail("c64dtvmem");
        return -1;
    }
    if (vicii_resources_init() < 0) {
        init_resource_fail("vicii");
        return -1;
    }
    if (sid_resources_init() < 0) {
        init_resource_fail("sid");
        return -1;
    }
    if (rs232drv_resources_init() < 0) {
        init_resource_fail("rs232drv");
        return -1;
    }
    if (serial_resources_init() < 0) {
        init_resource_fail("serial");
        return -1;
    }
    if (flash_trap_resources_init() < 0) {
        init_resource_fail("flash_trap");
        return -1;
    }
    if (printer_resources_init() < 0) {
        init_resource_fail("printer");
        return -1;
    }
    if (joystick_resources_init() < 0) {
        init_resource_fail("joystick");
        return -1;
    }
    if (gfxoutput_resources_init() < 0) {
        init_resource_fail("gfxoutput");
        return -1;
    }
    if (fliplist_resources_init() < 0) {
        init_resource_fail("flip list");
        return -1;
    }
    if (file_system_resources_init() < 0) {
        init_resource_fail("file system");
        return -1;
    }
    /* Initialize file system device-specific resources.  */
    if (fsdevice_resources_init() < 0) {
        init_resource_fail("file system device");
        return -1;
    }
    if (disk_image_resources_init() < 0) {
        init_resource_fail("disk image");
        return -1;
    }
    if (event_resources_init() < 0) {
        init_resource_fail("event");
        return -1;
    }
    if (kbdbuf_resources_init() < 0) {
        init_resource_fail("Keyboard");
        return -1;
    }
    if (autostart_resources_init() < 0) {
        init_resource_fail("autostart");
        return -1;
    }
#ifdef HAVE_NETWORK
    if (network_resources_init() < 0) {
        init_resource_fail("network");
        return -1;
    }
#endif
#ifdef DEBUG
    if (debug_resources_init() < 0) {
        init_resource_fail("debug");
        return -1;
    }
#endif
#ifdef HAVE_MOUSE
    if (mouse_resources_init() < 0) {
        init_resource_fail("mouse");
        return -1;
    }
#endif
#ifndef COMMON_KBD
    if (kbd_resources_init() < 0) {
        init_resource_fail("kbd");
        return -1;
    }
#endif
    if (drive_resources_init() < 0) {
        init_resource_fail("drive");
        return -1;
    }
    if (userport_joystick_resources_init() < 0) {
        init_resource_fail("userport joystick");
        return -1;
    }
    return 0;
}

void machine_resources_shutdown(void)
{
    serial_shutdown();
    flash_trap_shutdown();
    flash_trap_resources_shutdown();
    c64dtv_resources_shutdown();
    c64dtvmem_resources_shutdown();
    rs232drv_resources_shutdown();
    printer_resources_shutdown();
    drive_resources_shutdown();
    fsdevice_resources_shutdown();
    disk_image_resources_shutdown();
}

/* C64-specific command-line option initialization.  */
int machine_cmdline_options_init(void)
{
    if (traps_cmdline_options_init() < 0) {
        init_cmdline_options_fail("traps");
        return -1;
    }
    if (c64dtv_cmdline_options_init() < 0) {
        init_cmdline_options_fail("c64dtv");
        return -1;
    }
    if (c64dtvmem_cmdline_options_init() < 0) {
        init_cmdline_options_fail("c64dtvmem");
        return -1;
    }
    if (vicii_cmdline_options_init() < 0) {
        init_cmdline_options_fail("vicii");
        return -1;
    }
    if (sid_cmdline_options_init() < 0) {
        init_cmdline_options_fail("sid");
        return -1;
    }
    if (rs232drv_cmdline_options_init() < 0) {
        init_cmdline_options_fail("rs232drv");
        return -1;
    }
    if (serial_cmdline_options_init() < 0) {
        init_cmdline_options_fail("serial");
        return -1;
    }
    if (flash_trap_cmdline_options_init() < 0) {
        init_cmdline_options_fail("flash trap");
        return -1;
    }
    if (printer_cmdline_options_init() < 0) {
        init_cmdline_options_fail("printer");
        return -1;
    }
    if (joystick_cmdline_options_init() < 0) {
        init_cmdline_options_fail("joystick");
        return -1;
    }
    if (gfxoutput_cmdline_options_init() < 0) {
        init_cmdline_options_fail("gfxoutput");
        return -1;
    }
    if (fliplist_cmdline_options_init() < 0) {
        init_cmdline_options_fail("flip list");
        return -1;
    }
    if (file_system_cmdline_options_init() < 0) {
        init_cmdline_options_fail("attach");
        return -1;
    }
    if (fsdevice_cmdline_options_init() < 0) {
        init_cmdline_options_fail("file system");
        return -1;
    }
    if (disk_image_cmdline_options_init() < 0) {
        init_cmdline_options_fail("disk image");
        return -1;
    }
    if (event_cmdline_options_init() < 0) {
        init_cmdline_options_fail("event");
        return -1;
    }
    if (kbdbuf_cmdline_options_init() < 0) {
        init_cmdline_options_fail("keyboard");
        return -1;
    }
    if (autostart_cmdline_options_init() < 0) {
        init_cmdline_options_fail("autostart");
        return -1;
    }
#ifdef DEBUG
    if (debug_cmdline_options_init() < 0) {
        init_cmdline_options_fail("debug");
        return -1;
    }
#endif
#ifdef HAVE_MOUSE
    if (mouse_cmdline_options_init() < 0) {
        init_cmdline_options_fail("mouse");
        return -1;
    }
#endif
#ifndef COMMON_KBD
    if (kbd_cmdline_options_init() < 0) {
        init_cmdline_options_fail("kbd");
        return -1;
    }
#endif
    if (drive_cmdline_options_init() < 0) {
        init_cmdline_options_fail("drive");
        return -1;
    }
    if (userport_joystick_cmdline_options_init() < 0) {
        init_cmdline_options_fail("userport_joystick");
        return -1;
    }
    return 0;
}

static void c64dtv_monitor_init(void)
{
    unsigned int dnr;
    monitor_cpu_type_t asm6502dtv, asm6502, asmR65C02;
    monitor_interface_t *drive_interface_init[DRIVE_NUM];
    monitor_cpu_type_t *asmarray[4];

    asmarray[0] = &asm6502dtv;
    asmarray[1] = &asm6502;
    asmarray[2] = &asmR65C02;
    asmarray[3] = NULL;

    asm6502dtv_init(&asm6502dtv);
    asm6502_init(&asm6502);
    asmR65C02_init(&asmR65C02);

    for (dnr = 0; dnr < DRIVE_NUM; dnr++) {
        drive_interface_init[dnr] = drivecpu_monitor_interface_get(dnr);
    }

    /* Initialize the monitor.  */
    monitor_init(maincpu_monitor_interface_get(), drive_interface_init,
                 asmarray);
}

void machine_setup_context(void)
{
    cia1_setup_context(&machine_context);
    cia2_setup_context(&machine_context);
    machine_printer_setup_context(&machine_context);
}
int machine_specific_init_iec_proxy(void) {return 0;}

/* C64-specific initialization.  */
int machine_specific_init(void)
{
    int delay;

    c64_log = log_open("C64");

    if (mem_load() < 0) {
        return -1;
    }

    event_init();

    /* Setup trap handling.  */
    traps_init();

    /* Initialize serial traps.  */
    if (serial_init(c64_serial_traps) < 0) {
        return -1;
    }

    serial_trap_init(0xa4);
    serial_iec_bus_init();

    if (!video_disabled_mode) {
        joystick_init();
    }

    gfxoutput_init();

    /* Initialize flash traps.  */
    if (flash_trap_init(c64dtv_flash_traps) < 0) {
        return -1;
    }

    /* Initialize RS232 handler.  */
    rs232drv_init();

    /* Initialize print devices.  */
    printer_init();

    /* Fire up the hardware-level drive emulation.  */
    drive_init();

    disk_image_init();

    /* Initialize autostart.  */
    resources_get_int("AutostartDelay", &delay);
    if (delay == 0) {
        delay = 3; /* default */
    }
    autostart_init((CLOCK)(delay * C64_PAL_RFSH_PER_SEC * C64_PAL_CYCLES_PER_RFSH),
                   1, 0xcc, 0xd1, 0xd3, 0xd5);

    if (vicii_init(VICII_DTV) == NULL && !console_mode) {
        return -1;
    }

    cia1_init(machine_context.cia1);
    cia2_init(machine_context.cia2);

#ifndef COMMON_KBD
    /* Initialize the keyboard.  */
    if (c64_kbd_init() < 0) {
        return -1;
    }
#endif

    c64keyboard_init();

    c64dtv_monitor_init();

    /* Initialize vsync and register our hook function.  */
    vsync_init(machine_vsync_hook);
    vsync_set_machine_parameter(machine_timing.rfsh_per_sec,
                                machine_timing.cycles_per_sec);

    /* Initialize native sound chip */
    sid_sound_chip_init();

    drive_sound_init();
    video_sound_init();

    /* Initialize sound.  Notice that this does not really open the audio
       device yet.  */
    sound_init(machine_timing.cycles_per_sec, machine_timing.cycles_per_rfsh);

    /* Initialize keyboard buffer.  */
    kbdbuf_init(631, 198, 10, (CLOCK)(machine_timing.rfsh_per_sec * machine_timing.cycles_per_rfsh));

    /* Initialize the C64-specific part of the UI.  */
    if (!console_mode) {
        c64dtvui_init();
    }

    /* Initialize the C64DTV.  */
    c64dtv_init();

#ifdef HAVE_MOUSE
    /* Initialize mouse support (if present).  */
    mouse_init();
#endif

    c64iec_init();
    c64fastiec_init();

    machine_drive_stub();
#if defined (USE_XF86_EXTENSIONS) && \
    (defined(USE_XF86_VIDMODE_EXT) || defined (HAVE_XRANDR))
    {
        /* set fullscreen if user used `-fullscreen' on cmdline */
        int fs;
        resources_get_int("UseFullscreen", &fs);
        if (fs) {
            resources_set_int("VICIIFullscreen", 1);
        }
    }
#endif

    return 0;
}

/* C64-specific reset sequence.  */
void machine_specific_reset(void)
{
    serial_traps_reset();
    flash_traps_reset();

    ciacore_reset(machine_context.cia1);
    ciacore_reset(machine_context.cia2);
    sid_reset();

    rs232drv_reset();

    printer_reset();

    /* FIXME */
    /* reset_reu(); */

    /* The VIC-II must be the *last* to be reset.  */
    vicii_reset();

    drive_reset();
    c64dtvmem_reset();
}

void machine_specific_powerup(void)
{
    vicii_reset_registers();
}

void machine_specific_shutdown(void)
{
    ciacore_shutdown(machine_context.cia1);
    ciacore_shutdown(machine_context.cia2);

#ifdef HAVE_MOUSE
    mouse_shutdown();
#endif

    /* close the video chip(s) */
    vicii_shutdown();

    c64dtvmem_shutdown();

    c64dtvui_shutdown();
}

void machine_handle_pending_alarms(int num_write_cycles)
{
    vicii_handle_pending_alarms_external(num_write_cycles);
}

/* ------------------------------------------------------------------------- */

/* This hook is called at the end of every frame.  */
static void machine_vsync_hook(void)
{
    CLOCK sub;

    network_hook();

    drive_vsync_hook();

    autostart_advance();

    screenshot_record();

    sub = clk_guard_prevent_overflow(maincpu_clk_guard);

    /* The drive has to deal both with our overflowing and its own one, so
       it is called even when there is no overflowing in the main CPU.  */
    drivecpu_prevent_clk_overflow_all(sub);
}

void machine_set_restore_key(int v)
{
    c64keyboard_restore_key(v);
}

int machine_has_restore_key(void)
{
    return 1;
}

/* ------------------------------------------------------------------------- */

long machine_get_cycles_per_second(void)
{
    return machine_timing.cycles_per_sec;
}

long machine_get_cycles_per_frame(void)
{
    return machine_timing.cycles_per_rfsh;
}

void machine_get_line_cycle(unsigned int *line, unsigned int *cycle, int *half_cycle)
{
    *line = (unsigned int)((maincpu_clk) / machine_timing.cycles_per_line % machine_timing.screen_lines);

    *cycle = (unsigned int)((maincpu_clk) % machine_timing.cycles_per_line);

    *half_cycle = (int)-1;
}

void machine_change_timing(int timeval)
{
    int border_mode;

    switch (timeval) {
        default:
        case MACHINE_SYNC_PAL ^ VICII_BORDER_MODE(VICII_NORMAL_BORDERS):
        case MACHINE_SYNC_NTSC ^ VICII_BORDER_MODE(VICII_NORMAL_BORDERS):
            timeval ^= VICII_BORDER_MODE(VICII_NORMAL_BORDERS);
            border_mode = VICII_NORMAL_BORDERS;
            break;
        case MACHINE_SYNC_PAL ^ VICII_BORDER_MODE(VICII_FULL_BORDERS):
        case MACHINE_SYNC_NTSC ^ VICII_BORDER_MODE(VICII_FULL_BORDERS):
            timeval ^= VICII_BORDER_MODE(VICII_FULL_BORDERS);
            border_mode = VICII_FULL_BORDERS;
            break;
        case MACHINE_SYNC_PAL ^ VICII_BORDER_MODE(VICII_DEBUG_BORDERS):
        case MACHINE_SYNC_NTSC ^ VICII_BORDER_MODE(VICII_DEBUG_BORDERS):
            timeval ^= VICII_BORDER_MODE(VICII_DEBUG_BORDERS);
            border_mode = VICII_DEBUG_BORDERS;
            break;
        case MACHINE_SYNC_PAL ^ VICII_BORDER_MODE(VICII_NO_BORDERS):
        case MACHINE_SYNC_NTSC ^ VICII_BORDER_MODE(VICII_NO_BORDERS):
            timeval ^= VICII_BORDER_MODE(VICII_NO_BORDERS);
            border_mode = VICII_NO_BORDERS;
            break;
    }

    switch (timeval) {
        case MACHINE_SYNC_PAL:
            machine_timing.cycles_per_sec = C64_PAL_CYCLES_PER_SEC;
            machine_timing.cycles_per_rfsh = C64_PAL_CYCLES_PER_RFSH;
            machine_timing.rfsh_per_sec = C64_PAL_RFSH_PER_SEC;
            machine_timing.cycles_per_line = C64_PAL_CYCLES_PER_LINE;
            machine_timing.screen_lines = C64_PAL_SCREEN_LINES;
            machine_timing.power_freq = 0;
            break;
        case MACHINE_SYNC_NTSC:
            machine_timing.cycles_per_sec = C64_NTSC_CYCLES_PER_SEC;
            machine_timing.cycles_per_rfsh = C64_NTSC_CYCLES_PER_RFSH;
            machine_timing.rfsh_per_sec = C64_NTSC_RFSH_PER_SEC;
            machine_timing.cycles_per_line = C64_NTSC_CYCLES_PER_LINE;
            machine_timing.screen_lines = C64_NTSC_SCREEN_LINES;
            machine_timing.power_freq = 0;
            break;
        default:
            log_error(c64_log, "Unknown machine timing.");
    }

    vsync_set_machine_parameter(machine_timing.rfsh_per_sec,
                                machine_timing.cycles_per_sec);
    sound_set_machine_parameter(machine_timing.cycles_per_sec,
                                machine_timing.cycles_per_rfsh);
    debug_set_machine_parameter(machine_timing.cycles_per_line,
                                machine_timing.screen_lines);
    drive_set_machine_parameter(machine_timing.cycles_per_sec);
    serial_iec_device_set_machine_parameter(machine_timing.cycles_per_sec);
    sid_set_machine_parameter(machine_timing.cycles_per_sec);
    clk_guard_set_clk_base(maincpu_clk_guard, machine_timing.cycles_per_rfsh);

    vicii_change_timing(&machine_timing, border_mode);
    cia1_set_timing(machine_context.cia1, machine_timing.cycles_per_sec, machine_timing.power_freq);
    cia2_set_timing(machine_context.cia2, machine_timing.cycles_per_sec, machine_timing.power_freq);

    machine_trigger_reset(MACHINE_RESET_MODE_HARD);
}

/* ------------------------------------------------------------------------- */

int machine_write_snapshot(const char *name, int save_roms, int save_disks,
                           int event_mode)
{
    return c64dtv_snapshot_write(name, save_roms, save_disks, event_mode);
}

int machine_read_snapshot(const char *name, int event_mode)
{
    return c64dtv_snapshot_read(name, event_mode);
}

/* ------------------------------------------------------------------------- */

int machine_screenshot(screenshot_t *screenshot, struct video_canvas_s *canvas)
{
    if (canvas != vicii_get_canvas()) {
        return -1;
    }

    vicii_screenshot(screenshot);
    return 0;
}

int machine_canvas_async_refresh(struct canvas_refresh_s *refresh,
                                 struct video_canvas_s *canvas)
{
    if (canvas != vicii_get_canvas()) {
        return -1;
    }

    vicii_async_refresh(refresh);
    return 0;
}

void machine_update_memory_ptrs(void)
{
    vicii_update_memory_ptrs_external();
}

int machine_num_keyboard_mappings(void)
{
    return NUM_KEYBOARD_MAPPINGS;
}

struct image_contents_s *machine_diskcontents_bus_read(unsigned int unit)
{
    return diskcontents_iec_read(unit);
}

BYTE machine_tape_type_default(void)
{
    return TAPE_CAS_TYPE_BAS;
}

/* to avoid linkage problems */
void datasette_trigger_flux_change(unsigned int on)
{
}

void datasette_set_tape_sense(int sense)
{
}

int machine_autodetect_psid(const char *name)
{
    return -1;
}

int machine_addr_in_ram(unsigned int addr)
{
    /* NOTE: while the RAM/ROM distinction is more complicated, this is
       sufficient from autostart's perspective */
    return (addr < 0xe000 && !(addr >= 0xa000 && addr < 0xc000)) ? 1 : 0;
}

const char *machine_get_name(void)
{
    return machine_name;
}
