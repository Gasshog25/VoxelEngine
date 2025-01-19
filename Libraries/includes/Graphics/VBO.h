#pragma once

#include <glad/glad.h>
#include <vector>

class VBO
{
public:
    VBO(std::vector<GLfloat>& vertices);
    ~VBO();

    void Bind();
    void Unbind();
    void Destroy();

private:
    GLuint ID;
};