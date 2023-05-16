# ndigo6g_babel
Wrappers, Utilities and Examples for using the [Ndigo6G-12](https://www.cronologic.de/products/adcs/ndigo6g-12) with various programming languages.

## License

The code in this repository is licensed under the [Mozilla Public License 2.0](LICENSE). This more or less means that you can do with this code whatever you want, but if you improve the code you shall make your changes available to others upon request. Please read the license for additional details. 

We encourage you to contribute to this repository. By uploading to this repository you agree to make your changes available under the beforementioned license.

## Directory Structure
    .
    ├── images/     # images used in documentation
    ├── include/    # header files required to use the ndigo6g12_driver DLL
    ├── lib/        # ndigo6g12_driver DLL
    ├── ug_example/ # example applications using the ndigo6g12_driver DLL
    └── tools/      # supporting tools and tool configurations

## Ndigo6G-12 Slot Cover Connections
![Ndigo6G-12 connections](images/Ndigo6G_connections.png)

## Ndigo6G-12 Hardware Installation
![Ndigo6G-12 hardware installation](images/ndigo6g12_hw_installation.jpg)

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
I<sub>3V3</sub> | PCIe 3,3V rail |  | tbd |  | mA
VCC<sub>3V3</sub> | PCIe 3,3V rail | 3.1 | 3.3 | 3.6 | V
I<sub>12V</sub> | PCIe 12V rail |  | 2.5 |  | A
VCC<sub>12V</sub> | PCIe 12V rail | 11.1 | 12 | 12.9 | V
I<sub>3V3Aux</sub> | PCIe 3,3VAux rail |  | tbd |  | mA
VCC<sub>3V3Aux</sub> | PCIe 3,3VAux rail |  | 3.3 |  | V


## C/C++ Examples
The example applications can be build _on Windows_ using the [Clang frontend for LLVM](https://clang.llvm.org/index.html). Easy LLVM installation for Windows is provided by the [Chocolatey project](https://chocolatey.org/): [LLVM Chocolatey package](https://community.chocolatey.org/packages/llvm)


### ug_example/ndigo6g12_example.cpp
Example code to read Ndigo6G-12 6.4 Gsps ADC and TDC data using the driver library.
#### Windows
Using `ndigo6g12_driver_64.dll`:
```
clang++.exe .\ug_example\ndigo6g12_example.cpp .\ug_example\ndigo6g12_adc_dual.cpp .\ug_example\ndigo6g12_adc_single.cpp .\ug_example\ndigo6g12_adc_averager.cpp .\ug_example\ndigo6g12_adc_quad.cpp .\ug_example\ndigo6g12_tdc.cpp -l .\lib\ndigo6g12_driver_64.lib -I .\include\ -o ndigo_example.exe
```
#### Ubuntu
Using `ndigo6g12_driver.a`:
```
g++ ./ug_example/ndigo6g12_example.cpp ./ug_example/ndigo6g12_adc_dual.cpp ./ug_example/ndigo6g12_adc_single.cpp ./ug_example/ndigo6g12_adc_averager.cpp ./ug_example/ndigo6g12_adc_quad.cpp ./ug_example/ndigo6g12_tdc.cpp -I./include -L./lib -l:ndigo6g12_driver.a -o ndigo6g_example
```
