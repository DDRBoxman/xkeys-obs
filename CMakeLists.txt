project(xkeys)

include_directories(hidapi)

set(hidapi_HEADERS
        hidapi/hidapi.h)

if (WIN32)
    set(hidapi_SOURCES
            hidapi/windows/hid.c)
elseif(APPLE)
    set(hidapi_SOURCES
            hidapi/mac/hid.c)
    find_library(IOKIT IOKit)
    include_directories(${IOKIT})
    find_library(COREFOUNDATION CoreFoundation)
    include_directories(${COREFOUNDATION})

    set(hidapi_DEPS
            ${IOKIT}
            ${COREFOUNDATION})
elseif(UNIX)
    set(hidapi_SOURCES
            hidapi/libusb/hid.c)
endif()

set(xkeys_HEADERS
        XKeysDevice.h)

set(xkeys_SOURCES
        plugin-main.cpp
        XKeysDevice.cpp)

add_library(xkeys MODULE
        ${hidapi_SOURCES}
        ${hidapi_HEADERS}
        ${xkeys_SOURCES}
        ${xkeys_HEADERS})

target_link_libraries(xkeys
        ${hidapi_DEPS}
        libobs)

install_obs_plugin_with_data(xkeys data)