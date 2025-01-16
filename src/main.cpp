#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <thread>
#include <chrono>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"

// Vertices coordinates
GLfloat vertices[] =
{
	// Front face
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 	 0.0f,  0.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 	 0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 	 0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 	 0.0f,  0.0f,  1.0f,
	
	// Back face
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 	 0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 	 0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 	 0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 	 0.0f,  0.0f, -1.0f,
	
	// Left face
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 	-1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 	-1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 	-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 	-1.0f,  0.0f,  0.0f,
	
	// Right face
	 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 	 1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 	 1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 	 1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 	 1.0f,  0.0f,  0.0f,
	
	// Top face
	-0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 	 0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 	 0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 	 0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 0.0f, 	 0.0f,  1.0f,  0.0f,
	
	// Bottom face
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 	 0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 	 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 	 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 	 0.0f, -1.0f,  0.0f,
};

// Indices for vertices order
GLuint indices[] =
{
	// Front face
	0, 2, 1, // Upper triangle
	0, 3, 2, // Lower triangle
	
	// Back face
	4, 5, 6, // Upper triangle
	4, 6, 7, // Lower triangle
	
	// Left face
	8, 10, 9, // Upper triangle
	8, 11, 10, // Lower triangle
	
	// Right face
	12, 13, 14, // Upper triangle
	12, 14, 15, // Lower triangle
	
	// Top face
	16, 17, 18, // Upper triangle
	16, 18, 19, // Lower triangle
	
	// Bottom face
	20, 21, 22, // Upper triangle
	20, 22, 23, // Lower triangle
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

int width = 800, height = 800;

int main() {
    // Initialize GLFW
    glfwInit();

    // Tell GLFW what version of OpenGL we want to use
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the core profile (Only the modern functions will be available)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Create a window of size 800x800 and called "OpenGL"
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLAD to load all OpenGL function pointers
    gladLoadGL();

    // Define the viewport dimensions
    glViewport(0, 0, width, height);
    glfwWindowHint(GLFW_REFRESH_RATE, GL_DONT_CARE);
    // glfwSwapInterval(1);
    

	// First Object
    Shader shaderProgram("res/shader/default.vert", "res/shader/default.frag");
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

    Texture Pilou = Texture("res/img/pilou.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    Pilou.texUnit(shaderProgram, "tex0", 0);

	// Light
	Shader lightSahder = Shader("res/shader/light.vert", "res/shader/light.frag");
	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(lightVertices, sizeof(lightVertices));
	EBO EBO2(lightIndices, sizeof(lightIndices));

	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	

	glm::vec3 CubePos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 CubeModel = glm::mat4(1.0f);
	CubeModel = glm::translate(CubeModel, CubePos);

	glm::vec4 lightColor = glm::vec4(0.99f, 0.98f, 1.0f, 1.0f);
	glm::vec4 AmbientLight = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	float AmbientStrength = 0.15f;
	glm::vec3 lightPos = glm::vec3(0.7f, 0.8f, 0.7f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(CubeModel));
	glUniform4fv(glGetUniformLocation(shaderProgram.GetID(), "lightColor"), 1, glm::value_ptr(lightColor));
	glUniform4fv(glGetUniformLocation(shaderProgram.GetID(), "AmbientLight"), 1, glm::value_ptr(AmbientLight * AmbientStrength));
	glUniform3fv(glGetUniformLocation(shaderProgram.GetID(), "lightPos"), 1, glm::value_ptr(lightPos));

	lightSahder.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightSahder.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4fv(glGetUniformLocation(lightSahder.GetID(), "lightColor"), 1, glm::value_ptr(lightColor));



    Camera cam = Camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
    
    float StartTime = glfwGetTime();
    float ElapseTime = 1.0f / 60.0f;
    long int frame = 0;
	
    // Render loop
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
        StartTime = glfwGetTime();
        
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        int frameWidth, frameHeight;
		glfwGetWindowSize(window, &frameWidth, &frameHeight);

		// Check if the window has been resized
		if (frameWidth != width || frameHeight != height) {
			width = frameWidth;
			height = frameHeight;
			glViewport(0, 0, width, height);
			cam.updateResolution(width, height);
		}


        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
        cam.Inputs(window, ElapseTime);
        cam.updateMatrix(75.0f, 0.1f, 1000.0f);


        // Draw our first triangle
        shaderProgram.Activate();
		glUniform3fv(glGetUniformLocation(shaderProgram.GetID(), "camPos"), 1, glm::value_ptr(cam.GetPosition()));
        cam.Matrix(shaderProgram, "camMatrix");
        // Bind every thing
        Pilou.Bind();
        VAO1.Bind();
        // Draw on the screen
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

		lightSahder.Activate();
		cam.Matrix(lightSahder, "camMatrix");
		VAO2.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
		frame++;
        ElapseTime = glfwGetTime() - StartTime;
    }



    VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
    Pilou.Delete();

	shaderProgram.Delete();

    // Delete window before ending the program
    glfwDestroyWindow(window);
    glfwTerminate();
}