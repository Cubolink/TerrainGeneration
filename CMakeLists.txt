cmake_minimum_required(VERSION 3.21)
project(terraingen)

set(CMAKE_CXX_STANDARD 17)

# Additional Include Directories
include_directories(Dependencies/GLEW-2.1.0/include)
include_directories(Dependencies/GLFW/include)
include_directories(src/vendor)

# Additional Library Directories
link_directories(Dependencies/GLEW-2.1.0/lib/Release/Win32)
link_directories(Dependencies/GLFW/lib-mingw-w64)

# Preprocessor Definitions
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

        src/glerrorhandler.cpp
        src/indexbuffer.cpp
        src/renderer.cpp
        src/shader.cpp
        src/texture.cpp
        src/vertexarray.cpp
        src/vertexbuffer.cpp
        src/vertexbufferlayout.cpp
        src/shape.cpp

        src/Application.cpp
        )

add_executable(terraingen
        ${SOURCE_FILES}
        ${GLFW_FILES}
        ${GLEW_FILES}
        ${STB_IMAGE_FILES}
        ${IMGUI_FILES}
        )

# Additional Dependencies
target_link_libraries(terraingen
        glew32s.lib
        libglfw3.a
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
