# to setup for the first time
# $ meson setup build --cross-file=arm-none-eabi.ini --buildtype=plain

# to compile
# $ meson compile -C build

# to reconfigure every time the cross file or the meson file has change
# $ meson setup --wipe build


project( 'mezcalito', 'c', 
    version : '0.0.0', 
    default_options : ['c_std=c11', 'buildtype=plain']
)

# get the project name to be reference all over the build targets
name = meson.project_name()
# references to cross file variables
c_link_args = []

# project source files
srcs = files(
    'main.c',
    'startup.c',
    'autosar/mcal/Port.c',
    'cfg/Port_Cfg.c'
)

# project linker file
linker = 'linker.ld'

# to generate the binary
main = executable( name, 
    sources : srcs,
    name_suffix : 'elf',
    link_args : [ 
        c_link_args, 
        '-T@0@/@1@'.format(meson.current_source_dir(), linker),
        '-Wl,-Map=@0@.map'.format(name) 
        ],
    include_directories : [ 
        'autosar',
        'autosar/libraries',
        'autosar/mcal',
        'cfg'
    ]
)

# to generate the hex file
hex = custom_target( 'hex',
    output : '@0@.hex'.format(name),
    command : [ 'arm-none-eabi-objcopy', '-O', 'ihex', main, '@OUTPUT@' ],
    depends : main,
    build_by_default : true
)

# just print the mcu memory utilization everytime its build
size = custom_target( 'size',
    output : 'none',
    command : ['arm-none-eabi-size', '--format=berkeley', main],
    depends : main,
    build_by_default : true
)

# generate html documentation like requirements, detail design, api docs, etc..
# $ meson compile -C build docs
run_target(
    'docs',
    command : ['sphinx-build', '-b', 'html', '../docs', 'sphinx', '-c', '../', '-W']
)

# flash the board using openocd
# $ meson compile -C build flash
run_target(
    'flash',
    command : ['openocd', '-f', 'board/st_nucleo_g0.cfg', '-c', 'program @0@.hex verify reset'.format(name), '-c', 'shutdown'],
    depends : hex
)

