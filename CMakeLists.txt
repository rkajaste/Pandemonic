# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (EngineSample)

find_package(OpenGL REQUIRED)

# Compile external dependencies 
add_subdirectory (external)

include_directories(
	external/glfw-3.3.2/include/
	external/glm/
	external/glew-2.1.0/include/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_210
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

add_executable(EngineSample 
	main.cpp
	src/GameState.hpp
	src/Game.cpp
	src/Game.hpp
	src/SpriteRenderer.cpp
	src/SpriteRenderer.hpp
    common/shader.cpp
	common/shader.hpp
	common/texture.cpp
	common/texture.hpp
	common/ResourceManager.cpp
	common/ResourceManager.hpp
    shaders/FragmentShader.glsl
    shaders/VertexShader.glsl
)
target_link_libraries(EngineSample
	${ALL_LIBS}
)