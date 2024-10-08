# Ndigo6G-12 User Guide Example

## About

This directory contains a project to compile the C++ example shows in the user guide of the cronologic Ndigo6G-12 analog-to-digital converter.

You can download the user guide from the [product web page](https://www.cronologic.de/product/ndigo6g-12).

## Directory Structure
```
    .
    ├── include/    # C++ include files from driver
    ├── bin/        # C++ binary files from driver
    ├── lib/        # C++ library files from driver
    └── ug_example/ # source code: .cpp files
        ├── tools/  # files and scripts of the tools, e.g. building tools (CMake, etc...)
        └── build/  # (recommended) compiled output for any OS, configuration, platform
```

---

## Build the Project
- The project is a `Console` App.
- The project is built using `CMake`.
- If you don't have `CMake` installed, please refer to [Installing CMake](https://cmake.org/install/) for instructions. You can check if `CMake` is installed by running `cmake --version`.
- On **Windows**, you can build the project using either `CMake` directly, or using Visual Studio 2019 (or later), see [Build Using `CMake`](#build-using-cmake) or [Build Using Visual Studio](#build-using-visual-studio), respectively.
- On **Linux**, you can build the project using `CMake`, see [Build Using `CMake`](#build-using-cmake).

---

### Build Using Visual Studio

**Prerequisites**
- Visual Studio 2019 or later
- [C++ CMake tools for Windows](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio#installation)

  You can install them from the _Visual Studio Installer_ under 
  _Desktop development with C++_.

**Open and configure the project**
1. Open Visual Studio.
2. Select `Open a local folder`.
3. Select the folder `/ug_example`.
4. If "CMake Integration" message _to enable Visual Studio's CMake support with this workspace_ is displayed
   1. Select `Enable and set source directory` button.
   2. In "Select CMakeLists.txt" Dialog, navigate to the `\ug_example\tools`, and open `CMakeLists.txt`.

**Compile and Link**

Select `Build -> Build All` from menu, or any standard Visual Studio way to build the project.

**Project Environments and Configurations**

| Configuration     | `CMakeSettings` | `Build root`                     | `CMake generator`     | 
| ----------------- | --------------- | -------------------------------- | --------------------- | 
| **x86_64 Debug**  | x64-Debug       | `${projectDir}\..\build\bfvsD`   | Visual Studio 17 2022 Win64 | 
| **x86_64 Release**| x64-Release     | `${projectDir}\..\build\bfvsR`   | Visual Studio 17 2022 Win64 | 

> **Notes**
> * The provided file builds the project using Visual Studio 2022, however, you can change `generator` in [`CMakeSettings.json`](./tools/CMakeSettings.json) to any other Visual Studio generator you have on your machine.
> * The output folder is the same for both release and debug builds.

### Build using `CMake`

In a terminal, navigate to `tools\` and run the following command:

| Platform          | Configuration | Configure CMake command                           | Compile & Link Command                            | 
| ----------------- | ------------- | ----------------------------------------------    | ------------------------------------------------- | 
| **Windows x86_64**| Release       | `cmake -B ..\build\bfR -A x64`                    | `cmake --build ..\build\bfR --config Release`     | 
| **Windows x86_64**| Debug         | `cmake -B ..\build\bfD -A x64`                    | `cmake --build ..\build\bfD --config Debug`       | 
| **Linux x86_64**  | Release       | `cmake -B ../build/bfR -DCMAKE_BUILD_TYPE=Release`| `cmake --build ../build/bfR`                      | 
| **Linux x86_64**  | Debug         | `cmake -B ../build/bfD -DCMAKE_BUILD_TYPE=Debug`  | `cmake --build ../build/bfD`                      | 

> **Notes**
> * The default configuration is `Debug` on Windows, and `Release` on Linux.
> * The output folder is the same for both release and debug builds.
> * You can change the build/output directory from `CMakeLists.txt` file.
> * Linux `x86` is not supported.

---

## Run/Debug the Sample

### Windows
In a terminal, navigate to `/bin` and run the executable. Alternatively, if you are using Visual Studio, you can run/debug the program from within Visual Studio.

### Linux
1. `Cronologic PCI Linux Kernel Module` needs to be installed on your machine. You can build it from [`cronologic_linux_kernel`](https://github.com/cronologic-de/cronologic_linux_kernel) on GitHub.
2. In a terminal, navigate to the `./bin` and run the executable. `sudo` privileges may be necessary.
