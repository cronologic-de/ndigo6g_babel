# Ndigo6G-12 User Guide Example

## About

This directory contains a project to compile the C++ example shows in the user guide of the cronologic Ndigo6G-12 analog-to-digital converter.

You can download the user guide from the [product web page](https://www.cronologic.de/product/ndigo6g-12).

## Directory Structure
```
    .
    ├── include/    # C++ include files from driver
    ├── lib/        # C++ library files from driver
    └── ug_example/ # source code: .cpp files
        ├── tools/  # files and scripts of the tools, e.g. building tools (CMake, etc...)
        └── build/  # (recommended) compiled output for any OS, configuration, platform
```

---

## Build the Project

### Overview
- The project is a `Console` App.
- The Project can be mainly built using `CMake`, on both Windows and Linux. 
- `CMake` also can be used on Windows by Microsoft Visual Studio 2019 or later for build and debug, [`CMakeSettings.json`](/ug_example/tools/CMakeSetting.json) is provided to build the project using Visual Studio CMake Tools.

### Prerequisites

##### 1. Install `CMake`
To check if `CMake` is installed, run `cmake --version`; if not installed, please refer to [Installing CMake](https://cmake.org/install/).

### Build Using Visual Studio for Windows
It is mainly done using `CMakeSettings.json` file provided in [`tools` folder](/ug_example/tools/CMakeSettings.json) package, that uses the projects [`CMakeLists.txt`](/ug_example/tools/CMakeLists.tx).

#### Prerequisites
##### 1. Install Development Tools
1. `Visual Studio 2019` or later is installed.
2. In "Visual Studio Installer", under "Desktop development with C++", the option [`C++ CMake tools for Windows`](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio#installation) is installed.

##### Open the Project 
1. Open Visual Studio.
2. Select `Open a local folder`.
3. Select the folder `/ug_example`.
4. If "CMake Integration" message _to enable Visual Studio's CMake support with this workspace_ is displayed
   1. Select `Enable and set source directory` button.
   2. In "Select CMakeLists.txt" Dialog, navigate to the `\ug_example\tools`, and open `CMakeLists.txt`.

##### Compile and Link
Select `Build -> Build All` from menu, or any standard Visual Studio way to build the project.

#### Project Environments and Configurations
The Target Exectuable name is `ndigo6g12_ugex.exe`.
| Configuration     | `CMakeSettings` | `Build root`                     | `CMake generator`     | Output Folder          |
| ----------------- | --------------- | -------------------------------- | --------------------- | ---------------------  |
| **x86_64 Debug**  | x64-Debug       | `${projectDir}\..\build\bfvsD`   | Visual Studio 17 2022 Win64 | `\lib`   |
| **x86_64 Release**| x64-Release     | `${projectDir}\..\build\bfvsR`   | Visual Studio 17 2022 Win64 | `\lib`   |
* The provided file builds the project using `Visual Studio 2022`, however, you can change `generator` in  `CMakeSettings.json` to any other Visual Studio generator you have on your machine.

### Build Using `CMake`, for Windows and Linux

Go to tools: `cd ug_example/tools`, then run the following command:
| Platform          | Configuration | Configur CMake ommand                            | Compile & Link Command                            | Output Folder |
| ----------------- | -------- | -------------------------------------------------     | ------------------------------------------------- | ------ |
| **Windows x86_64**| Release  | `cmake -B ..\build\bfR -A x64`                        | `cmake --build ..\build\bfR --config Release`     | `\lib` |
| **Windows x86_64**| Debug    | `cmake -B ..\build\bfD -A x64`                        | `cmake --build ..\build\bfD --config Debug`       | `\lib` |
| **Linux x86_64**  | Release  | `cmake -B ../build/bfR -DCMAKE_BUILD_TYPE=Release`    | `cmake --build ../build/bfR`                      | `/lib` |
| **Linux x86_64**  | Debug    | `cmake -B ../build/bfD -DCMAKE_BUILD_TYPE=Debug`      | `cmake --build ../build/bfD`                      | `/lib` |

* The default configuration is `Debug` on Windows, and `Release` on Linux.
* Linux x86 is not supported.
* The provided `ndigo6g12_driver.a` is built on Debian.

---

## Run/Debug the Sample

#### Prerequisites
1. Cronologic Kernel Servie/Module is installed:
   - Linux: `Cronologic PCI Linux Kernel Module` is installed on the machine. You can build it from [`cronologic_linux_kernel`](https://github.com/cronologic-de/cronologic_linux_kernel) on github.
   - Windows: `Cronologic Kernel Service` is installed on the machine.
2. Device is installed properly on the machine.

**Steps**
- Run the executable found in the _Output Folder_ from system command

**Notes**
- For Linux: you might need to use `sudo`.
