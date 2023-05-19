# front end maek targets, there is a problem with meson, we need to type quiet long lines in our 
# terminal if we want to compiler or rebuild, but with make we can simplify to up to two words

# build project
all :
	meson compile -C build
# remove binaries
clean :
	meson setup --wipe build
# flash binaries into the mcu
flash:
	meson compile -C build flash
