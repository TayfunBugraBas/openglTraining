#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;
// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
/*
OpenGl GLSL ynai openGL shading language ile yazýlmýþ kodlardýr
*/

//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.5f, 0.6f, 0.07f, 1.0f);\n"
"}\n\0";

void frame_buffer_size_callback(GLFWwindow* window, int  width, int height);


int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "double fragment shader", NULL, NULL);

	if (window == NULL) {
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}
	int success;
	char infolog[512];

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

	unsigned int vertexShader, fragment1, fragment2;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		return -1;
	}

	fragment1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment1, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragment1);

	glGetShaderiv(fragment1, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragment1, 512, NULL, infolog);
		return -1;
	}

	fragment2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragment2);

	glGetShaderiv(fragment2, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragment2, 512, NULL, infolog);
		return -1;
	}

	unsigned int shaderprog1, shaderprog2;
	shaderprog1 = glCreateProgram();
	glAttachShader(shaderprog1, vertexShader);
	glAttachShader(shaderprog1, fragment1);
	glLinkProgram(shaderprog1);

	glGetProgramiv(shaderprog1,GL_LINK_STATUS,&success);

	if (!success) {
		glGetProgramInfoLog(shaderprog1, 512, NULL, infolog);
		return -1;
	}

	shaderprog2 = glCreateProgram();
	glAttachShader(shaderprog2, vertexShader);
	glAttachShader(shaderprog2, fragment2);
	glLinkProgram(shaderprog2);

	glGetProgramiv(shaderprog2, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shaderprog2, 512, NULL, infolog);
		return -1;
	}



	unsigned int VBO[2], VAO[2];

	float vertices[] = {
		-0.9f,-0.5f,0.0f,
		-0.0f,-0.5f,0.0f,
		-0.45f,0.5f,0.0f,

	};

	float vertices2[] = {
	

		0.0f,-0.5f,0.0f,
		0.9f,-0.5f,0.0f,
		0.45f,0.5f,0.0f,
	};
	glGenBuffers(2, VBO);
	glGenVertexArrays(2, VAO);
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);


	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.5f, 0.3f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderprog1);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderprog2);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void frame_buffer_size_callback(GLFWwindow* window, int  width, int height) {

	glViewport(0, 0, width, height);
}
