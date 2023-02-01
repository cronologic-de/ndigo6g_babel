# File description

## ndigo6g12_averager_example.cpp
Example code to read Ndigo6G-12 Averager data using the ndigo6g12_driver_64.dll.

### Build
Directory ndigo6g_babel:
```
clang++.exe .\src\ndigo6g12_averager_example.cpp -l .\lib\ndigo6g12_driver_64.lib -I .\include\ -o averager.exe
```
## ndigo6g12_example.cpp
Example code to read Ndigo6G-12 6.4 Gsps ADC and TDC data using the ndigo6g12_driver_64.dll.

### Build
Directory ndigo6g_babel:
```
clang++.exe .\src\ndigo6g12_example.cpp -l .\lib\ndigo6g12_driver_64.lib -I .\include\ -o ndigo_example.exe
```
