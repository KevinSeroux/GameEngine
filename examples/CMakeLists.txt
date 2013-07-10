link_directories(${PROJECT_BINARY_DIR}/src/Common/)

set(bin_name "01")
add_subdirectory(${bin_name})
set_property(TARGET ${bin_name} PROPERTY FOLDER "Examples")