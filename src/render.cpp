#include <iostream>
#include <render.h>

float vertices[] = {
    -1.0f, -1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f
};
unsigned int indices[] = {0, 1, 2, 1, 2, 3};
const char *vertShaderStr = "#version 330 core\nlayout (location = 0) in vec3 aPos;\n\nvoid main() {\n    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n}";
const char *fragShaderStr = "#version 330 core\nout vec4 FragColor;\n\nvoid main() {\n    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n}";
void Render() {
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void BuildShader() {
    // upload shader
    unsigned int vertShader;
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertShaderStr, NULL);
    glCompileShader(vertShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
        std::cout << "ERROR: Vertex Shader compile failed\n" << infoLog << std::endl;
    }

    unsigned int fragShader;
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragShaderStr, NULL);
    glCompileShader(fragShader);

    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cout << "ERROR: Fragment Shader compile failed\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR: Link Program failed\n" << infoLog << std::endl;
    }
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    glUseProgram(shaderProgram);
}

void UploadData() {
    // upload indices
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    // upload vertices
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}
