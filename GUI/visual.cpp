
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "gl.h"

#include "vertex_group.h"
#include "shader.h"

#include "visualizer.h"
#include "whack.h"

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
    window = glfwCreateWindow(640, 480, "Whack", NULL, NULL);

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
    Tile t = Tile(0, 0, 50, 24);
    Tile t2(t);
    Tile t3(t);
    Tile t4(t);
    RowBox g(&t);
    g.set_direction(0);
    g.rowmod.resize_on_update = false;
    g.size.x = 600;
    g.size.y = 300;
    g.add(&t2);
    g.add(&t3);
    g.add(&t4);
    Visualizer v(&g);

    printf("%s\n", glfwGetVersionString());
    int width, height, pwidth, pheight;

    while( !glfwWindowShouldClose( window ) )
    {
        glfwGetWindowSize(window, &width, &height);
        if(pwidth != width || pheight != height){
            glViewport(0, 0, width, height);
            v.size.x = width;
            v.size.y = height;
            g.size.x = width;
            g.size.y = height;
            g.update();
            pwidth = width;
            pheight = height;
        }
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear( GL_COLOR_BUFFER_BIT );

        v.draw();

        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}