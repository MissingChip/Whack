
#include <stdio.h>
#include "gl.h"

#include "vertex_group.h"
#include "shader.h"

int main(){
    /* Initialize the library */
    if (!glfwInit()){
        printf("GLFW init error\n");
        return -1;
    }
    GLFWwindow* window;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    //glfwWindowHint( GLFW_SAMPLES, 4);
    //glEnable(GL_MULTISAMPLE);
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!window)
    {
        printf("Window creation failed\n");
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent( window );
    if( glewInit() != GLEW_OK ){
        printf("GLEW init error\n");
    }
    float vertices[] = {
        // positions    // texture coords
        1.0f, 1.0f,     1.0f, 1.0f,   // top right
        1.0f, 0.0f,     1.0f, 0.0f,   // bottom right
        0.0f, 0.0f,     0.0f, 0.0f,   // bottom left
        0.0f, 1.0f,     0.0f, 1.0f    // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
    VertexGroup quad(sizeof(vertices), vertices, sizeof(indices), indices, 4);
    Shader shader = Shader::file("/home/ethanf/A/pro/whack/GUI/gui.vs", "/home/ethanf/A/pro/whack/GUI/gui.fs");
    
    printf("%s\n", glfwGetVersionString());

    while( !glfwWindowShouldClose( window ) )
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear( GL_COLOR_BUFFER_BIT );

        quad.use();
        shader.use();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    glfwTerminate();
    //*/
    return 0;
}