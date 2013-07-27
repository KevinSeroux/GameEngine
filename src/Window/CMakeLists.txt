set_option(BUILD_WINDOW_AS "SHARED" STRING "Choose il you want to build Window module as <SHARED> (Default) or <STATIC> library")

if(${BUILD_WINDOW_AS} MATCHES "SHARED")
    set(window_lib_name "Window" CACHE INTERNAL "")
else()
    if(${BUILD_WINDOW_AS} MATCHES "STATIC")
        set(window_lib_name "Window-s" CACHE INTERNAL "")
    else()
        message(FATAL_ERROR "Please choose between SHARED or STATIC (Please respect the case)")
    endif()
endif()

file(
    GLOB
    source_files
    *.h
    *.cpp
    ../../include/GameEngine/Window/*
)

if(WINDOWS)
    file(
        GLOB_RECURSE
        source_files_platform
        Win32/*.h
        Win32/*.cpp
    )
else()
    find_package(X11 REQUIRED)
    if(X11_FOUND)
        file(
            GLOB_RECURSE
            source_files_platform
            X/*.h
            X/*.cpp
        )
    endif()
endif()

add_library(
    ${window_lib_name}
    ${BUILD_COMMON_AS}
    ${source_files}
    ${source_files_platform}
)

if(X11_FOUND)
    include_directories(${X11_INCLUDE_DIRS})
    target_link_libraries(
        ${window_lib_name}
        ${X11_LIBRARIES}
    )
endif()

target_link_libraries(
    ${window_lib_name}
    ${common_lib_name}
    )

set_property(TARGET ${window_lib_name} PROPERTY FOLDER "GameEngine")
