#include <iostream>

#include "Window.h"
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
{ //	COORDINATES		//
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

	Window window;
	window.Init();

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


	int *w = window.GetWidthptr();
	int *h = window.GetHeightptr();
	Camera cam = Camera(w, h, glm::vec3(0.0f, 0.0f, 2.0f));
	
		
	// Render loop
	while (!window.ShouldClose()) {
		window.NewFrame();
		
		// Render FPS and elapsed time on the window using OpenGL

		std::string title = "fps: " + std::to_string(window.GetFPS()) + 
							", min fps: " + std::to_string(window.GetMinFPS()) +
							", max fps: " + std::to_string(window.GetMaxFPS()) +
							", Avg fps: " + std::to_string(window.GetAverageFPS()) +
							", Elapsed Time: " + std::to_string(window.GetElapseTimeMillisecond()) + "ms" +
							", Avg Elapsed Time: " + std::to_string(window.GetAverageElapseTimeMillisecond()) + "ms";
		glfwSetWindowTitle(window.GetWindow(), title.c_str());

		cam.Inputs(window.GetWindow(), 1.0 / window.GetFPS());
		cam.updateMatrix(75.0f, 0.1f, 1000.0f);

		// Draw Objects
		PilouMesh.Draw(cam);
		lightMesh.Draw(cam);

		

		window.SwapBuffers();
	}


	PilouMesh.Destroy();
	lightMesh.Destroy();

	// Delete window before ending the program
	window.Close();
}