# File description

## ndigo6g12_averager_example.cpp
Example code to read Ndigo6G-12 Averager data using the driver library.

### Build
#### Windows 
Directory `ndigo6g_babel`, using `ndigo6g12_driver_64.dll`:
```
clang++.exe .\ug_example\ndigo6g12_averager_example.cpp -l .\lib\ndigo6g12_driver_64.lib -I .\include\ -o averager.exe
```
#### Ubuntu
Directory `ndigo6g_babel`, using `ndigo6g12_driver.a`:
```
g++ ./ug_example/ndigo6g12_averager_example.cpp -I./include -L./lib -l:ndigo6g12_driver.a -o averager
```

## ndigo6g12_example.cpp
Example code to read Ndigo6G-12 6.4 Gsps ADC and TDC data using the ndigo6g12_driver_64.dll.

### Build
#### Windows
Directory `ndigo6g_babel`, using `ndigo6g12_driver_64.dll`:
```
clang++.exe .\ug_example\ndigo6g12_example.cpp -l .\lib\ndigo6g12_driver_64.lib -I .\include\ -o ndigo_example.exe
```

#### Ubuntu
Directory `ndigo6g_babel`, using `ndigo6g12_driver.a`:
```
g++ ./ug_example/ndigo6g12_example.cpp -I./include -L./lib -l:ndigo6g12_driver.a -o ndigo6g_example
```
