#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include <iostream>
#include <string>
#include "shader.h"
#include "Camera.h"

int scr_wdth = 800;
int scr_height = 600;
float lastX = scr_height / 2.0;
float lastY = scr_wdth / 2.0;
bool first_mouse_move = true;
CameraClass camera(glm::vec3(0.0, 0.0, 3.0));
float deltatime = 0.0;
float lastFrame = 0.0;
void SFBSCB(GLFWwindow* wi, int w, int h) {
	glViewport(0, 0, w, h);
}
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
void process_Input(GLFWwindow* window);

void CursorCallBack(GLFWwindow* window, double posx, double posy);

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(scr_wdth, scr_height, "Cameraa", NULL, NULL);

	if (!window) {
		return -1;
	}
	glfwMakeContextCurrent(window);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}
	
	glViewport(0, 0, scr_wdth, scr_height);

	glfwSetFramebufferSizeCallback(window, SFBSCB);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, CursorCallBack);
	//glfwSetScrollCallback  /*daha karar vermedim olsun mu diye*/

	//	ShaderClass Shader("C:/Users/Bugra/source/repos/CameraExerciseee/CameraExerciseee/VShader.s", "C:/Users/Bugra/source/repos/CameraExerciseee/CameraExerciseee/FShader.s");
	ShaderClass lightingShader("C:/Users/Bugra/source/repos/LightiningScene/LightiningScene/basic_lightining.vs", "C:/Users/Bugra/source/repos/LightiningScene/LightiningScene/basic_lightining.fs");
	ShaderClass lightCubeShader("C:/Users/Bugra/source/repos/LightiningScene/LightiningScene/lightining_cube.vs", "C:/Users/Bugra/source/repos/LightiningScene/LightiningScene/lightining_cube.fs");
	
	float vertices[] = {
		  -0.5f, -0.5f, -0.5f,
		   0.5f, -0.5f, -0.5f,
		   0.5f,  0.5f, -0.5f,
		   0.5f,  0.5f, -0.5f,
		  -0.5f,  0.5f, -0.5f,
		  -0.5f, -0.5f, -0.5f,

		  -0.5f, -0.5f,  0.5f,
		   0.5f, -0.5f,  0.5f,
		   0.5f,  0.5f,  0.5f,
		   0.5f,  0.5f,  0.5f,
		  -0.5f,  0.5f,  0.5f,
		  -0.5f, -0.5f,  0.5f,

		  -0.5f,  0.5f,  0.5f,
		  -0.5f,  0.5f, -0.5f,
		  -0.5f, -0.5f, -0.5f,
		  -0.5f, -0.5f, -0.5f,
		  -0.5f, -0.5f,  0.5f,
		  -0.5f,  0.5f,  0.5f,

		   0.5f,  0.5f,  0.5f,
		   0.5f,  0.5f, -0.5f,
		   0.5f, -0.5f, -0.5f,
		   0.5f, -0.5f, -0.5f,
		   0.5f, -0.5f,  0.5f,
		   0.5f,  0.5f,  0.5f,

		  -0.5f, -0.5f, -0.5f,
		   0.5f, -0.5f, -0.5f,
		   0.5f, -0.5f,  0.5f,
		   0.5f, -0.5f,  0.5f,
		  -0.5f, -0.5f,  0.5f,
		  -0.5f, -0.5f, -0.5f,

		  -0.5f,  0.5f, -0.5f,
		   0.5f,  0.5f, -0.5f,
		   0.5f,  0.5f,  0.5f,
		   0.5f,  0.5f,  0.5f,
		  -0.5f,  0.5f,  0.5f,
		  -0.5f,  0.5f, -0.5f,
	};
	//unsigned int indices[] = {
	//	0, 1, 3, // first triangle
	//	1, 2, 3  // second triangle
	//};

	//glm::vec3 cubePositions[] = {
	//	glm::vec3(0.0f,  0.0f,  0.0f),
	//	glm::vec3(2.0f,  5.0f, -15.0f),
	//	glm::vec3(-1.5f, -2.2f, -2.5f),
	//	glm::vec3(-3.8f, -2.0f, -12.3f),
	//	glm::vec3(2.4f, -0.4f, -3.5f),
	//	glm::vec3(-1.7f,  3.0f, -7.5f),
	//	glm::vec3(1.3f, -2.0f, -2.5f),
	//	glm::vec3(1.5f,  2.0f, -2.5f),
	//	glm::vec3(1.5f,  0.2f, -1.5f),
	//	glm::vec3(-1.3f,  1.0f, -1.5f)
	//};


	unsigned int VBO,  VAO; //EBO,

	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	unsigned int  lightVAO;

	glGenVertexArrays(1, &lightVAO);

	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/*unsigned char* data;
	unsigned int textures[2];
	int W, H, NrC;

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
	Shader.Use();
	Shader.setInt("texture1", 0);
	Shader.setInt("texture2", 1);*/

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		// per-frame time logic
 // --------------------
		float currentFrame = static_cast<float>(glfwGetTime());
		deltatime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		process_Input(window);

		// render
		// ------
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// be sure to activate shader when setting uniforms/drawing objects
		lightingShader.Use();
		lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)scr_wdth / (float)scr_height, 0.1f, 100.0f);
		glm::mat4 view = camera.getViewMatrix();
		lightingShader.setMatrix4v("projection", projection);
		lightingShader.setMatrix4v("view", view);

		// world transformation
		glm::mat4 model = glm::mat4(1.0f);
		lightingShader.setMatrix4v("model", model);

		// render the cube
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// also draw the lamp object
		lightCubeShader.Use();
		lightCubeShader.setMatrix4v("projection", projection);
		lightCubeShader.setMatrix4v("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		lightCubeShader.setMatrix4v("model", model);

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}


void process_Input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.Porcess_Keyboard_Input(FORWARD, deltatime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		camera.Porcess_Keyboard_Input(BACKWARD, deltatime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.Porcess_Keyboard_Input(LEFT, deltatime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.Porcess_Keyboard_Input(RIGHT, deltatime);
	}
}

void CursorCallBack(GLFWwindow* window, double posx, double posy) {

	if (first_mouse_move) {
		lastX  = posx;
		lastY = posy ;
		first_mouse_move = false;
	}

	float xOffset = posx - lastX;
	float yOffset = lastY - posy;

	lastX = posx;
	lastY = posy;


	camera.process_mouse_movement(xOffset, yOffset);
}