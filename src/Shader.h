#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader {
public:
    GLuint ID;  // 셰이더 프로그램 ID
    
    // 생성자: 셰이더 파일 경로
    Shader(const char* vertexPath, const char* fragmentPath);
    
    // 소멸자
    ~Shader();
    
    // 셰이더 활성화
    void use();
    
private:
    // 컴파일 에러 체크
    void checkCompileErrors(GLuint shader, std::string type);
};

#endif