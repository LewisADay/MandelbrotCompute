
target_sources(${PROJECT_NAME} PUBLIC
	main.cpp
	Renderer/Renderer.cpp
	Mandelbrot/Mandelbrot.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC .)
