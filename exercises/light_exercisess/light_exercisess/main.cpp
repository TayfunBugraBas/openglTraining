#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
#include "stb_image.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


int scrW = 800;
int scrH = 600;
CameraClass Camera(glm::vec3(0.0, 0.0, 3.0));
float deltatime = 0.0;
float lastframe = 0.0;
float LastX = float(scrW) / 2.0;
float LastY = float(scrH) / 2.0;
bool firstMouseMove = true;



void SFBSCB(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void CursorCallback(GLFWwindow* window, double xpos, double ypos);

void ProcessInput(GLFWwindow* window);

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(scrW, scrH, "exercises", NULL, NULL);

	if (!window) {
		return -1;
	}
	glfwMakeContextCurrent(window);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;

	}

	glViewport(0, 0, scrW, scrH);

	glfwSetFramebufferSizeCallback(window, SFBSCB);
	glfwSetCursorPosCallback(window, CursorCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	float vertices[] = {
	  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	   0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	   0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	   0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	  -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	   0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	   0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	   0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	  -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	  -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	  -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	   0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	   0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	   0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	   0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	   0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	   0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	   0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	   0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	   0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	  -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	   0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	   0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	   0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	  -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	unsigned int VAO_cube, VBO, VAO_light_source;

	glGenBuffers(1,&VBO);
	glGenVertexArrays(1, &VAO_cube);

	glBindVertexArray(VAO_cube);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glGenVertexArrays(1, &VAO_light_source);

	glBindVertexArray(VAO_light_source);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glEnable(GL_DEPTH_TEST);

	ShaderClass CubeShader("cube.vert", "cube.frag");
	ShaderClass lightShader("lightSource.vert", "lightSource.frag");

	int W, H, NrC;
	unsigned int texture;
	unsigned char* data;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);

	data = stbi_load("container.jpg", &W, &H, &NrC, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

	}
	else {
		std::cout << "Failed To Load Image" << std::endl;
	}
	stbi_image_free(data);
	CubeShader.Use();
	
	CubeShader.setInt("texture1", 0);


	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.1, 0.1, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
		float currentFrame = glfwGetTime();
		deltatime = currentFrame - lastframe;
		lastframe = currentFrame;
		glm::vec3 lightPos(cos(glfwGetTime()) * 2 , sin(glfwGetTime()) * 2, sin(glfwGetTime()) * 2);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glm::mat4 projection = glm::perspective(45.0f, float(scrW / scrH), 0.1f, 100.f);

		ProcessInput(window);

		CubeShader.Use();
		glm::mat4 view = Camera.getViewMatrix();
		CubeShader.setVec3fv("lightPos", lightPos);
		CubeShader.setVec3fv("viewPos", Camera.Pos);

		CubeShader.setMatrix4v("view", view);
		CubeShader.setMatrix4v("projection", projection);
		
		glm::mat4 model = glm::mat4(1.0);
		CubeShader.setMatrix4v("model", model);
		
		CubeShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

		glBindVertexArray(VAO_cube);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		lightShader.Use();
		lightShader.setMatrix4v("view", view);
		lightShader.setMatrix4v("projection", projection);
		model = glm::mat4(1.0);
		

		glBindVertexArray(VAO_light_source);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::translate(model, lightPos);
		lightShader.setMatrix4v("model", model);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();
	return 0;
}

void CursorCallback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouseMove) {
		LastX = xpos;
		LastY = ypos;
		firstMouseMove = false;
	}
	float xOffset = xpos - LastX;
	float yOffset = LastY - ypos;


	LastX = xpos;
	LastY = ypos;
	Camera.process_mouse_movement(xOffset, yOffset);
}

void ProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Camera.Porcess_Keyboard_Input(FORWARD, deltatime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Camera.Porcess_Keyboard_Input(BACKWARD, deltatime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Camera.Porcess_Keyboard_Input(LEFT, deltatime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Camera.Porcess_Keyboard_Input(RIGHT, deltatime);
	}
}