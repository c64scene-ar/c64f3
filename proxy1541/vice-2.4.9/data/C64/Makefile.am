c64dir = $(VICEDIR)/C64

roms = \
	basic \
	chargen \
	jpchrgen \
	kernal \
	sxkernal \
	edkernal \
	gskernal \
	jpkernal

romsets = \
	default.vrs

palettes = \
	c64hq.vpl \
	c64s.vpl \
	ccs64.vpl \
	default.vpl \
	frodo.vpl \
	godot.vpl \
	pc64.vpl \
	vice.vpl

x11_keymaps = \
	x11_sym.vkm \
	x11_pos.vkm \
	x11_posger.vkm \
	x11_symger.vkm \
	x11_keyrah.vkm \
	x11_keyrah_de.vkm

sdl_keymaps = \
	sdl_sym.vkm \
	sdl_sym_da.vkm \
	sdl_sym_de.vkm \
	sdl_sym_fi.vkm \
	sdl_sym_no.vkm \
	sdl_keyrah.vkm \
	sdl_keyrah_de.vkm

extra_keymaps = \
	amiga_sym.vkm \
	amiga_pos.vkm \
	beos_sym.vkm \
	beos_pos.vkm \
	dos_sym.vkm \
	dos_pos.vkm \
	os2.vkm \
	os2_sym.vkm \
	osx_pos.vkm \
	osx_sym_de.vkm \
	osx_sym_us.vkm \
	win_sym_de.vkm \
	win_sym_it.vkm \
	win_sym_us.vkm \
	win_pos.vkm

win32_files = \
	win_hotkeys.vhk \
	win_shortcuts.vsc

sym_file = \
	c64mem.sym

if SDL_COMPILE
c64_DATA = $(roms) $(romsets) $(palettes) $(sdl_keymaps) $(sym_file)

EXTRA_DIST = $(c64_DATA) $(extra_keymaps) $(x11_keymaps) $(win32_files)
else
c64_DATA = $(roms) $(romsets) $(palettes) $(x11_keymaps) $(sym_file)

EXTRA_DIST = $(c64_DATA) $(extra_keymaps) $(sdl_keymaps) $(win32_files)
endif
