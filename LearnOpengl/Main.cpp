#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const unsigned int HEIGHT = 600, WIDTH = 800;

float vertices[] = {
// first triangle
	-0.9f, -0.5f, 0.0f,  // left 
	-0.0f, -0.5f, 0.0f,  // right
	-0.45f, 0.5f, 0.0f,  // top 
	// second triangle
	0.0f, -0.5f, 0.0f,  // left
	0.9f, -0.5f, 0.0f,  // right
	0.45f, 0.5f, 0.0f   // top 
};
unsigned int indices[] = {  // note that we start from 0!
	2, 0, 1,   // first triangle
	3, 5, 4    // second triangle
//	4, 1, 0,
//	2, 3, 4
};

float firstTriangle[] = {
	-0.9f, -0.5f, 0.0f,  // left 
	-0.0f, -0.5f, 0.0f,  // right
	-0.45f, 0.5f, 0.0f,  // top 
};
float secondTriangle[] = {
	0.0f, -0.5f, 0.0f,  // left
	0.9f, -0.5f, 0.0f,  // right
	0.45f, 0.5f, 0.0f   // top 
};
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";
const char* fragmentShader2Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\0";
// GLFW call this function when user resizes the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
// IF MAC OS UNCOMMENT THE ROW BELLOW
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

// Create window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

// Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

// register the callback functions after we've created the window and before the render loop is initiated.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

// Set opengl viewport, here is where opengl does it magic (-1,1) is scaled to (0,WIDTH),(0,HEIGHT)
	glViewport(0, 0, WIDTH, HEIGHT);


// Vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
// compile vertex shader 
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
// Check shader source is good..
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

// Fragment shader
	unsigned int orangeShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(orangeShader, 1, &fragmentShader1Source, NULL);
	glCompileShader(orangeShader);
	glGetShaderiv(orangeShader, GL_COMPILE_STATUS, &success);

	unsigned int yellowShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(yellowShader, 1, &fragmentShader2Source, NULL);
	glCompileShader(yellowShader);
	glGetShaderiv(yellowShader, GL_COMPILE_STATUS, &success);
	
// Shader program
	unsigned int shaderOrangeProgram = glCreateProgram();
	glAttachShader(shaderOrangeProgram, vertexShader);
	glAttachShader(shaderOrangeProgram, orangeShader);
	glLinkProgram(shaderOrangeProgram);

	unsigned int shaderYellowProgram;
	shaderYellowProgram = glCreateProgram();
	glAttachShader(shaderYellowProgram, vertexShader);
	glAttachShader(shaderYellowProgram, yellowShader);
	glLinkProgram(shaderYellowProgram);

	unsigned int VAOs[2];
	glGenVertexArrays(2, VAOs);

	unsigned int VBOs[2];
	glGenBuffers(2, VBOs);

	// first triangle
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// second triangle
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);


// Element Buffer Objects
	//unsigned int EBO;
//	glGenBuffers(1, &EBO);

//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 3. then set our vertex attributes pointers


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		//render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderYellowProgram);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderOrangeProgram);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

	//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// optional: de-allocate all resources once they've outlived their purpose:
   // ------------------------------------------------------------------------
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glfwTerminate();
	return 0;
}

