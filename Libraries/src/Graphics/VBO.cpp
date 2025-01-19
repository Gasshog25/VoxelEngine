#include "VBO.h"

VBO::VBO(std::vector<GLfloat>& vertices)
{
    glGenBuffers(1, &this->ID);
    glBindBuffer(GL_ARRAY_BUFFER, this->ID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLuint), vertices.data(), GL_STATIC_DRAW);
}

VBO::~VBO()
{
    this->Destroy();
}

void VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}

void VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Destroy()
{
    glDeleteBuffers(1, &this->ID);
}