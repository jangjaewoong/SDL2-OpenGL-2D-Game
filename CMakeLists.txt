cmake_minimum_required(VERSION 3.10)
project(MyGameEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# OpenGL 찾기
find_package(OpenGL REQUIRED)

# pkg-config 사용
find_package(PkgConfig REQUIRED)

# SDL2 찾기
pkg_check_modules(SDL2 REQUIRED sdl2)

# GLEW 찾기
pkg_check_modules(GLEW REQUIRED glew)

# 헤더 파일 경로 (더 명확하게)
include_directories(
    ${CMAKE_SOURCE_DIR}/src
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
    src/Shader.cpp
)

# include 디렉토리를 타겟에 명시적으로 추가
target_include_directories(game PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${SDL2_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
)

# 플랫폼별 라이브러리 링크
if(WIN32)
    target_link_libraries(game
        ${SDL2_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        mingw32
        SDL2main
    )
else()
    target_link_libraries(game
        ${SDL2_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        GL
        GLU
    )
endif()

# 셰이더 파일 자동 복사
file(COPY ${CMAKE_SOURCE_DIR}/shaders 
     DESTINATION ${CMAKE_BINARY_DIR})