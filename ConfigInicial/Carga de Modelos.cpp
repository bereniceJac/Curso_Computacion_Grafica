/* Jacinto Robledo Valeria Berenice
* No. de Cuenta: 32005797-3
* Fecha: 13/03/2025
* Practuca 6: Carga de modelos y camara sintetica
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
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );


// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f)); //posicion inicial de la camara, en el origen
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;



int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Jacinto Robledo - Carga de modelos y camara sintetica", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader( "Shader/modelLoading.vs", "Shader/modelLoading.frag" );
    
    // Load models
    Model dog((char*)"Models/dog/RedDog.obj"); //dentro de ese archivo ya se encuentra el RedDog.mtl y dentro de ese está la ruta de mi textura
    Model chair((char*)"Models/chair/Chair.obj");
    Model desk((char*)"Models/desk/metal_table.obj");
    Model pc((char*)"Models/pc/MacBookPro.obj");
    Model notebook((char*)"Models/notebook/Notebook.obj");
    Model folder((char*)"Models/folder/Folder.obj");
    Model lamp((char*)"Models/lamp/Lamp.obj");
    Model tulip((char*)"Models/plant/Plant.obj");
    Model frogCup((char*)"Models/frogCup/Frog_Cup.obj");
    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
  

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
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        //// Draw the loaded model
        //glm::mat4 model(1);
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //dog.Draw(shader);
		
        ////modificaciones del previo para agregar otro modelo del mismo perro pero con diferente tamaño y posición
        //model=glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f)); 
        //model=glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //dog.Draw(shader);


        // Draw the loaded model
        glm::mat4 modelDog = glm::mat4(1.0f);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelDog));
        dog.Draw(shader);

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




        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }

   
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }

 

 
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}