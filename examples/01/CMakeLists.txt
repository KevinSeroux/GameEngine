file(
    GLOB_RECURSE
    source_files
    src/*
)

set(bin_name "01")

add_executable(
    ${bin_name}
    ${source_files}
)

target_link_libraries(
    ${bin_name}
    ${common_lib_name}
)

set_property(TARGET ${bin_name} PROPERTY FOLDER "Examples")