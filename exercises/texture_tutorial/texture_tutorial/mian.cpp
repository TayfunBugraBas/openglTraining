#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shaderss.h"
#include "stb_image.h"

void set_frame_buffer_size_callback(GLFWwindow* windoe, int width, int height) {
	glViewport(0, 0, width, height);
}

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Texturesss", NULL, NULL);

	if (!window) {
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}
	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, set_frame_buffer_size_callback);

	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	// Resimleri 4 farkl� temel �ekilde �a��rabiliyoruz GL_REPEAT , GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER


	unsigned int VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//shader code here
	ShaderClass shader("C:/Users/Bugra/source/repos/texture_tutorial/texture_tutorial/vShader.s", "C:/Users/Bugra/source/repos/texture_tutorial/texture_tutorial/fShader.s");

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	glEnableVertexAttribArray(2);

	unsigned int texture[2];
	

	glGenTextures(2, texture);
	
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//resmi x,y,z i�in s,t,w de�erlerini ayarl�yoruz
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// filtre ayarlar� birder falz afiltre ayar� mevcut GL_LINEAR, GL_NEAREST, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEARES_MIPMAP_LINEAR, GL_LINEAR_MIMAP_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data) {

	
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); // resmi al�yoruz 
		/*
		parametreler s�ras� ile
		resmin boyutlar�n� belirler/

		ikinci parametre resmin mipmap d�zeyini belirler base d�zey 0'd�r

		���nc� parametre resmi ne tipte saklamak istedi�imizi belirtir
		4. ve 5. parametre resmin boyutlar�

		6 PARAMETRE HER ZAMAN 0 OLMALI OpenGl'in eski versiyonlar�ndan kalma bir de�i�ken
	
		7. ve 8. parametre kayna��n veri tipi ve nas�l sakland���n� belirtir
		son parametre de resmin kendisi
		*/
		glGenerateMipmap(GL_TEXTURE_2D); // mipmapler ekrandaki uzak yak�n piksel derinli�i i�in farkl� ��z�n�klerde resimler �retir mipmap kullanaca��m�z her resimden sonra �a��rmam�z gerek
	}
	else {
		std::cout << "Failed To Load Image" << std::endl;
	}
	stbi_image_free(data);
	
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//resmi x,y,z i�in s,t,w de�erlerini ayarl�yoruz
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// filtre ayarlar� birder falz afiltre ayar� mevcut GL_LINEAR, GL_NEAREST, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEARES_MIPMAP_LINEAR, GL_LINEAR_MIMAP_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width2, height2, nrChannels2;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data2 = stbi_load("awesomeface.png", &width2, &height2, &nrChannels2, 0);

	if (data2) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed To Load Image" << std::endl;
	}
	stbi_image_free(data2);

	shader.Use();
	shader.setInteger("texture2", 1);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.4f, 0.6f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
