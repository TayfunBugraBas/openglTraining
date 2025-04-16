#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

void frame_buffer_size_callback(GLFWwindow* window, int width, int height);

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

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "square_and_triangle", NULL, NULL);

	if (window == NULL) {
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}

	glViewport(0, 0, 600, 800);

	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);


	unsigned int vertexShader, fragment1, fragment2;
	int success;
	char infolog[512];

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

	unsigned int shaderProg1, shaderProg2;

	shaderProg1 = glCreateProgram();
	glAttachShader(shaderProg1, vertexShader);
	glAttachShader(shaderProg1, fragment1);
	glLinkProgram(shaderProg1);

	glGetProgramiv(shaderProg1, GL_LINK_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shaderProg1, 512, NULL, infolog);
		return -1;
	}

	glDeleteShader(fragment1);

	shaderProg2 = glCreateProgram();
	glAttachShader(shaderProg2, vertexShader);
	glAttachShader(shaderProg2, fragment2);
	glLinkProgram(shaderProg2);

	glGetProgramiv(shaderProg2, GL_LINK_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shaderProg2, 512, NULL, infolog);
		return -1;
	}

	glDeleteShader(fragment2);
	glDeleteShader(vertexShader);

	float vertices[] = { // X, Y, Z koordinatlarý için ekranda noktalar belirledik buradaki nokalar ekranda bir üçgen çizmek için yeterlidir.
		 0.2f,0.2f,0.0f,
		 0.2f,-0.2f,0.0f,
		-0.2f,-0.2f,0.0f,
		-0.2f, 0.2f,0.0f // dikdörtgen için EBO kullanýmýný öðrenmek amaçlý
	};
	unsigned int indices[] = {
		0,1,3, // ilk üçgenin verticesleri yukarýdaki dizideki konumlarý
		1,2,3 // ikinci üçgenin verticesleri
	};
	float vertices2[] = {


		0.1f,-0.5f,0.0f,
		1.0f,-0.5f,0.0f,
		0.46f,0.5f,0.0f,
	};

	unsigned int VBOs[2], VAOs[2], EBO;

	
	glGenBuffers(2, VBOs);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(2, VAOs);

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.6f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProg1);
		glBindVertexArray(VAOs[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glUseProgram(shaderProg2);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}