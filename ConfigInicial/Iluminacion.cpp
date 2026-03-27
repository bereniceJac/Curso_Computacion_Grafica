/* Jacinto Robledo Valeria Berenice
* No. de Cuenta: 32005797-3
* Fecha: 25/03/2025
* Practica 8: Materiales e Iluminacion
/*/

// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"
// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();


// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;


// Light attributes
//glm::vec3 lightPos(0.5f, 0.5f, 2.5f);
//glm::vec3 lightPos2(-2.5f, 1.5f, -1.0f); // segunda luz
//float movelightPos = 0.0f;
//float movelightPos2 = 0.0f; 
float orbitAngle = 0.0f;     // Ángulo de rotación para las luces
float orbitRadius = 3.0f;  //radio de la órbita
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float rot = 0.0f;
bool activanim = false;

int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Jacinto Robledo - Materiales e Iluminacion", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Set the required callback functions
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader shader("Shader/modelLoading.vs", "Shader/modelLoading.frag");
    Shader lampshader("Shader/lamp.vs", "Shader/lamp.frag");
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");



    // Load models
    Model red_dog((char*)"Models/dog/RedDog.obj");
    Model dog_house((char*)"Models/dogHouse/dogHouse.obj");
    Model chair((char*)"Models/chair/Chair.obj");
    Model desk((char*)"Models/desk/metal_table.obj");
    Model pc((char*)"Models/pc/MacBookPro.obj");
    Model notebook((char*)"Models/notebook/Notebook.obj");
    Model folder((char*)"Models/folder/Folder.obj");
    Model lamp((char*)"Models/lamp/Lamp.obj");
    Model tulip((char*)"Models/plant/Plant.obj");
    Model frogCup((char*)"Models/frogCup/Frog_Cup.obj");
    Model sphere((char*)"Models/sphere/sphere.obj");
    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    float vertices[] = {
		//posicion 		 //vector normales
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

    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load textures

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int textureWidth, textureHeight, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

    image = stbi_load("Models/dog/Texture_albedo.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(image);


    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//para el sol
        glm::vec3 dynamicLightPos1 = glm::vec3(
            sin(glm::radians(orbitAngle)) * orbitRadius,
            cos(glm::radians(orbitAngle)) * orbitRadius,
            0.0f
        );

		//para la luna
        glm::vec3 dynamicLightPos2 = glm::vec3(
            sin(glm::radians(orbitAngle + 180.0f)) * orbitRadius,
            cos(glm::radians(orbitAngle + 180.0f)) * orbitRadius,
            0.0f
        );

        lightingShader.Use();
        GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "light.position");
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
       // glUniform3f(lightPosLoc, lightPos.x + movelightPos, lightPos.y + movelightPos, lightPos.z + movelightPos);
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


        // Set lights properties
		// luz 1
        glUniform3f(lightPosLoc, dynamicLightPos1.x, dynamicLightPos1.y, dynamicLightPos1.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), 0.9f, 0.9f, 0.8f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 1.0f, 1.0f, 1.0f);

		// luz 2
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.position"), dynamicLightPos2.x, dynamicLightPos2.y, dynamicLightPos2.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.ambient"), 0.1f, 0.1f, 0.3f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.diffuse"), 0.2f, 0.2f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.specular"), 0.3f, 0.3f, 0.5f);


        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Set material properties
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 0.8f, 0.2f, 0.4f);        
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0.7f, 0.2f, 0.4f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 0.6f, 0.6f, 0.6f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 1.0f);

         



        // Draw the loaded model
        glm::mat4 model(1); //esta es la caja
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        red_dog.Draw(lightingShader);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //modelo de la casita del perro
        glm::mat4 modeldogHouse(1.0f);
        modeldogHouse = glm::translate(modeldogHouse, glm::vec3(-3.0f, -1.2f, -1.5f));
		modeldogHouse = glm::rotate(modeldogHouse, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modeldogHouse = glm::scale(modeldogHouse, glm::vec3(2.0f, 2.0f, 2.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modeldogHouse));
		dog_house.Draw(lightingShader);

        //chair
        glm::mat4 modelChair = glm::mat4(1.0f);
        modelChair = glm::translate(modelChair, glm::vec3(0.0f, -0.9f, 0.0f));
        modelChair = glm::scale(modelChair, glm::vec3(0.03f, 0.03f, 0.03f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelChair));
        chair.Draw(shader);

        //desk
        glm::mat4 modelDesk = glm::mat4(1.0f);
        modelDesk = glm::translate(modelDesk, glm::vec3(0.0f, -0.88f, 0.8f));
        modelDesk = glm::scale(modelDesk, glm::vec3(0.03f, 0.02f, 0.03f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelDesk));
        desk.Draw(shader);

        //pc
        glm::mat4 modelPC = glm::mat4(1.0f);
        modelPC = glm::translate(modelPC, glm::vec3(0.07f, -0.16f, 0.9f));
        modelPC = glm::rotate(modelPC, glm::radians(-135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelPC = glm::scale(modelPC, glm::vec3(0.05f, 0.05f, 0.05f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelPC));
        pc.Draw(shader);

        //notebook
        glm::mat4 modelNotebook = glm::mat4(1.0f); //revisar las texturas de este
        modelNotebook = glm::translate(modelNotebook, glm::vec3(-0.22f, -0.16f, 0.8f));
        modelNotebook = glm::rotate(modelNotebook, glm::radians(-150.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelNotebook));
        notebook.Draw(shader);

        //folder
        glm::mat4 modelFolder = glm::mat4(1.0f);
        modelFolder = glm::translate(modelFolder, glm::vec3(0.3f, -0.15f, 0.8f));
        modelFolder = glm::scale(modelFolder, glm::vec3(0.005f, 0.005f, 0.005f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelFolder));
        folder.Draw(shader);

        //lamp
        glm::mat4 modelLamp = glm::mat4(1.0f);
        modelLamp = glm::translate(modelLamp, glm::vec3(-0.4f, -0.16f, 1.0f));
        modelLamp = glm::rotate(modelLamp, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelLamp = glm::scale(modelLamp, glm::vec3(0.008f, 0.008f, 0.008f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelLamp));
        lamp.Draw(shader);

        //plant
        glm::mat4 modelPlant = glm::mat4(1.0f);
        modelPlant = glm::translate(modelPlant, glm::vec3(-0.6f, -0.17f, 1.2f));
        modelPlant = glm::scale(modelPlant, glm::vec3(0.005f, 0.005f, 0.005f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelPlant));
        tulip.Draw(shader);

        //frogCup
        glm::mat4 modelfrogC = glm::mat4(1.0f);
        modelfrogC = glm::translate(modelfrogC, glm::vec3(-0.3f, -0.17f, 0.6f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelfrogC));
        frogCup.Draw(shader);
        
		//sphere no se ve la fokin sphere, revisar
        /*glm::mat4 modelSphere = glm::mat4(1.0f);
        modelSphere = glm::translate(modelSphere, glm::vec3(0.0f, 1.3f, 0.0f));
        modelSphere = glm::scale(modelSphere, glm::vec3(0.1f, 0.1f, 0.1f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelSphere));
        sphere.Draw(shader);*/

        glBindVertexArray(0);




        lampshader.Use();
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        
        //luz 1
        glm::mat4 modelSun = glm::mat4(1.0f);
        modelSun = glm::translate(modelSun, dynamicLightPos1);
        modelSun = glm::scale(modelSun, glm::vec3(0.1f));
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelSun));
		sphere.Draw(lampshader);


        // dibuja la luz 2
        glm::mat4 modelMoon = glm::mat4(1.0f);
        modelMoon = glm::translate(modelMoon, dynamicLightPos2);
        modelMoon = glm::scale(modelMoon, glm::vec3(0.1f));
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelMoon));
		sphere.Draw(lampshader);


        glBindVertexArray(0);

        // Swap the buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement()
{
    // Camera controls
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (activanim)
    {
        if (rot > -90.0f)
            rot -= 0.1f;
    }

}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }

    /*if (keys[GLFW_KEY_I])
    {
       
        movelightPos += 0.1f;
    }

    if (keys[GLFW_KEY_K])
    {
        
        movelightPos -= 0.1f;
    }

    if (keys[GLFW_KEY_O])
    {

        movelightPos2 += 0.1f;
    }

    if (keys[GLFW_KEY_L])
    {

        movelightPos2 -= 0.1f;
    }*/
    if (keys[GLFW_KEY_O])
    {
        orbitAngle += 1.0f; // Aumenta el ángulo para hacerlos girar
        
        if (orbitAngle > 360.0f) orbitAngle -= 360.0f;
    }
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}


