# MemoryManager
A C library for easy memory management of other processes. Could be used for process hacking and other fun things.
# Installation
## Another CMake Project (Reccomended)
##### Use FetchContent:
```cmake
include(FetchContent)

fetchcontent_declare(
        MemoryManage
        GIT_REPOSITORY https://github.com/Jacoblightning/MemoryManager
        GIT_TAG main
)
fetchcontent_makeavailable(
        MemoryManage
)

target_link_libraries(<Your executable> PRIVATE MemoryManage<Static or Dynamic>)
```
###### Then just include the header:
```c++ // At the very least, IDEA does not accept C as a language here.
#include <MemoryManage/MemoryManage.h>
```
## A normal C or C++ Project
##### Use git and install
```shell
git clone https://github.com/Jacoblightning/MemoryManager
cd MemoryManager
mkdir build
cd build
cmake ..
cmake --build .
sudo cmake --install .
```