#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp> 


#include "FPSCounter.h"


struct Parameters
{
    int width;
    int height;
    int majorVersion;
    int minorVersion;
    bool IsDepthEnable;
    
    int maxFPS;
    bool vsync;
    bool fullscreen;

    glm::vec4 clearColor;
};



class Window
{
public:
    Window();
    ~Window();

    int Init();
    void Update();
    void ProcessInput();
    void NewFrame();
    void SwapBuffers();
    
    void Close();

    int GetWidth() { return this->parameters.width; }
    int GetHeight() { return this->parameters.height; }
    int* GetWidthptr() { return &this->parameters.width; }
    int* GetHeightptr() { return &this->parameters.height; }

    void ChangeDepth(bool IsDepthEnable);
    bool IsDepthEnable() { return this->parameters.IsDepthEnable; }

    bool ShouldClose() { return glfwWindowShouldClose(this->window); }
    double GetAspectRatio () { return (double)this->parameters.width / (double)this->parameters.height; }

    GLFWwindow* GetWindow() { return this->window; }

    FPSCounter GetFPSCounter() { return this->fpsCounter; }
    double GetFPS() { return this->fpsCounter.getFPS(); }
    double GetElapseTimeSecond() { return this->fpsCounter.getElapseTimeInSeconds(); }

private:
    GLFWwindow* window;

    Parameters parameters;

    FPSCounter fpsCounter;
};