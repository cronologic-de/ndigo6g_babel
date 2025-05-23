# ndigo6g_babel
Wrappers, Utilities and Examples for using the [Ndigo6G-12](https://www.cronologic.de/products/adcs/ndigo6g-12) with various programming languages.

## License

The code in this repository is licensed under the Mozilla Public License 2.0. In essence, this gives you free access to the code but, upon request, you shall make your changes available to others. Refer to [LICENSE](./LICENSE) for additional details.

We encourage you to contribute to this repository. By uploading to this repository you agree to make your changes available under the before-mentioned license.

## Directory Structure
    .
    ├── images/     # images used in documentation
    ├── include/    # header files required to use the ndigo6g12_driver DLL
    ├── lib/        # ndigo6g12_driver libraries (DLL, .a)
    ├── bin/        # driver binary files
    └── ug_example/ # example applications using the ndigo6g12_driver DLL
        └── tools/  # supporting tools and tool configurations

## Ndigo6G-12 Slot Cover Connections
![Ndigo6G-12 connections](images/Ndigo6G_connections.png)

## Ndigo6G-12 Hardware Installation
![Ndigo6G-12 hardware installation](images/Ndigo6G_periphery.jpg)

Insert the Ndigo6G-12 in a x8 or x16 PCI Express 3.0 slot and attach a 6-pin GPU power cable to the rear connector. The Ndigo6G-12 does not work when the power connector is missing. The Ndigo6G-12 will work in PCIe slots with less than 8 lanes or confirming to PCIe 1.0 or 2.0 albeit at reduced maximum data transfer rates.

## Electrical and Environmental Characteristics
### Analog Inputs
Symbol | Parameter | Min | Typical | Max | Units
--- | --- | --- | --- | --- | ---
V<sub>p-p</sub> | Peak to peak input voltage |  |  | 1000 | mV
Z<sub>p</sub> | Input impedance (AC-coupled) |   | 50 |   | Ω
<nbsp> | Adjustable offset | -500  |   | 500 | mV
    
### Digital Inputs
Symbol | Parameter | Min | Typical | Max | Units
--- | --- | --- | --- | --- | ---
V<sub>p-p</sub> | Peak to peak input voltage |  |  | 1300 | mV
Z<sub>p</sub> | Input impedance (AC-coupled) |   | 50 |   | Ω
<nbsp> | Trigger threshold | -1300  |   | 1300 | mV

### Environment
Symbol | Parameter | Min | Typical | Max | Units
--- | --- | --- | --- | --- | ---    
T | ambient temperature | 5 |   | 40 | °C
RH | relative humidity | 20 |   | 75 | %

### Power Supply
Symbol | Parameter | Min | Typical | Max | Units
--- | --- | --- | --- | --- | ---    
I<sub>3V3</sub> | PCIe 3,3V rail |  | 0.42 |  | W
VCC<sub>3V3</sub> | PCIe 3,3V rail | 3.1 | 3.3 | 3.6 | V
I<sub>12V</sub> | PCIe 12V rail<sup>1</sup> |  | 31 |  | W
VCC<sub>12V</sub> | PCIe 12V rail<sup>1</sup> | 11.1 | 12 | 12.9 | V
I<sub>3V3Aux</sub> | PCIe 3,3VAux rail |  | 0 |  | W
VCC<sub>3V3Aux</sub> | PCIe 3,3VAux rail |  | 3.3 |  | V

<sup>1</sup>The 12V PCIe power is sourced solely from the GPU power connector.

## C/C++ Examples
The example applications can be build _on Windows_ using the [Clang frontend for LLVM](https://clang.llvm.org/index.html). Easy LLVM installation for Windows is provided by the [Chocolatey project](https://chocolatey.org/): [LLVM Chocolatey package](https://community.chocolatey.org/packages/llvm)

The user guide example is provided in [./ug_example](./ug_example/), which reads the Ndigo6G-12 6.4 Gsps ADC and TDC data using the driver library.

Follow the instructions within the directory on how to compile and run the example on Windows or Linux.

>**Note**<br>
>The provided prebuilt Linux libraries are tested on Ubuntu/Debian, and might work for other distributions. If they didn't work with you, please contact the [cronologic support team](https://www.cronologic.de/contact).