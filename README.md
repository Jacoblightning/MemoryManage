# MemoryManager

[![Documentation Status](https://readthedocs.org/projects/memorymanage/badge/?version=latest)](https://memorymanage.readthedocs.io/en/latest/?badge=latest)

## We (I) recommend you look at the online docs instead. They are much more detailed. You can view them [Here](https://memorymanage.readthedocs.io)
### A C library for easy memory management of other processes. Could be used for process hacking and other fun things.
# Installation
## Another CMake Project (Recommended)
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
## The latest action
### [Nightly.link (Just click here)](https://nightly.link/Jacoblightning/MemoryManager/workflows/cmake-single-platform-release/main)
### Manually (Requires GitHub account)
1. Go to the [Actions Page](https://github.com/Jacoblightning/MemoryManager/actions/workflows/cmake-single-platform-release.yml)
2. Click on the latest action
3. Scroll to Artifacts and choose the one you want.
## GitHut Releases (Not Recommended)
1. Go to [the latest release](https://github.com/Jacoblightning/MemoryManager/releases/latest)
2. Download the one you want.