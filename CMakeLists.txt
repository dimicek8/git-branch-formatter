cmake_minimum_required(VERSION 3.22)
project(BranchFormatter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic)

set(SRC_FILES
        src/main.cpp
        src/app/MainWindow.cpp
        src/core/sanitizer.cpp
)
add_executable(BranchFormatter ${SRC_FILES})

target_include_directories(BranchFormatter PRIVATE ${CMAKE_SOURCE_DIR}/src)

set(FLTK_SKIP_OPENGL TRUE)
find_package(FLTK REQUIRED)
target_include_directories(BranchFormatter PRIVATE ${FLTK_INCLUDE_DIR})
target_link_libraries(BranchFormatter PRIVATE ${FLTK_LIBRARIES})

if (NOT WIN32)
    find_library(FLTK_IMAGES_LIB fltk_images)
    if (FLTK_IMAGES_LIB)
        target_link_libraries(BranchFormatter PRIVATE ${FLTK_IMAGES_LIB})
    endif()
    target_compile_definitions(BranchFormatter PRIVATE RESOURCE_DIR="${CMAKE_SOURCE_DIR}")
endif()

if (WIN32)
    target_link_options(BranchFormatter PRIVATE -static -static-libgcc -static-libstdc++)
    target_compile_definitions(BranchFormatter PRIVATE BF_WINDOWS_STATIC=1)
endif()
