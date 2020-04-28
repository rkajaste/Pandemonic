# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (Pandemonic)

find_package(OpenGL REQUIRED)
find_package(ZLIB)
# Compile external dependencies
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(submodules/glfw)
add_subdirectory(submodules/tmxparser)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(
	src/headers/
	src/common/
	submodules/glad/include/
	submodules/glfw/include/
	submodules/tmxparser/include/
	submodules/glm/
	submodules/stb/
)
# Need to build tinyxml2 manually under tmxparser/third-party, because I do not know how to automate it
# Run 'ldconfig' after building everything
set(ALL_LIBS
	glfw
	tmxparser
	tinyxml2
	ZLIB::ZLIB
	${GLAD_LIBRARIES}
)

file(GLOB VENDORS_SOURCES submodules/glad/src/glad.c)
file(GLOB PROJECT_HEADERS src/*.hpp src/**/*.hpp src/**/**/*.hpp)
file(GLOB PROJECT_SOURCES src/*.cpp src/**/*.cpp src/**/**/*.cpp)
file(GLOB PROJECT_SHADERS shaders/*.glsl)
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