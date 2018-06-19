#include "glad/glad.h"
#include "mesh.h"

Mesh::Mesh(float* vertices, unsigned int length) {
    this->vertices = vertices;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * length * 6, vertices, GL_STATIC_DRAW);

    this->length = length;
}
