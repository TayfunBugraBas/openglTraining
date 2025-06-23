#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"
#include "shader.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


float W = 800.0;
float H = 600.0;
float deltatime = 0.0;
float lastframe = 0.0;
float lastX = W / 2;
float lastY = H / 2;
bool firstMouseMove = true;
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


void SFBSCB(GLFWwindow* window, int width, int height) {

	glViewport(0, 0, width, height);

}

void ProcessInput(GLFWwindow* window);

void mouseCallback(GLFWwindow* window, double xpos, double ypos);
CameraClass Camera(glm::vec3(0.0, 0.0, 3.0));

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Lightining Exercise", NULL, NULL);

	if (!window) {
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}
	glViewport(0, 0, W, H);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetFramebufferSizeCallback(window, SFBSCB);

	float vertices[] = {
	  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	  -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	  -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	  -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	  -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	   0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	   0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	   0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	   0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	   0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	   0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	   0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	   0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	  -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	   0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	   0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	  -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	// shaders
	ShaderClass shaderCube("cube.vert", "cube.Frag");
	ShaderClass shaderLightSource("lightSource.vert", "lightSource.Frag");


	// vertexes etc.
	unsigned int VBO_cube, VAO_light_cube, VAO;

	glGenBuffers(1, &VBO_cube);

	glGenVertexArrays(1, &VAO);
	

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_cube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//---------------//---------------//

	glGenVertexArrays(1, &VAO_light_cube);
	glBindVertexArray(VAO_light_cube);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_cube);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {

		float currentFrame = glfwGetTime();
		deltatime = currentFrame - lastframe;
		lastframe = currentFrame;

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ProcessInput(window);

		shaderCube.Use();
		shaderCube.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		shaderCube.setVec3("LightSourceColor", 1.0f, 1.0f, 1.0f);
		shaderCube.setVec3fv("LightSourcePos", lightPos);
		shaderCube.setVec3fv("viewPos", Camera.Pos);
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)W / (float)H, 0.1f, 100.0f);
		glm::mat4 view = Camera.getViewMatrix();

		shaderCube.setMatrix4v("projection", projection);
		shaderCube.setMatrix4v("view", view);

		glm::mat4 model = glm::mat4(1.0f);
		shaderCube.setMatrix4v("model", model);


		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);




		shaderLightSource.Use();
		shaderLightSource.setMatrix4v("projection", projection);
		shaderLightSource.setMatrix4v("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		glBindVertexArray(VAO_light_cube);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		shaderLightSource.setMatrix4v("model", model);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}



	glfwTerminate();
	return 0;
}

void ProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
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

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {

	if (firstMouseMove) {
		lastX = xpos;
		lastY = ypos;
		firstMouseMove = false;
	}
	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos;


	lastX = xpos;
	lastY = ypos;
	Camera.process_mouse_movement(xOffset, yOffset);

}