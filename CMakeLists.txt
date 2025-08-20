cmake_minimum_required(VERSION 3.22)
project(BranchFormatter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic)

set(FLTK_SKIP_OPENGL TRUE)
find_package(FLTK REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src)
add_compile_definitions(RESOURCE_DIR="${CMAKE_SOURCE_DIR}")

add_executable(BranchFormatter
        src/main.cpp
        src/app/MainWindow.cpp
        src/core/sanitizer.cpp
)

target_include_directories(BranchFormatter PRIVATE ${FLTK_INCLUDE_DIR})
target_link_libraries(BranchFormatter PRIVATE
        ${FLTK_LIBRARIES}
        fltk_images
)

# Windows: statické linkování pro "single .exe"
if (WIN32)
    target_link_options(BranchFormatter PRIVATE -static -static-libgcc -static-libstdc++)
endif()
