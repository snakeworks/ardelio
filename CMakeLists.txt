cmake_minimum_required(VERSION 3.28)
project(Ardelio LANGUAGES CXX)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

set(CMAKE_BUILD_TYPE Debug)

add_library(ardelio STATIC ${SRC_FILES})

target_include_directories(ardelio PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  # For public headers
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>      # For internal headers
    $<INSTALL_INTERFACE:include>                            # When installed
)

target_compile_features(ardelio PUBLIC cxx_std_17)

include(GNUInstallDirs)
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)
install(TARGETS ardelio
    EXPORT ArdelioTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_link_libraries(ardelio PRIVATE SFML::Graphics SFML::Audio)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ArdelioTargets
    FILE ArdelioConfig.cmake
    NAMESPACE Ardelio::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Ardelio
)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE ardelio SFML::Graphics SFML::Audio)
