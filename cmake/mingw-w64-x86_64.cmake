# CMake Toolchain file for Windows cross-compilation using MinGW-w64 on macOS

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# MinGW-w64 toolchain location
set(CMAKE_C_COMPILER /opt/homebrew/bin/x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER /opt/homebrew/bin/x86_64-w64-mingw32-g++)

# Where to find the build environment
set(CMAKE_FIND_ROOT_PATH /opt/homebrew/opt/mingw-w64)

# Search for programs only in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Search for libraries and headers only in the target sysroot
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Windows sysroot (if needed)
# set(CMAKE_SYSROOT /path/to/windows/sysroot)

# Don't search for programs in the sysroot
set(CMAKE_DISABLE_FIND_PACKAGE_Qt6 ON)
