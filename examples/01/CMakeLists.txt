file(
    GLOB_RECURSE
    source_files
    src/*
)

add_executable(
    01
    ${source_files}
)

target_link_libraries(
    01
    ${common_lib_name}
)
