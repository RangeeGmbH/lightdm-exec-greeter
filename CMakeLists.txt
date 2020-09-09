cmake_minimum_required(VERSION 3.10)
project(lightdm-exec-greeter C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB REQUIRED IMPORTED_TARGET glib-2.0)
pkg_check_modules(GOBJECT REQUIRED IMPORTED_TARGET gobject-2.0)
pkg_check_modules(LIGHTDM REQUIRED IMPORTED_TARGET liblightdm-gobject-1)

include_directories(${GLIB_INCLUDE_DIRS} ${GOBJECT_INCLUDE_DIRS} ${LIGHTDM_INCLUDE_DIRS})

add_executable(
        lightdm-exec-greeter
        src/main.c
        src/config.c
        src/execgreeter.c
)

target_link_libraries(
        lightdm-exec-greeter
        PkgConfig::GLIB
        PkgConfig::GOBJECT
        PkgConfig::LIGHTDM
)