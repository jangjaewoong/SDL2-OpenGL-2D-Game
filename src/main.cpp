#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include "Shader.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* argv[]) {
    // SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL 초기화 실패: " << SDL_GetError() << std::endl;
        return -1;
    }

    // OpenGL 버전 설정 (3.3 Core Profile)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // 윈도우 생성
    SDL_Window* window = SDL_CreateWindow(
        "My Game Engine - Day 1",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "윈도우 생성 실패: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // OpenGL 컨텍스트 생성
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "OpenGL 컨텍스트 생성 실패: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // GLEW 초기화
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        std::cerr << "GLEW 초기화 실패: " << glewGetErrorString(glewError) << std::endl;
        return -1;
    }

    // VSync 활성화
    SDL_GL_SetSwapInterval(1);
    // 삼각형 정점 (x, y, z)
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  // 왼쪽 아래
         0.5f, -0.5f, 0.0f,  // 오른쪽 아래
         0.0f,  0.5f, 0.0f   // 위쪽
    };
    
    GLuint VBO, VAO;
    
    // VAO 생성 & 바인딩
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    // VBO 생성 & 데이터 업로드
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // 정점 속성 설정
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // 바인딩 해제
    glBindVertexArray(0);

    // 셰이더 생성 (파일 읽기 + 컴파일 + 링크)
    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    // 게임 루프
    bool isRunning = true;
    SDL_Event event;
    
    while (isRunning) {
        // 이벤트 처리
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                }
            }
        }
        
        // ===== 렌더링 =====
        
        // 1. 화면 클리어
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // 2. 셰이더 활성화
        shader.use();
        
        // 3. VAO 바인딩
        glBindVertexArray(VAO);
        
        // 4. 그리기!
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        // 5. 버퍼 스왑 (화면 표시)
        SDL_GL_SwapWindow(window);
    }
    // OpenGL 객체 삭제
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // 정리
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "프로그램 종료" << std::endl;
    return 0;
}