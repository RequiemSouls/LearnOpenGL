#ifndef MESH_H
#define MESH_H

class Mesh {
 public:
    Mesh(float* vertices, unsigned int length);
    unsigned int length;
    unsigned int vbo;
 private:
    float* vertices;
};

#endif
