cmake_minimum_required(VERSION 3.10)
project(MyGameEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenGL 찾기 (모든 플랫폼)
find_package(OpenGL REQUIRED)

# pkg-config 사용 (Linux와 MSYS2 Windows 모두 지원)
find_package(PkgConfig REQUIRED)

# SDL2 찾기
pkg_check_modules(SDL2 REQUIRED sdl2)

# GLEW 찾기
pkg_check_modules(GLEW REQUIRED glew)

# 헤더 파일 경로
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
)

# 링커 경로
link_directories(
    ${SDL2_LIBRARY_DIRS}
    ${GLEW_LIBRARY_DIRS}
)

# 실행 파일
add_executable(game
    src/main.cpp
)

# 플랫폼별 라이브러리 링크
if(WIN32)
    # Windows (MSYS2)
    target_link_libraries(game
        ${SDL2_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        mingw32      # Windows 전용
        SDL2main     # Windows 전용
    )
else()
    # Linux
    target_link_libraries(game
        ${SDL2_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        GL           # Linux OpenGL
        GLU          # Linux OpenGL Utility
    )
endif()

# 빌드 정보 출력
message(STATUS "=== Build Configuration ===")
message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "SDL2 version: ${SDL2_VERSION}")
message(STATUS "SDL2 include: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2 libraries: ${SDL2_LIBRARIES}")
message(STATUS "GLEW version: ${GLEW_VERSION}")