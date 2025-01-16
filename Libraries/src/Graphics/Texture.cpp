#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
    : type(texType), slot(slot), format(format)
{
    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    glGenTextures(1, &this->ID);
    glActiveTexture(slot);
    this->Bind();

    glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(this->type, 0, GL_RGBA, widthImg, heightImg, 0, this->format, pixelType, bytes);
    glGenerateMipmap(this->type);

    stbi_image_free(bytes);
    this->Unbind();
}
Texture::~Texture()
{
    this->Delete();
}

void Texture::texUnit(Shader &shader, const char* uniform, GLuint unit)
{
    shader.Activate();
    glUniform1i(glGetUniformLocation(shader.GetID(), uniform), unit);
    
}

void Texture::Bind()
{
    glBindTexture(this->type, this->ID);
}

void Texture::Unbind()
{
    glBindTexture(this->type, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &this->ID);
}