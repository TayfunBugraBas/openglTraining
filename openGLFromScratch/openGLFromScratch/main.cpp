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
//OpenGl GLSL ynai openGL shading language ile yazýlmýþ kodlardýr
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

	/*
	OpenGL koordinatlarýn renklerini ve onunla ne yapmasý gerrektiðini bilebilmesi için nasýl bir render alacaðýný 
	bilmesi gerekmekte bunlar deðiþkenlerle belirlenmiþ ve primitive denmektedir 3 farklý primitive var 
	GL_POINTS, GL_TRIANGLES, GL_LINE_STRIP
	*/

	//openGL de fragmentler bir pixelin renderlanmasý için gerekli olan bütün bilgidir pixelin rengini falan ayarlar 

	/*
	Modern Opengl'de en az bir vertex ve fragment shaer'i (Programý) belirlemek gerekmektedir.
	*/

	float vertices[] = { // X, Y, Z koordinatlarý için ekranda noktalar belirledik buradaki nokalar ekranda bir üçgen çizmek için yeterlidir.
		 0.5f,0.5f,0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f,-0.5f,0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f,-0.5f,0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f,0.0f , 1.0f, 0.0f, 0.0f,// dikdörtgen için EBO kullanýmýný öðrenmek amaçlý
	};
	unsigned int indices[] = {
		0,1,3, // ilk üçgenin verticesleri yukarýdaki dizideki konumlarý
		1,2,3 // ikinci üçgenin verticesleri
	};
	unsigned int vertex_buffer_objects;
	unsigned int VAO;
	unsigned int EBO; // Element Buffer Object bir nesneyi ovelap eden vertexleri birden fazla kere çizmemek için kullanýlýr
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertex_buffer_objects); // how many buffer, buffer

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_objects);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // burada çaðýrýlan GL_ARRAY_BUFFER aslýnda  vertex_buffer_objects'dir çünkü bir üst satýrda birleþtirilmiþtir.
	
	/*
	static draw yerine 3 farklý kullaným metodu mevcut GL_STREAM_DRAW, veri bir kere set edilir ve GPU'da birkaç kere kullanýlýr.
	GL_STATIC_DRAW data bir kere set edilir ve bir sürü kez kullanýlýr
	GL_DYNAMIC_DRAW data dinamiktir deðiþir ve bir sürü kez GPU'da kullanýlýr 
	*/

	/*
	yapýlan iþlem vertices dizisinde bulunan koordinat deðerlerinin vertex_buffer_objects'e atýlmasý "yukarýdaaa 72-85. satýrlar VAO aþaðýda yazýyor"
	*/

	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER); // buffer oluþturduðumuz gibi shader'i de oluþturmamýz gerekli bu programlar ekran kartý içinde çiplerde çalýþacaklar
 //	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //shader, size, source, length, burada shader  kaynak kodunu vs belirtiyoruz.
	//glCompileShader(vertexShader); // program için yazdýðýmýz kodu çalýþtýrýlabilir hale getiriyoruz

	///* hata yönetimi shader için*/
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
	//tüm shaderlar derlendi ve renderlamaya hazýr bir shader program ile, shader programý tüm shaderlarýn birleþtirilmiþ son halidir.
	//*/
	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();
	///*compile edilmiþ shaderleri baðla*/
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram); // shader programýný baðladýk shaderleri programa ekledikten sonra

	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success) {
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
	//	std::cout << infolog << std::endl;
	//}

	//
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader); // iþi bitin shader'leri GPU'ya gönderdiðimiz için siliyoruz

	Shader ourShader("C:/Users/Bugra/source/repos/openGLFromScratch/openGLFromScratch/vertexShader.vs", "C:/Users/Bugra/source/repos/openGLFromScratch/openGLFromScratch/fragmentShader.fs");

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); /* 
	baþlangýç-- vertex shaderde belirttiðimiz location=0 deðeri ile ayn olmalý çünkü bu deðeri ona göndereceðiz
	, vertex uzunluðu vec3 olduðu için 3 deðer içerir
	, veri tipi
	, normalize veri mi ? 
	, her vertex'in boyutu -- bu her vertex deðerlerinin arasýndaki boþluðu bulmamýz için gerekli
	, void* -- offset (kaydýrma) deðeri þuan 0 olarak ayarlandý */

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	/* þimdi tüm bunlar için 100 tane çizeceðimiz þey olsa 100 kere bunu yapmamýz gerekecek onun yerine konfigürasyonlarý belirteceðimiz bir obje kullanacaðýz -- yukarýya yazýldý */
	glBindVertexArray(0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window)) { // herhangi kapatma eylemi gerçekleþtirilmeden ekranýn kapanmasýný önlemek amacýyla bir döngü
		
		processInput(window); // klavye kontrolü :)


		/* alttaki fonksiyondan önce ekranda render olacak herþeyi yaz :D  örn:*/ 
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Red Green Blue Alpha(saydamlýk) tüm ekraný kapsayacak bu rengi yap diyoruz || durumu belirleme fonksiyonu

		glClear(GL_COLOR_BUFFER_BIT); // ekrandaki renkleri temizle atanabilir deðerler GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT || durum kullanma fonksiyonu 
		ourShader.use(); // oluþturduðumuz shaderleri kullanan ve GPU üzerinde execute edilebilecek olan programý openGL'in kullanmasý için belirtiyoruz
	
		

		//float timeValue = glfwGetTime();
		//float greenValue = sin(timeValue) / 2.0f + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0); // ne çizeceðimiz, hangi vertex'i kullanacaðýmýz, kaç vertices  çizeceðimiz

		glfwSwapBuffers(window); // her pixel için renk deðeri içeren ve onlarý deðiþtiren, ekranda render çýktýsý görmemizi saðlayan fonksiyon
		/*
		ekranda birþeyler çizerken tek bir buffer kullanýlýr standart olarak fakat bu durum ekranda glitchlere sebep olabilir anýnda güncellenen görüntüler için
		dolayýsý ile double buffer kullanmak gereklidir
		*/

		glfwPollEvents(); // herhangi bir olay (Event) tetiklenmiþ mi kontrol ediyor klavye girdisi vs.
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &vertex_buffer_objects);
	glDeleteBuffers(1, &EBO);




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