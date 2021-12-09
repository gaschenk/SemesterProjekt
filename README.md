# SemesterProjekt

This is my semester coding project, which is about creating an application which can create "encryption" using certain chiffres, in this case caesar, and breaking as in cracking those.

## Requirements

* Qt version 6 preferably 6.2
* CMake
* C++/CXX Compiler with C++20 Support
  * Note that it should be possible to even compile it with C++17 or even something as old as C++11, but this isn't tested.
  
## Information in regards to building this project

As I haven't found time yet to make additional changes to the CMakefiles and the underlying buildsystem, the user is required to set `QT_INSTALL_PATH` according to their own environment.
Furthermore it's recommended to run CMake with either Ninja or NMakefiles if you're using MSVC as the compiler/linker.

Please be aware that a symlink from the resource folder to the binary output folder will be created; **IT'S NOT BEING COPIED!**
