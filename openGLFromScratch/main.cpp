#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

int main() {

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // glfw i�in temel global de�i�ken �zelliklerini tan�tmam�z gerekli yoksa gl versiyon vs bulamaz ve �al��maz

	GLFWwindow* window = glfwCreateWindow(800, 600, "TEST", NULL, NULL); // ekran objesi GLFW Y�kseklik, geni�lik, isim, tam ekran, kaynak payla��m�
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // belirtilen i�eri�i thread'e ekler ve �ncekileri iptal eder

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed To Initialize GLAD" << std::endl; // glad'�n do�ru i�letim sistemi ile initialize edildi�inden emin oluyoruz
		return -1;
	}

    glViewport(0,0,800,600); 

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/* 
	openGL'e ekran �zerinde koordinatlar� s�f�rlayabilmesi i�in bunu yaz�yoruz 
	ilk iki paramatre ekran�n sol ALT k��esi i�in sonraki iki parametre y�kselik
	ve geni�lik ayar� i�in ekran boyutundan k���k verilebilir b�ylelikle her�ey 
	daha k���k ekran i�inde g�z�k�r etrafa farkl� etmenler koyabiliriz bu �ekilde
	*/

	while (!glfwWindowShouldClose(window)) { // herhangi kapatma eylemi ger�ekle�tirilmeden ekran�n kapanmas�n� �nlemek amac�yla bir d�ng�
		
		processInput(window); // klavye kontrol� :)


		/* alttaki fonksiyondan �nce ekranda render olacak her�eyi yaz :D  �rn:*/ 
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Red Green Blue Alpha(saydaml�k) t�m ekran� kapsayacak bu rengi yap diyoruz || durumu belirleme fonksiyonu

		glClear(GL_COLOR_BUFFER_BIT); // ekrandaki renkleri temizle atanabilir de�erler GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT || durum kullanma fonksiyonu 


		glfwSwapBuffers(window); // her pixel i�in renk de�eri i�eren ve onlar� de�i�tiren, ekranda render ��kt�s� g�rmemizi sa�layan fonksiyon
		/*
		ekranda bir�eyler �izerken tek bir buffer kullan�l�r standart olarak fakat bu durum ekranda glitchlere sebep olabilir an�nda g�ncellenen g�r�nt�ler i�in
		dolay�s� ile double buffer kullanmak gereklidir
		*/

		glfwPollEvents(); // herhangi bir olay (Event) tetiklenmi� mi kontrol ediyor klavye girdisi vs.
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) { // kullan�c� ekran boyutunu de�i�tirirse diye ufak bir fonksiyon :)
	glViewport(0, 0, width, height); 
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { // escape'e bas�ld���nda ekran� kapat
		glfwSetWindowShouldClose(window, true);
	}
}