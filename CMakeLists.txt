cmake_minimum_required(VERSION 3.12) 

project(Mandelbrotmenge VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED False)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_GENERATOR_PLATFORM}/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_GENERATOR_PLATFORM}/${CMAKE_BUILD_TYPE})

file(GLOB src CONFIGURE_DEPENDS src/*.c src/*.cpp src/*.h src/*.hpp)


set(BUILD_SHARED_LIBS true)
#disable some sfml modules
set(SFML_BUILD_AUDIO false)
set(SFML_BUILD_DOC false)
set(SFML_BUILD_EXAMPLES false)
set(SFML_BUILD_GRAPHICS true)
set(SFML_BUILD_NETWORK false)
set(SFML_BUILD_TEST_SUITE false)
set(SFML_BUILD_WINDOW false)

add_subdirectory(libs/SFML)

add_executable(Mandelbrotmenge ${src})

#copy shader
add_custom_command(TARGET Mandelbrotmenge PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/shader/ $<TARGET_FILE_DIR:Mandelbrotmenge>)
set_property(TARGET Mandelbrotmenge PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:Mandelbrotmenge>)

target_include_directories(Mandelbrotmenge PUBLIC "${CMAKE_SOURCE_DIR}/src" "libs/SFML/include")

target_link_libraries(Mandelbrotmenge PUBLIC sfml-graphics)
