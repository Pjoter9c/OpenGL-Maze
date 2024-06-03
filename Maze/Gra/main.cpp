#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <iostream>

#include "ShaderClass.h"
#include "ObjLoader.h"
#include "Camera.h"
#include "ListOfCollisions.h"
#include "ListOfObjects.h"




void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCREEN_WIDTH = 1200;
const unsigned int SCREEN_HEIGHT = 800;

ShaderClass shader;

ListOfCollisions Walls;


glm::vec3 camPos = glm::vec3(0.0f, 0.25f, -0.3f);
glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);
float camSpeed = 0.1f;
float camAngle = 0.01f;
Camera cam(camPos, camFront, camUp, camSpeed, camAngle);

float ambientVal = 1.;

int main()
{

    //inicjacja biblioteki glfw i utworzenie kontekstu okna
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Przeksztalcenia", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    //wczytanie i kompikacja shaderów
    shader.LoadShader(GL_VERTEX_SHADER, "shader_vs.vert");
    shader.LoadShader(GL_FRAGMENT_SHADER, "shader_fs.frag");
    shader.Create_and_Link();
    shader.Use();
    
    //wczytanie danych z pliku
    ListOfObjects Objects;
    ObjLoader shape;
    shape.LoadObj("labnuv.obj", "PedroCage.jpg");
    Objects.Add(shape);


    ListOfCollisions walls;
    Walls.Create("collisions.obj");

    //wyzerowanie czasu
    glfwSetTime(0);
    glfwSwapInterval(1);

    
    //pêtla gry
    while (!glfwWindowShouldClose(window))
    {
        srand(time(0));
        processInput(window);

        glClearColor(0.6f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();


        float CurrentTime = glfwGetTime();

        glm::mat4 ProjMatrix = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.01f, 100.0f);
        //view matrix
        
        glm::mat4 ViewMatrix = glm::lookAt(cam.getPosition(), cam.getLook(), cam.getUp());

        glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

  
        shader.Set4Mat("u_ProjMatrix", ProjMatrix);
        shader.Set4Mat("u_ViewMatrix", ViewMatrix);
        shader.Set4Mat("u_ModelMatrix", ModelMatrix);
        shader.Set4DVec("TriangleColor", glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
        shader.Set3DVec("CamPos", cam.getPosition());
        shader.SetFloat("ambientValue", ambientVal);
        shader.Use();


        if (cam.getPosition().z < -15.5) {
            do {
                float xPos = rand() % (int)(Walls.getmaxX() - Walls.getminX()) + Walls.getminX();
                float zPos = rand() % (int)(Walls.getmaxZ() - Walls.getminZ()) + Walls.getminZ();
                cam.setPosition(glm::vec3(xPos, cam.getPosition().y, zPos));
            } while (Walls.detectCollision(cam.getPosition()));
            ambientVal = ambientVal/2;
        }
      
        Objects.Draw();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    shape.Delete();
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // MOVE
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        if (Walls.detectCollision(cam.Move(0.0f, 0.0f, -1.0f * cam.getSpeed())) == false) {
            glm::vec3 pos = cam.Move(0.0f, 0.0f, -1.0f * cam.getSpeed());
            cam.setPosition(pos);
        }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        if (Walls.detectCollision(cam.Move(-1.0f * cam.getSpeed(), 0.0f, 0.0f)) == false) {
            glm::vec3 pos = cam.Move(-1.0f * cam.getSpeed(), 0.0f, 0.0f);
            cam.setPosition(pos);
        }
    
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        if (Walls.detectCollision(cam.Move(0.0f, 0.0f, 1.0f * cam.getSpeed())) == false) {
            glm::vec3 pos = cam.Move(0.0f, 0.0f, 1.0f * cam.getSpeed());
            cam.setPosition(pos);
        }
    
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        if (Walls.detectCollision(cam.Move(1.0f * cam.getSpeed(), 0.0f, 0.0f)) == false) {
            glm::vec3 pos = cam.Move(1.0f * cam.getSpeed(), 0.0f, 0.0f);
            cam.setPosition(pos);
        }


    //ROTATE
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        cam.Rotate(glm::vec3(0.0, 1.0, 0.0));

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        cam.Rotate(glm::vec3(0.0, -1.0, 0.0));
 
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}