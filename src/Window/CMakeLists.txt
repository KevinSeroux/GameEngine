set_option(BUILD_WINDOW_AS "SHARED" STRING "Choose il you want to build Window module as <SHARED> (Default) or <STATIC> library")

if(${BUILD_WINDOW_AS} MATCHES "SHARED")
    set(window_lib_name "Window" CACHE INTERNAL "")
		add_definitions(-DBUILD_AS_SHARED)
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
    ../../include/GameEngine/Window/*.h
)


if(WIN32)
    file(
        GLOB
        source_files_platform
        ../../include/GameEngine/Window/Win32/*.h
        Win32/*.h
        Win32/*.cpp
    )
	
	set_option(USE_OPENGL TRUE BOOL "Uncheck to use Direct3D instead (not supported for the moment)")
	
	if(${USE_OPENGL} MATCHES "ON")
		find_package(OpenGL REQUIRED)
		if(OPENGL_FOUND)
			file(
				GLOB
				source_files_graphic_api
				../../include/GameEngine/Window/Win32/WGL/*.h
				Win32/WGL/*.h
				Win32/WGL/*.cpp
			)
		else()
			message(FATAL_ERROR "Can't find OpenGL")
		endif()
	endif()
else()
    find_package(X11 REQUIRED)
    if(X11_FOUND)
        file(
            GLOB
            source_files_platform
            ../../include/GameEngine/Window/X/*.h
            X/*.h
            X/*.cpp
        )
		
		find_package(OpenGL REQUIRED)
		if(NOT OPENGL_FOUND)
			message(FATAL_ERROR "Can't find OpenGL")
		endif()
	else()
		message(FATAL_ERROR "Can't find X11")
    endif()
endif()

add_library(
    ${window_lib_name}
    ${BUILD_COMMON_AS}
    ${source_files}
    ${source_files_platform}
	${source_files_graphic_api}
)

if(X11_FOUND)
    include_directories(${X11_INCLUDE_DIRS})
    target_link_libraries(
        ${window_lib_name}
        ${X11_LIBRARIES}
        ${X11_Xinerama_LIB}
    )
endif()

if(OPENGL_FOUND)
	include_directories(${OPENGL_INCLUDE_DIR})
	target_link_libraries(
		${window_lib_name}
		${OPENGL_LIBRARIES}
	)
endif()

target_link_libraries(
    ${window_lib_name}
    ${common_lib_name}
    )

set_property(TARGET ${window_lib_name} PROPERTY FOLDER "GameEngine")
