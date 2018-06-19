#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>

class Shader {
 public:
    unsigned int shaderId;
    Shader(const char* vertPath, const char* fragPath);
    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec3f(const std::string &name, float x, float y, float z) const;
    void setMat4(const std::string &name, const float* value) const;
};

#endif
