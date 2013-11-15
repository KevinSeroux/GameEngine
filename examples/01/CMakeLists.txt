link_directories(${PROJECT_BINARY_DIR}/src/Common/)
link_directories(${PROJECT_BINARY_DIR}/src/Window/)

#If we use the shared version of common, we must define COMMON_SHARED
if(${BUILD_COMMON_AS} MATCHES "SHARED")
	add_definitions(-DCOMMON_SHARED)
endif()

#If we use the shared version of window, we must define WINDOW_SHARED
if(${BUILD_WINDOW_AS} MATCHES "SHARED")
	add_definitions(-DWINDOW_SHARED)
endif()

file(
    GLOB_RECURSE
    source_files
    src/*
)

add_executable(
    ${bin_name}
    ${source_files}
)

target_link_libraries(
    ${bin_name}
    ${common_lib_name}
    ${window_lib_name}
)