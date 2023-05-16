cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)

include(FetchContent)
project(JIN4 VERSION 1.0.0 LANGUAGES CXX)

if(WIN32)
  # SonarLint support for CMake requires the following flag to be set on.
  #(see https://community.sonarsource.com/t/sonarlint-for-visual-studio-v4-38-support-cmake-projects/50127)
  set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

set (BUILD_SHARED_LIBS FALSE)

set(CMAKE_CXX_STANDARD 20)

FetchContent_Declare(
    pugixml
    GIT_REPOSITORY https://github.com/zeux/pugixml.git
    GIT_TAG v1.10
)

FetchContent_MakeAvailable(pugixml)

add_subdirectory(mainLauncher)
add_subdirectory(src)
# enable_testing() must be in the source directory root (see cmake documentation at https://cmake.org/cmake/help/latest/command/enable_testing.html)
# Otherwise, Visual Studio test explorer does not see unit tests (See ticket https://developercommunity.visualstudio.com/t/No-tests-discovered-for-googletest-and-C/1148799#T-ND1150621)
enable_testing()
add_subdirectory(unitTests)
