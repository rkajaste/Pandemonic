# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (Pandemonic)

set(OpenGL_GL_PREFERENCE "GLVND")
set(tinyxml2_DIR "C:/msys64/mingw64/lib")

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIRS})
endif()

# Compile external dependencies
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(FT_WITH_HARFBUZZ "Improve auto-hinting of OpenType fonts." OFF)
add_subdirectory(submodules/glfw)
add_subdirectory(submodules/tmxparser)
add_subdirectory(submodules/freetype2)
set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -mms-bitfields")
    set(CMAKE_CXX_COMPILER  "C:/msys64/mingw64/bin/g++")
    set(CMAKE_CXX_FLAGS "-std=c++1z")
    if(NOT WIN32)
        set(CMAKE_CXX_COMPILER  "/bin/g++")
        set(GLAD_LIBRARIES dl)
    endif()
endif()


include_directories(
    include/
    include/engine/common/
    include/engine/renderers/
    include/engine/camera/
    include/engine/sprite/
    include/engine/managers/
    include/engine/stores/
    include/userInterface/
    include/sprites/
    include/stores/
    external/jsoncpp/
    submodules/glad/include/
    submodules/glfw/include/
    submodules/tmxparser/include/
    submodules/glm/
    submodules/stb/
    submodules/freetype2/include/
)

set(ALL_LIBS
    glfw
    tmxparser
    freetype
    stdc++fs
    ${ZLIB_LIBRARIES}
    ${GLAD_LIBRARIES}
    ${JSONCPP_LIBRARIES}
)

file(GLOB VENDORS_SOURCES submodules/glad/src/glad.c)
file(GLOB PROJECT_HEADERS include/*.hpp include/**/*.hpp)
file(GLOB PROJECT_SOURCES src/*.cpp src/**/*.cpp src/**/**/*.cpp)
file(GLOB PROJECT_SHADERS shaders/**/*.vs shaders/**/*.fs)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          README.md
                         .gitignore
                         .gitmodules)

source_group("headers" FILES ${PROJECT_HEADERS})
source_group("shader" FILES ${PROJECT_SHADERS})
source_group("src" FILES ${PROJECT_SOURCES})
source_group("submodules" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME}
                ${PROJECT_SOURCES}
                ${PROJECT_HEADERS}
                ${PROJECT_SHADERS}
                ${PROJECT_CONFIGS}
                ${VENDORS_SOURCES})

target_link_libraries(${PROJECT_NAME} ${ALL_LIBS})
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})