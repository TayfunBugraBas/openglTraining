#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <../../shader_s.h>

//// Vertex Shader source code
//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\0";
///*
//OpenGl GLSL ynai openGL shading language ile yaz�lm�� kodlard�r
//*/
//
////Fragment Shader source code
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
//"}\n\0";
/*const char* vertexShaderSource = "#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{"
"    gl_Position = vec4(aPos, 1.0);\n"
"	 vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"	
"}"
;
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"in vec4 vertexColor;\n"
//"void main()\n"
//"{" 
//"	  FragColor = vertexColor;  "
//"}"
//;


*/



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

	/*
	OpenGL koordinatlar�n renklerini ve onunla ne yapmas� gerrekti�ini bilebilmesi i�in nas�l bir render alaca��n� 
	bilmesi gerekmekte bunlar de�i�kenlerle belirlenmi� ve primitive denmektedir 3 farkl� primitive var 
	GL_POINTS, GL_TRIANGLES, GL_LINE_STRIP
	*/

	//openGL de fragmentler bir pixelin renderlanmas� i�in gerekli olan b�t�n bilgidir pixelin rengini falan ayarlar 

	/*
	Modern Opengl'de en az bir vertex ve fragment shaer'i (Program�) belirlemek gerekmektedir.
	*/

	float vertices[] = { // X, Y, Z koordinatlar� i�in ekranda noktalar belirledik buradaki nokalar ekranda bir ��gen �izmek i�in yeterlidir.
		 0.5f,0.5f,0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f,-0.5f,0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f,-0.5f,0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f,0.0f , 1.0f, 0.0f, 0.0f,// dikd�rtgen i�in EBO kullan�m�n� ��renmek ama�l�
	};
	unsigned int indices[] = {
		0,1,3, // ilk ��genin verticesleri yukar�daki dizideki konumlar�
		1,2,3 // ikinci ��genin verticesleri
	};
	unsigned int vertex_buffer_objects;
	unsigned int VAO;
	unsigned int EBO; // Element Buffer Object bir nesneyi ovelap eden vertexleri birden fazla kere �izmemek i�in kullan�l�r
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertex_buffer_objects); // how many buffer, buffer

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_objects);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // burada �a��r�lan GL_ARRAY_BUFFER asl�nda  vertex_buffer_objects'dir ��nk� bir �st sat�rda birle�tirilmi�tir.
	
	/*
	static draw yerine 3 farkl� kullan�m metodu mevcut GL_STREAM_DRAW, veri bir kere set edilir ve GPU'da birka� kere kullan�l�r.
	GL_STATIC_DRAW data bir kere set edilir ve bir s�r� kez kullan�l�r
	GL_DYNAMIC_DRAW data dinamiktir de�i�ir ve bir s�r� kez GPU'da kullan�l�r 
	*/

	/*
	yap�lan i�lem vertices dizisinde bulunan koordinat de�erlerinin vertex_buffer_objects'e at�lmas� "yukar�daaa 72-85. sat�rlar VAO a�a��da yaz�yor"
	*/

	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER); // buffer olu�turdu�umuz gibi shader'i de olu�turmam�z gerekli bu programlar ekran kart� i�inde �iplerde �al��acaklar
 //	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //shader, size, source, length, burada shader  kaynak kodunu vs belirtiyoruz.
	//glCompileShader(vertexShader); // program i�in yazd���m�z kodu �al��t�r�labilir hale getiriyoruz

	///* hata y�netimi shader i�in*/
	//int success;
	//char infolog[512];
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if (!success) {
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
	//	std::cout << infolog << std::endl ;
	//}

	//unsigned int fragmentShader;
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);

	///*
	//t�m shaderlar derlendi ve renderlamaya haz�r bir shader program ile, shader program� t�m shaderlar�n birle�tirilmi� son halidir.
	//*/
	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();
	///*compile edilmi� shaderleri ba�la*/
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram); // shader program�n� ba�lad�k shaderleri programa ekledikten sonra

	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success) {
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
	//	std::cout << infolog << std::endl;
	//}

	//
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader); // i�i bitin shader'leri GPU'ya g�nderdi�imiz i�in siliyoruz

	Shader ourShader("C:/Users/Bugra/source/repos/openGLFromScratch/openGLFromScratch/vertexShader.vs", "C:/Users/Bugra/source/repos/openGLFromScratch/openGLFromScratch/fragmentShader.fs");

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); /* 
	ba�lang��-- vertex shaderde belirtti�imiz location=0 de�eri ile ayn olmal� ��nk� bu de�eri ona g�nderece�iz
	, vertex uzunlu�u vec3 oldu�u i�in 3 de�er i�erir
	, veri tipi
	, normalize veri mi ? 
	, her vertex'in boyutu -- bu her vertex de�erlerinin aras�ndaki bo�lu�u bulmam�z i�in gerekli
	, void* -- offset (kayd�rma) de�eri �uan 0 olarak ayarland� */

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	/* �imdi t�m bunlar i�in 100 tane �izece�imiz �ey olsa 100 kere bunu yapmam�z gerekecek onun yerine konfig�rasyonlar� belirtece�imiz bir obje kullanaca��z -- yukar�ya yaz�ld� */
	glBindVertexArray(0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window)) { // herhangi kapatma eylemi ger�ekle�tirilmeden ekran�n kapanmas�n� �nlemek amac�yla bir d�ng�
		
		processInput(window); // klavye kontrol� :)


		/* alttaki fonksiyondan �nce ekranda render olacak her�eyi yaz :D  �rn:*/ 
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Red Green Blue Alpha(saydaml�k) t�m ekran� kapsayacak bu rengi yap diyoruz || durumu belirleme fonksiyonu

		glClear(GL_COLOR_BUFFER_BIT); // ekrandaki renkleri temizle atanabilir de�erler GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT || durum kullanma fonksiyonu 
		ourShader.use(); // olu�turdu�umuz shaderleri kullanan ve GPU �zerinde execute edilebilecek olan program� openGL'in kullanmas� i�in belirtiyoruz
	
		

		//float timeValue = glfwGetTime();
		//float greenValue = sin(timeValue) / 2.0f + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0); // ne �izece�imiz, hangi vertex'i kullanaca��m�z, ka� vertices  �izece�imiz

		glfwSwapBuffers(window); // her pixel i�in renk de�eri i�eren ve onlar� de�i�tiren, ekranda render ��kt�s� g�rmemizi sa�layan fonksiyon
		/*
		ekranda bir�eyler �izerken tek bir buffer kullan�l�r standart olarak fakat bu durum ekranda glitchlere sebep olabilir an�nda g�ncellenen g�r�nt�ler i�in
		dolay�s� ile double buffer kullanmak gereklidir
		*/

		glfwPollEvents(); // herhangi bir olay (Event) tetiklenmi� mi kontrol ediyor klavye girdisi vs.
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &vertex_buffer_objects);
	glDeleteBuffers(1, &EBO);




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