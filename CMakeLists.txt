cmake_minimum_required(VERSION 3.21)
project(terraingen)

set(CMAKE_CXX_STANDARD 17)

# Additional Include Directories
include_directories(Dependencies/GLEW-2.1.0/include)
include_directories(Dependencies/GLFW/include)
include_directories(src/vendor)

# Additional Library Directories
link_directories(Dependencies/GLEW-2.1.0/lib/Release/x64)

if(WIN32)
    message("WIN32")
endif()
if(UNIX)
    message("UNIX")
endif()
if(MSCV)
    message("MSCV")
endif()
message("CMAKE_CXX_COMPILER_ID: " ${CMAKE_CXX_COMPILER_ID})
message("CMAKE_XX_COMPILER_VERSION: " ${CMAKE_CXX_COMPILER_VERSION})

if(MINGW)
    message("Linking lib-mingw-w64 library of GLFW")
    link_directories(Dependencies/GLFW/lib-mingw-w64)
    set(GLFWLIB_CUSTOM_PATH Dependencies/GLFW/lib-mingw-w64)
elseif((MSCV) OR (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC"))
    if(MSVC_TOOLSET_VERSION EQUAL 143)
        message("Detected build for Visual Studio 22")
        link_directories(Dependencies/GLFW/lib-vc2022)
        set(GLFWLIB_CUSTOM_PATH Dependencies/GLFW/lib-vc2022)
    elseif(MSVC_TOOLSET_VERSION EQUAL 142)
        message("Detected build for Visual Studio 19")
        link_directories(Dependencies/GLFW/lib-vc2019)
        set(GLFWLIB_CUSTOM_PATH Dependencies/GLFW/lib-vc2019)
    elseif(MSVC_TOOLSET_VERSION EQUAL 141)
        message("Detected build for Visual Studio 17")
        link_directories(Dependencies/GLFW/lib-vc2017)
        set(GLFWLIB_CUSTOM_PATH Dependencies/GLFW/lib-vc2019)
    else()
        message("The current MSVC_TOOLSET_VERSION is not handled because it has not been tested")
        message("MSVC_VERSION: " ${MSVC_VERSION})
        message("MSVC_TOOLSET_VERSION:" ${MSVC_TOOLSET_VERSION})
        message("Feel free to add it to these if-else chain if you need it")
        message("you may find useful https://cmake.org/cmake/help/latest/variable/MSVC_TOOLSET_VERSION.html#variable:MSVC_TOOLSET_VERSION")
    endif()
endif()
find_library(LIBGLFW3 NAMES libglfw3.a glfw3.lib PATHS ${GLFWLIB_CUSTOM_PATH})

# Preprocessor Definitions
if((MSCV) OR (CMAKE_CXX_COMPILER_ID MATCHES "MSVC"))
    add_compile_definitions(_USE_MATH_DEFINES)
endif()
#add_definitions(GLEW_STATIC WIN32)
#add_definitions(-DGLEW_STATIC)
add_compile_definitions(GLEW_STATIC WIN32)

set(GLFW_FILES
        Dependencies/GLFW/include/GLFW/glfw3.h
        Dependencies/GLFW/include/GLFW/glfw3native.h)
set(GLEW_FILES
        Dependencies/GLEW-2.1.0/include/GL/eglew.h
        Dependencies/GLEW-2.1.0/include/GL/glew.h
        Dependencies/GLEW-2.1.0/include/GL/glxew.h
        Dependencies/GLEW-2.1.0/include/GL/wglew.h)
set(STB_IMAGE_FILES
        src/vendor/stb_image/stb_image.h
        src/vendor/stb_image/stb_image.cpp)
set(IMGUI_FILES
        src/vendor/imgui/imconfig.h
        src/vendor/imgui/imgui.cpp
        src/vendor/imgui/imgui.h
        src/vendor/imgui/imgui_demo.cpp
        src/vendor/imgui/imgui_draw.cpp
        src/vendor/imgui/imgui_impl_glfw.cpp
        src/vendor/imgui/imgui_impl_glfw.h
        src/vendor/imgui/imgui_impl_opengl3.cpp
        src/vendor/imgui/imgui_impl_opengl3.h
        src/vendor/imgui/imgui_impl_opengl3_loader.h
        src/vendor/imgui/imgui_internal.h
        src/vendor/imgui/imgui_tables.cpp
        src/vendor/imgui/imgui_widgets.cpp
        src/vendor/imgui/imstb_rectpack.h
        src/vendor/imgui/imstb_textedit.h
        src/vendor/imgui/imstb_truetype.h
        )
set(PERLIN_NOISE_FILES
        src/vendor/perlin_noise/PerlinNoise.hpp
        )

set(SOURCE_FILES
        src/glerrorhandler.h
        src/indexbuffer.h
        src/renderer.h
        src/shader.h
        src/texture.h
        src/vertexarray.h
        src/vertexbuffer.h
        src/vertexbufferlayout.h
        src/shape.h
        src/camera.h
        src/controler.h
        src/material.h
        src/light.h

        src/glerrorhandler.cpp
        src/indexbuffer.cpp
        src/renderer.cpp
        src/shader.cpp
        src/texture.cpp
        src/vertexarray.cpp
        src/vertexbuffer.cpp
        src/vertexbufferlayout.cpp
        src/shape.cpp
        src/camera.cpp
        src/controler.cpp
        src/material.cpp
        src/light.cpp

        src/Application.cpp
        src/noise.cpp src/noise.h src/color.h src/obj_files.h src/geometry.h)

add_executable(terraingen
        ${SOURCE_FILES}
        ${GLFW_FILES}
        ${GLEW_FILES}
        ${STB_IMAGE_FILES}
        ${IMGUI_FILES}
        ${PERLIN_NOISE_FILES}
        )

# Additional Dependencies
target_link_libraries(terraingen
        glew32s.lib
        ${LIBGLFW3}
        opengl32.lib
        kernel32.lib
        user32.lib
        gdi32.lib
        winspool.lib
        comdlg32.lib
        advapi32.lib
        shell32.lib
        ole32.lib
        oleaut32.lib
        uuid.lib
        odbc32.lib
        odbccp32.lib
        )

# copy resources folder to build directory
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})
