cmake_minimum_required(VERSION 2.6)

# Thanks to SFML for this macro
macro(set_option var default type docstring)
if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

project(GameEngine)

set_option(BUILD_EXAMPLES FALSE BOOL "Check if you want to build examples with the library")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include_directories(include)

add_subdirectory(src)

if(${BUILD_EXAMPLES} MATCHES "ON")
	add_subdirectory(examples)
endif()
