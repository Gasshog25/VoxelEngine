#pragma once

#include <glad/glad.h>

class EBO
{
public:
    EBO(GLuint* indices, GLsizeiptr size);
    ~EBO();

    void Bind();
    void Unbind();
    void Delete();

private:
    GLuint ID;
};