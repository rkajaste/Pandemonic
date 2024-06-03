# Pandemonic

Clone with submodules

```
git clone --recursive ${REPO_URL}
```

Forgot?

```
git submodule init
git submodule update
```

## Required libraries

### JsonCpp
https://github.com/open-source-parsers/jsoncpp

1. Build library files with python script
```
python amalgamate.py
```
2. Copy paste to `external/jsoncpp`

### Simpleini

https://github.com/brofield/simpleini

2. Copy paste to `external/simpleini`


## Windows pre-requisites

MSYS2 - https://www.msys2.org/

MSYS2 packages

```
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
pacman -S mingw-w64-x86_64-cmake mingw-w64-x86_64-ninja mingw-w64-x86_64-zlib mingw-w64-x86_64-tinyxml2
```

### CMake

https://www.msys2.org/docs/cmake/

```
cmake --build .\build
```
### Run

```
.\build\Pandemonic\Pandemonic.exe
```
