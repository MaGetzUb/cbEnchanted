set(EXE_NAME "cbEnchanted.exe")

include(CMakeForceCompiler)

option(OSX_TOOLCHAIN_PATH "/bin")
option(OSX_TOOLCHAIN_PKGS "")

set(CMAKE_SYSTEM_NAME Darwin)
set(CMAKE_C_COMPILER x86_64-apple-darwin15-clang)
set(CMAKE_CXX_COMPILER x86_64-apple-darwin15-clang++-libc++)
set(CMAKE_FIND_ROOT_PATH ${OSX_TOOLCHAIN_PATH} ${OSX_TOOLCHAIN_PKGS})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

include_directories(${OSX_TOOLCHAIN_PATH}/usr/include/c++/v1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

set(CROSS-DARWIN ON)