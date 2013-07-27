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