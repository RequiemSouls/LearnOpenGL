#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class Texture {
 public:
    unsigned int texId;
    Texture(const char* texPath);
    void use(int index);
};

#endif
