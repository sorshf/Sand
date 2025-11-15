cmake_minimum_required(VERSION 3.10)
project(Sand VERSION 1.0 LANGUAGES CXX)

# Set C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Switch between a system sdl library and FetchContent
option(FETCH_SDL3 "Download SDL3" ON)

if(FETCH_SDL3)
    # Use FetchContent to download SDL3
    include(FetchContent)
    
    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.2.26
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
    
    # Optional: Set SDL3 options before making it available
    set(SDL_SHARED ON CACHE BOOL "" FORCE)
    set(SDL_STATIC OFF CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(SDL3)
else()
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
endif()

# Sources
set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/InputHandler.cpp
    ${PROJECT_SOURCE_DIR}/src/Game.cpp
    ${PROJECT_SOURCE_DIR}/src/Material.cpp
    ${PROJECT_SOURCE_DIR}/src/World.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Link SDL3
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

# For IDEs: make source groups by folders
source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES})