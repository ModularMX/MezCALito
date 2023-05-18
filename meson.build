# to setup for the first time
# $ meson setup build --cross-file=arm-none-eabi.ini --buildtype=plain

# to compile
# $ meson compile -C build

# to reconfigure every time the cross file or the meson file has change
# $ meson setup --wipe build

project('mezcalito', 'c')
executable('demo', 'main.c', 'startup.c')
