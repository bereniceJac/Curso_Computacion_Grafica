/* Jacinto Robledo Valeria Berenice
* No. de Cuenta: 32005797-3
* Fecha: 11/02/2025
* Practica 2: Dibujo de primitivas en 2D
/*/
#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas en 2D - Jacinto Robledo Valeria Berenice", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		//colita
		-0.7f,  0.5f, 0.0f,    1.0f,0.5f,1.0f,// 0 E
		-0.9f,  0.3f, 0.0f,    1.0f,0.5f,0.5f,  //1 A
		-0.85f, 0.2f, 0.0f,    0.5f,1.0f,0.0f,  //2 B
		-0.8f,  0.3f, 0.0f,    0.5f,1.0f,1.0f,  //3 C
		-0.68f, 0.4f, 0.0f,    0.4f,0.3f,1.0f,  //4 D
		

		//espalda
		-0.63f,  0.14f, 0.0f,    1.0f,0.2f,0.1f,  //5 G
		-0.53f,  0.54f, 0.0f,    1.0f,0.3f,0.0f,  //6 H
		-0.46f,  0.11f, 0.0f,    1.0f,0.0f,0.2f,  //7 I
		-0.22f,  0.55f, 0.0f,    0.0f,0.2f,0.3f,  //8 J 
		 0.0f,   0.0f,  0.0f,    1.0f,0.0f,0.0f,  //9 A1
		

		//pata
		-0.03f, -0.28f, 0.0f,    0.7f,1.0f,0.0f,  //10 S
		-0.14f, -0.28f, 0.0f,    0.1f,1.0f,0.0f,  //11 T
		-0.27f, -0.28f, 0.0f,    0.2f,1.0f,0.0f,  //12 U
		-0.4f,  -0.36f, 0.0f,    0.8f,1.0f,0.0f,  //23 V
		-0.46f, -0.52f, 0.0f,    0.0f,0.0f,0.2f,  //14 M
		-0.27f, -0.53f, 0.0f,    0.0f,1.0f,0.0f,  //15 W
		-0.12f, -0.44f, 0.0f,    0.0f,1.0f,0.0f,  //16 Z
		-0.87f,  0.06f, 0.0f,    0.5f,1.5f,1.0f,  //17 F
		-0.87f, -0.19f, 0.0f,    1.0f,1.0f,0.5f,  //18 K
		-0.75f, -0.47f, 0.0f,    0.0f,1.0f,0.0f,  //19 L
		-0.59f, -0.32f, 0.0f,    0.2f,1.0f,0.0f,  //20 N
		-0.5f,  -0.19f, 0.0f,    0.0f,0.2f,0.8f,  //21 O
		-0.36f, -0.13f, 0.0f,    0.0f,0.4f,0.5f,  //22 P
		-0.23f, -0.13f, 0.0f,    0.0f,0.6f,0.7f,  //23 Q
		-0.11f, -0.15f, 0.0f,    0.0f,0.8f,0.1f,  //24 R
		
		//brazo
		-0.22f,  0.55f, 0.0f,    0.0f,0.0f,1.0f,  //25 J
		 0.0f,   0.0f,  0.0f,    0.0f,0.0f,1.0f,  //26 A1
		 0.04f, -0.26f, 0.0f,    0.0f,0.0f,1.0f,  //27 E1
		 0.11f, -0.47f, 0.0f,    0.0f,0.0f,1.0f,  //28 D1
		 0.3f,  -0.54f, 0.0f,    0.0f,0.0f,1.0f,  //29 F1
		 0.57f, -0.54f, 0.0f,    0.0f,0.0f,1.0f,  //30 G1
		 0.36f, -0.28f, 0.0f,    0.0f,0.0f,1.0f,  //31 H1
		 0.18f, -0.11f, 0.0f,    0.0f,0.0f,1.0f,  //32 C1
		 0.1f,   0.14f, 0.0f,    0.0f,0.0f,1.0f,  //33 B1

		 
		 
		//oreja
		0.23f,   0.35f,  0.0f,    0.0f,1.0f,1.0f,  //34 V1
		0.29f,   0.43f,  0.0f,    0.0f,1.0f,1.0f,  //35 I1
		0.34f,   0.46f,  0.0f,    0.0f,1.0f,1.0f,  //36 N1
		0.4f,    0.46f,  0.0f,    0.0f,1.0f,1.0f,  //37 O1
		0.46f,   0.42f,  0.0f,    0.0f,1.0f,1.0f,  //38 P1
		0.54f,   0.46f,  0.0f,    0.0f,1.0f,1.0f,  //39 Q1
		0.62f,   0.44f,  0.0f,    0.0f,1.0f,1.0f,  //40 R1
		0.57f,   0.32f,  0.0f,    0.0f,1.0f,1.0f,  //41 J1
		0.44f,   0.37f,  0.0f,    0.0f,1.0f,1.0f,  //42 S1
		0.38f,   0.35f,  0.0f,    0.0f,1.0f,1.0f,  //43 T1
		0.32f,   0.33f,  0.0f,    0.0f,1.0f,1.0f,  //44 U1

		
		//ojo
		0.82f,  -0.1f,   0.0f,    1.0f,1.0f,1.0f,  //45 Z1
		0.75f,  -0.2f,   0.0f,    1.0f,1.0f,1.0f,  //46 A2
		0.64f,  -0.24f,  0.0f,    1.0f,1.0f,1.0f,  //47 B2
		0.6f,   -0.2f,   0.0f,    1.0f,1.0f,1.0f,  //48 C2
		0.56f,  -0.1f,   0.0f,    1.0f,1.0f,1.0f,  //49 W1
		0.73f,   0.05f,  0.0f,    1.0f,1.0f,1.0f,  //50 L1
		
		//nariz
		0.89f,  -0.23f,  0.0f,    0.0f,1.0f,0.7f,  //51 G2
		0.95f,  -0.17f,  0.0f,    1.0f,0.7f,0.0f,  //52 H2
		0.96f,  -0.25f,  0.0f,    0.7f,1.0f,0.0f,  //53 F2


		//Contorno de la cabeza va desde H2- I2
		0.87f,  -0.39f,  0.0f,    1.0f,1.0f,0.0f,  //54 E2
		0.73f,  -0.51f,  0.0f,    1.0f,1.0f,0.0f,  //55 D2
		0.57f,  -0.54f,  0.0f,    1.0f,1.0f,0.0f,  //56 G1
		0.36f,  -0.28f, 0.0f,     1.0f,1.0f,0.0f,  //57 H1
		0.57f,   0.32f,  0.0f,    1.0f,1.0f,0.0f,  //58 J1
		0.8f,    0.2f,  0.0f,     1.0f,1.0f,0.0f,  //59 K1
		0.86f,   0.05f,  0.0f,    1.0f,1.0f,0.0f,  //60 M1
		0.88f,  -0.11f,  0.0f,    1.0f,1.0f,0.0f,  //61 I2

	};
	
	unsigned int indices[] = {  // note that we start from 0!
		2, 17,   17, 5,   17, 18,  7,22,   18,19,    19, 14,
		14,20,   21, 22,  20, 21,  22,23,  23,24,    24, 10,
		25,35,   31, 49,  50, 60,  50,59,

		//contorno de la pata
		17, 18, 19, 14, 20, 21, 22, 7, 5
	};
	
	

	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);


        glPointSize(5);
        glDrawArrays(GL_POINTS,0,61);
        
		glDrawArrays(GL_LINE_LOOP, 0, 5); //colita
		glDrawArrays(GL_LINE_LOOP, 4, 3); //triangulo 1
		glDrawArrays(GL_LINE_LOOP, 5, 3); //triangulo 2
		glDrawArrays(GL_LINE_LOOP, 6, 3); //triangulo 3
		glDrawArrays(GL_LINE_LOOP, 7, 3); //triangulo 4
		glDrawArrays(GL_LINE_LOOP, 10, 7); //parte interna de la pata 
		glDrawElements(GL_LINES, 32, GL_UNSIGNED_INT, 0); //parte externa de la pata, une las líneas en base al indice
		glDrawArrays(GL_LINE_LOOP, 25, 9); //brazo
		glDrawArrays(GL_LINE_LOOP, 34, 11); //oreja
		glDrawArrays(GL_LINE_LOOP, 45, 6); //ojo
		glDrawArrays(GL_LINE_LOOP, 51, 3); //nariz
		glDrawArrays(GL_LINE_LOOP, 52, 10); //contorno de cabeza
		glDrawArrays(GL_LINE_LOOP, 33, 2); //líena que me falta
		
		
		//relleno de color de algunas partes
		glDrawArrays(GL_TRIANGLE_FAN, 0, 5); //colita
		glDrawArrays(GL_TRIANGLE_FAN, 10, 7); //parte interna de la pata
		glDrawArrays(GL_TRIANGLES,51,3); //nariz
		glDrawArrays(GL_TRIANGLE_FAN, 34, 11); //oreja
		glDrawArrays(GL_TRIANGLE_FAN, 45, 6); //ojo


		//glDrawElements(GL_LINE_LOOP, 2, GL_UNSIGNED_INT, 0);// línea que me falta
		
		//glDrawArrays(GL_LINE_LOOP, 5, 7);
        
       
       

        
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}