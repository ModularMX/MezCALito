MezCALito
=========


This is simply an AUTOSAR implementation with no other objective than to create something functional enough to be used for academic purposes and possibly something else.

We have chosen to develop this project using the STM32G0xx microcontroller as a starting point, due to its simple architecture and widespread availability. All code is being written from scratch to avoid any license compliance issues with third-party software.

The language of choice for development is Python, as we plan to create a configuration generator based on a command-line approach, with the possibility of creating a GUI later on.

Deviations:
-------

Our aim is to stick as closely as possible to the official standard, but some liberties will be taken for the sake of our mental well-being. For example, we plan to replace the XML file with YAML in order to enhance human readability and delay the implementation of the GUI for software unit configuration. However, the architecture will be modular enough for someone to add XML support and an Eclipse IDE, just not us.

To-Do List:
-----

- Split the project into multiple repositories, as this is definitely something that must be done. For now, we will start with one repository.
- Add support for various architectures and compilers.


Tools
-----

**Build system**

-[meson](https://github.com/mesonbuild/meson), [ninja](https://github.com/ninja-build/ninja)


```bash
sudo pacman -S make
python -m pip install meson
python -m pip install ninja
```

**Compiler**

```bash
sudo pacman -S arm-none-eabi-gcc
```
