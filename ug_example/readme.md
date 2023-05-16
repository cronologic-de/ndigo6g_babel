# File description

## ndigo6g12_example.cpp
Example code to read Ndigo6G-12 6.4 Gsps ADC and TDC data using the ndigo6g12_driver_64.dll.

### Buildld
#### Windows
From directory `ndigo6g_babel`, using `ndigo6g12_driver_64.dll`:
```
clang++.exe .\ug_example\ndigo6g12_example.cpp .\ug_example\ndigo6g12_adc_dual.cpp .\ug_example\ndigo6g12_adc_single.cpp .\ug_example\ndigo6g12_adc_averager.cpp .\ug_example\ndigo6g12_adc_quad.cpp .\ug_example\ndigo6g12_tdc.cpp -l .\lib\ndigo6g12_driver_64.lib -I .\include\ -o ndigo_example.exe
```

#### Ubuntu
From directory `ndigo6g_babel`, using `ndigo6g12_driver.a`:
```
g++ ./ug_example/ndigo6g12_example.cpp ./ug_example/ndigo6g12_adc_dual.cpp ./ug_example/ndigo6g12_adc_single.cpp ./ug_example/ndigo6g12_adc_averager.cpp ./ug_example/ndigo6g12_adc_quad.cpp ./ug_example/ndigo6g12_tdc.cpp -I./include -L./lib -l:ndigo6g12_driver.a -o ndigo6g_example
```
