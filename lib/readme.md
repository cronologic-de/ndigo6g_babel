# Overview  
- User mode (library) driver files for both Windows and Linux.
- Files are automatically updated when creating a new driver release.

# Files description

## `ndigo6g12_driver_64.lib`
- Windows linker information for ndigo6g12_driver_64.dll.

## `libndigo6g12_driver.a`
- Linux 64 Bit user mode driver. 
- Requires cronologic GmbH & Co. [Linux Kernel Module for driver version `1.3.0`](https://github.com/cronologic-de/cronologic_linux_kernel/releases) (or above) for device access.
