#include "model.h"
#include <iostream>

Model::Model(Mesh* mesh, Shader* shader) : position(glm::vec3(0.0f, 0.0f, 0.0f)), scale(glm::vec3(1.0f, 1.0f, 1.0f)), color(glm::vec3(1.0f, 1.0f, 1.0f)), vao(0) {
    this->mesh = mesh;
    this->shader = shader;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
}

const glm::mat4 Model::GetModelMat() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    return model;
}

void Model::Draw(glm::mat4 projection, Camera* camera) {
    shader->use();
    shader->setInt("ourTexture1", 0);
    shader->setInt("ourTexture2", 1);
    shader->setMat4("projection", &projection[0][0]);
    glm::mat4 view = camera->GetViewMatrix();
    shader->setMat4("view", &view[0][0]);
    shader->setVec3f("color", color.x, color.y, color.z);
    shader->setVec3f("viewPos", camera->position.x, camera->position.y, camera->position.z);
    shader->setVec3f("lightColor", 1.0f, 1.0f, 1.0f);
    shader->setVec3f("lightPos", 3.0f, 0.0f, 2.0f);
    glm::mat4 model = GetModelMat();
    shader->setMat4("model", &model[0][0]);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh->length);
}
