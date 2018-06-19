#include <shader.h>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertPath, const char* fragPath) {
    std::string vertCode;
    std::string fragCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // open file
        vShaderFile.open(vertPath);
        fShaderFile.open(fragPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertCode = vShaderStream.str();
        fragCode = fShaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR read shader file error " << e.code().message() << std::endl;
    }

    const char* vShaderCode = vertCode.c_str();
    const char* fShaderCode = fragCode.c_str();
    unsigned int vert, frag;
    int success;
    char infoLog[512];

    vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vShaderCode, NULL);
    glCompileShader(vert);
    glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vert, 512, NULL, infoLog);
        std::cout << "ERROR: Vertex Shader compile failed\n" << infoLog << std::endl;
    }

    frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fShaderCode, NULL);
    glCompileShader(frag);
    glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(frag, 512, NULL, infoLog);
        std::cout << "ERROR: Fragment Shader compile failed\n" << infoLog << std::endl;
    }

    shaderId = glCreateProgram();
    glAttachShader(shaderId, vert);
    glAttachShader(shaderId, frag);
    glLinkProgram(shaderId);
    glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderId, 512, NULL, infoLog);
        std::cout << "ERROR: Link Program failed\n" << infoLog << std::endl;
    }
    glDeleteShader(vert);
    glDeleteShader(frag);
}

void Shader::use() {
    glUseProgram(shaderId);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(shaderId, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(shaderId, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(shaderId, name.c_str()), value);
}
void Shader::setVec3f(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(shaderId, name.c_str()), x, y, z);
}
void Shader::setMat4(const std::string &name, const float* value) const {
    glUniformMatrix4fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE, value);
}
