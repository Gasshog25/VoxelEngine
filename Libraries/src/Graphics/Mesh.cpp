#include "Mesh.h"

Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices, std::vector<GLuint> sizeAttrib)
    : vertices(vertices), indices(indices)
{
    VAO.Bind();
    VBO VBO(this->vertices);
    EBO EBO(this->indices);

    int numComponents = 0;
    for (GLuint i = 0; i < sizeAttrib.size(); i++) {
        numComponents += sizeAttrib[i];
    }

    int offset = 0;
    for (GLuint i = 0; i < sizeAttrib.size(); i++) {
        this->VAO.LinkAttrib(VBO, i, sizeAttrib[i], GL_FLOAT, numComponents * sizeof(GLfloat), (void*)(offset * sizeof(GLfloat)));
        offset += sizeAttrib[i];
    }

    this->VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

Mesh::~Mesh() {
    this->Destroy();
}

void Mesh::Destroy() {
    this->VAO.Destroy();
    this->shader.Destroy();
    for (GLuint i = 0; i < this->textures.size(); i++) {
        this->textures[i].Destroy();
    }
}

void Mesh::AddTexture(Texture texture) { 
    this->textures.push_back(texture);
}

void Mesh::AddTexture(const char* image, const char* name, GLenum format, GLenum pixelType) {
    GLuint slot = this->textures.size();
    this->textures.push_back(Texture(image, name, slot, format, pixelType));
}

void Mesh::Draw(Camera& camera)
{
    this->shader.Activate();
    this->VAO.Bind();
    
    this->InitUniform3f("camPos", glm::value_ptr(camera.GetPosition()));
    camera.Matrix(this->shader, "camMatrix");

    for (GLuint i = 0; i < this->textures.size(); i++) {
        this->textures[i].texUnit(this->shader);
        
        this->textures[i].Bind();
    }

    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    this->VAO.Unbind();
}

void Mesh::InitUniform()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, this->position);
    model = glm::rotate(model, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, this->scale);

    this->InitUniformMatrix4f("model", glm::value_ptr(model));
}
