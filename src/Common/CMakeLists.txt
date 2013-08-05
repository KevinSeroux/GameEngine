set_option(BUILD_COMMON_AS "STATIC" STRING "Choose il you want to build Common module as <STATIC> (Default) or <SHARED> library")

if(${BUILD_COMMON_AS} MATCHES "STATIC")
    set(common_lib_name "Common-s" CACHE INTERNAL "")
else()
    if(${BUILD_COMMON_AS} MATCHES "SHARED")
        set(common_lib_name "Common" CACHE INTERNAL "")
		add_definitions(-DBUILD_AS_SHARED)
    else()
        message(FATAL_ERROR "Please choose between STATIC or SHARED (Please respect the case)")
    endif()
endif()

file(
    GLOB_RECURSE
    source_files
    *.h
    *.cpp
    ../../include/GameEngine/Common/*.h
)

add_library(
    ${common_lib_name}
    ${BUILD_COMMON_AS}
    ${source_files}
)

set_property(TARGET ${common_lib_name} PROPERTY FOLDER "GameEngine")
