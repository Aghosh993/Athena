# Setup script for Linux

The "setup.sh" script in this directory automatically fetches dependencies for OpenOCD and the OpenOCD source code. It then builds and installs it to your system. It also copies a number of Udev rules to the necessary directory and restarts Udev for them the rules to take effect. You make need to make the script executable with:

```bash
chmod +x setup.sh
```

Then, execute the script as either

```bash
sudo ./setup.sh ARCH_LINUX
```

or

```bash
sudo ./setup.sh UBUNTU_LINUX
```

depending on whether you're running on an Arch or Debian-based distro.