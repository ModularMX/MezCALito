# front end maek targets, there is a problem with meson, we need to type quiet long lines in our 
# terminal if we want to compiler or rebuild, but with make we can simplify to up to two words

# build project
all :
	ninja -C build clang-format
	meson compile -C build

.PHONY : clean docs flash utest

# remove binaries
clean :
	meson setup --wipe build
# flash binaries into the mcu
docs :
	meson compile -C build docs
	firefox build/sphinx/index.html
# flash binaries into the mcu
flash :
	meson compile -C build flash
# run ceedling unit tests, for some reason we cannot run this from meson
utest :
	ceedling gcov:all utils:gcov
