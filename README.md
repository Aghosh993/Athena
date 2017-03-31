# Athena Build System

## Intent

This is the Athena build system, which targets a variety of ARM development boards and APIs. It currently supports Windows, Mac OS X and Linux, though any OS with POSIX compatibility and the GNU toolchain should work. Mac and Windows support are currently in process of testing, while the Linux support currently has been tested.

This build system is heavily-based on my prior work in the EL6483_EmbeddedSystems repository on my Github account, which can be viewed at https://github.com/Aghosh993/EL6483_EmbeddedSystems

## Prerequisites

The majority of supported hardware platforms on this repo assume the availability of openocd if you intend to use the "make load" target to flash your board. OpenOCD can be either pre-installed by your package manager, or (preferred) installed via the "setup.sh" script located in "linux_osx/setup_scripts" here. That script fetches a specific version of OpenOCD tested to work the the ST-Link and TM4C Launchpad, and compiles it from source and installs it to your system.

For those using the Segger J-Link, you must have the Segger J-Link driver and GDB package for Linux. Please go on Segger's website and download/extract it to some convenient location. Next, you will need to edit the "JLINK_PATH" variable in your project's Makefile to the appropriate value. Please use the 4.80 version of the package as later versions have somewhat difference CLI syntax and may require modification of the Makefile. I may patch my Makefile to support later J-Link GDB server versions later on when I have tested with a hardware target...

## Quickstart

This repository has a number of submodules it depends on. Please run the following command to fetch all relevant submodules that Athena depends on:

```bash
git submodule update --init --recursive
```
This may take a while so go get a coffee in the meantime...

(c) 2017, Abhimanyu Ghosh