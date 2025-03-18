cmake_minimum_required(VERSION 3.28)
project(Ardelio LANGUAGES CXX)

# Find all .cpp files automatically
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

# Create the library
add_library(ardelio STATIC ${SRC_FILES})

# Specify the include directories
target_include_directories(ardelio PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  # For public headers
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>      # For internal headers
    $<INSTALL_INTERFACE:include>                            # When installed
)

# Set C++ standard
target_compile_features(ardelio PUBLIC cxx_std_17)

# Installation setup
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

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ArdelioTargets
    FILE ArdelioConfig.cmake
    NAMESPACE Ardelio::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Ardelio
)
