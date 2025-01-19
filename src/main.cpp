#include <cmath>
#include <thread>
#include <chrono>

#include "Mesh.h"

// Vertices coordinates
std::vector<GLfloat> vertices =
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
std::vector<GLuint> indices =
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

std::vector<GLfloat> lightVertices =
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

std::vector<GLuint> lightIndices =
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
	
	Mesh PilouMesh(vertices, indices, {3, 2, 3});
	PilouMesh.SetShader("res/shader/default.vert", "res/shader/default.frag");
	PilouMesh.AddTexture("res/img/pilou.jpg", "tex0", GL_RGB, GL_UNSIGNED_BYTE);
	PilouMesh.InitUniform();


	// Light
	Mesh lightMesh(lightVertices, lightIndices, {3});
	lightMesh.SetShader("res/shader/light.vert", "res/shader/light.frag");
	lightMesh.SetPosition(glm::vec3(0.7f, 0.8f, 0.7f));
	lightMesh.SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	lightMesh.InitUniform();

	glm::vec4 lightColor = glm::vec4(0.99f, 0.98f, 1.0f, 1.0f);
	glm::vec4 AmbientLight = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	float AmbientStrength = 0.15f;
	

	PilouMesh.InitUniform4f("lightColor", glm::value_ptr(lightColor));
	PilouMesh.InitUniform4f("AmbientLight", glm::value_ptr(AmbientLight * AmbientStrength));
	PilouMesh.InitUniform3f("lightPos", glm::value_ptr(lightMesh.GetPosition()));

	lightMesh.InitUniform4f("lightColor", glm::value_ptr(lightColor));


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

        // Draw Objects
		PilouMesh.Draw(cam);
		lightMesh.Draw(cam);

        glfwSwapBuffers(window);
		frame++;
        ElapseTime = glfwGetTime() - StartTime;
    }


	PilouMesh.Destroy();
	lightMesh.Destroy();

    // Delete window before ending the program
    glfwDestroyWindow(window);
    glfwTerminate();
}