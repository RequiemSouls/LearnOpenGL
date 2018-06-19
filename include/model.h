#ifndef MODEL_H
#define MODEL_H

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"

class Model {
 public:
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 color;
    unsigned int vao;

    Shader* shader;
    Mesh* mesh;

    Model(Mesh* mesh, Shader* shader);
    const glm::mat4 GetModelMat();
    void Draw(glm::mat4 projection, Camera* camera);
};

#endif
