#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include <iostream>
#include "shader.h"
#include "Camera.h"

CameraClass Camera(glm::vec3(0.0,0.0,3.0));

float deltaTime = 0.0f;
float lastFrame = 0.0f;
bool firstMouse = true;
float lastX = 800.0 / 2.0;
float lastY = 600.0 / 2.0;

void SFBSCB(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void process_Input(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Camera Class", NULL, NULL);

	if (!window) {
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}
	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, SFBSCB);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//shader class here 
	ShaderClass shader("C:/Users/Bugra/source/repos/CameraClassExercise/CameraClassExercise/VShader.s", "C:/Users/Bugra/source/repos/CameraClassExercise/CameraClassExercise/FShader.s");
	//Camera Class Here


	float vertices[] = {
		// positions               // texture coords
		-0.5f, -0.5f, -0.5f,     0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,     1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f,     0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,     0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f,     0.0f, 0.0f,
		 0.5f, -0.5f, 0.5f,     1.0f, 0.0f,
		 0.5f,  0.5f, 0.5f,     1.0f, 1.0f,
		 0.5f,  0.5f, 0.5f,     1.0f, 1.0f,
		-0.5f,  0.5f, 0.5f,     0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,     0.0f, 0.0f,

		 -0.5f, 0.5f, 0.5f,     1.0f, 0.0f,
		 -0.5f, 0.5f, -0.5f,     1.0f, 1.0f,
		 -0.5f,  -0.5f, -0.5f,     0.0f, 1.0f,
		-0.5f,  -0.5f, -0.5f,     0.0f, 1.0f,
		-0.5f,  -0.5f, 0.5f,     0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,     1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,     1.0f, 0.0f,


		-0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,     1.0f, 1.0f,
		 0.5f, -0.5f, 0.5f,     1.0f, 0.0f,
		 0.5f, -0.5f, 0.5f,     1.0f, 0.0f,
		-0.5f,-0.5f, 0.5f,     0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,     0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f,     0.0f, 1.0f,
		 0.5f, 0.5f, -0.5f,     1.0f, 1.0f,
		 0.5f, 0.5f, 0.5f,     1.0f, 0.0f,
		 0.5f, 0.5f, 0.5f,     1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,     0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,     0.0f, 1.0f,

	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	unsigned int VBO, EBO, VAO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned char* data;
	int W, H, NrC;
	//textures
	unsigned int textures[2];
	glGenTextures(2, textures);
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = stbi_load("container.jpg", &W, &H, &NrC, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "failed to load image" << std::endl;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, textures[1]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = stbi_load("awesomeface.png", &W, &H, &NrC, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "failed to load image" << std::endl;
	}
	stbi_image_free(data);

	glEnable(GL_DEPTH_TEST);

	shader.Use();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(.03f, 0.4f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float CurrentFrame = glfwGetTime();
		deltaTime = CurrentFrame - lastFrame;
		lastFrame = CurrentFrame;

		shader.Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[1]);

		process_Input(window);
		
		glm::mat4 projection = glm::perspective(glm::radians(Camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
		shader.setMatrix4("projection", projection);

		glm::mat4 view = Camera.getViewMatrix();
		shader.setMatrix4("view", view);

		glBindVertexArray(VAO);

		
		
		for (unsigned int i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0);
			
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, glm::radians(45.0f) * (float)glfwGetTime(), glm::vec3(0.2, 0.5, 0.6));
			
			shader.setMatrix4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		glfwSwapBuffers(window);


		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}

void process_Input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window,true);
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Camera.ProcessKeyboard(RIGHT, deltaTime);


}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	Camera.ProcessMouseMovement(xoffset, yoffset);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

	Camera.ProcessMouseScroll(yoffset);

}
