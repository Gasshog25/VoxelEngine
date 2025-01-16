#pragma once

#include <glad/glad.h>

class VBO
{
public:
    VBO(GLfloat* vertices, GLsizeiptr size);
    ~VBO();

    void Bind();
    void Unbind();
    void Delete();

private:
    GLuint ID;
};