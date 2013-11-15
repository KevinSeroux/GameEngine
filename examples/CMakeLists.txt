#repeate these two following lines for each examples
set(bin_name "01")
add_subdirectory(${bin_name})

set_property(TARGET ${bin_name} PROPERTY FOLDER "Examples")