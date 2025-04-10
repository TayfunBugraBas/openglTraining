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
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // glfw için temel global deðiþken özelliklerini tanýtmamýz gerekli yoksa gl versiyon vs bulamaz ve çalýþmaz

	GLFWwindow* window = glfwCreateWindow(800, 600, "TEST", NULL, NULL); // ekran objesi GLFW Yükseklik, geniþlik, isim, tam ekran, kaynak paylaþýmý
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // belirtilen içeriði thread'e ekler ve öncekileri iptal eder

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed To Initialize GLAD" << std::endl; // glad'ýn doðru iþletim sistemi ile initialize edildiðinden emin oluyoruz
		return -1;
	}

    glViewport(0,0,800,600); 

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/* 
	openGL'e ekran üzerinde koordinatlarý sýfýrlayabilmesi için bunu yazýyoruz 
	ilk iki paramatre ekranýn sol ALT köþesi için sonraki iki parametre yükselik
	ve geniþlik ayarý için ekran boyutundan küçük verilebilir böylelikle herþey 
	daha küçük ekran içinde gözükür etrafa farklý etmenler koyabiliriz bu þekilde
	*/

	while (!glfwWindowShouldClose(window)) { // herhangi kapatma eylemi gerçekleþtirilmeden ekranýn kapanmasýný önlemek amacýyla bir döngü
		
		processInput(window); // klavye kontrolü :)


		/* alttaki fonksiyondan önce ekranda render olacak herþeyi yaz :D  örn:*/ 
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Red Green Blue Alpha(saydamlýk) tüm ekraný kapsayacak bu rengi yap diyoruz || durumu belirleme fonksiyonu

		glClear(GL_COLOR_BUFFER_BIT); // ekrandaki renkleri temizle atanabilir deðerler GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT || durum kullanma fonksiyonu 


		glfwSwapBuffers(window); // her pixel için renk deðeri içeren ve onlarý deðiþtiren, ekranda render çýktýsý görmemizi saðlayan fonksiyon
		/*
		ekranda birþeyler çizerken tek bir buffer kullanýlýr standart olarak fakat bu durum ekranda glitchlere sebep olabilir anýnda güncellenen görüntüler için
		dolayýsý ile double buffer kullanmak gereklidir
		*/

		glfwPollEvents(); // herhangi bir olay (Event) tetiklenmiþ mi kontrol ediyor klavye girdisi vs.
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) { // kullanýcý ekran boyutunu deðiþtirirse diye ufak bir fonksiyon :)
	glViewport(0, 0, width, height); 
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { // escape'e basýldýðýnda ekraný kapat
		glfwSetWindowShouldClose(window, true);
	}
}