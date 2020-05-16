
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "gl.h"

#include "vertex_group.h"
#include "shader.h"

#include "visualizer.h"
#include "group.h"
#include "mods.h"
//#include "demo.h"
#include "pagedemo.h"

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

    //Demo d;
    PageDemo b;
    Visualizer v (b.tile);
    Tile& d = *b.tile;

    printf("%s\n", glfwGetVersionString());
    //printf("%p %p\n", &g2, &sidemenu);
    int width, height, pwidth, pheight, state = GLFW_RELEASE, pstate = GLFW_RELEASE;
    double xpos, ypos;

    //g3.update_all();
    while( !glfwWindowShouldClose( window ) )
    {
        glfwGetCursorPos(window, &xpos, &ypos);
        
        state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if (state == GLFW_PRESS && pstate == GLFW_RELEASE)
        {
            printf("clicked %f %f\n", xpos, ypos);
            b.clicked(glm::vec2(xpos, ypos));
        }
        pstate = state;

        glfwGetWindowSize(window, &width, &height);
        if(pwidth != width || pheight != height){
            glViewport(0, 0, width, height);
            v.size.x = width;
            v.size.y = height;
            
            d.size.x = width;
            d.size.y = height;
            b.update();
            pwidth = width;
            pheight = height;

            //Vec2 p = g2.global_pos();
            //printf("%f %f\t%f %f\n", sidemenu.size.x, sidemenu.size.y, p.x, p.y);
            //printf("b %f %p\n", g2.size.y, &g2);
            //printf("b %f %p %lu\n", sidemenu.pos.y, sidemenu.parent, g2.mods.size());
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