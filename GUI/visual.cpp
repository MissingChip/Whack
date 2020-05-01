
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "gl.h"

#include "vertex_group.h"
#include "shader.h"

#include "visualizer.h"
#include "whack.h"
#include "demo.h"

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
/*
    Tile t = Tile(0, 0, 50, 24);
    Tile t2(t);
    Tile t3(t);
    Tile t4(t);
    t.size.x = 40;
    t2.size.x = 60;
    RowBox g(&t);
    g.add(&t2);
    g.add(&t3);
    g.add(&t4);
    BoundMod bm;
    bm.bind_x = false;
    g.add(&bm);
    RowBox g2;
    RowBox g3(&g);
    g3.add(&g2);
    FillMod f;
    g3.add(&f);
    f.direction = 1;
    StretchMod s(anchors::horizontal);
    g3.add(&s);
    g.set_direction(0);
    g2.set_direction(0);
    g3.set_direction(1);
    g3.rowmod.resize_on_update = false;

    StretchMod menustretch(anchors::vertical);
    Group sidemenu;
    FillMod winstretch;
    winstretch.direction = 0;
    Group win;
    sidemenu.size.x = 240;
    sidemenu.size.y = 300;
    g2.add(&sidemenu);
    g2.add(&win);
    g2.add(&menustretch);
    g2.add(&winstretch);
*/
    Demo d;
    Visualizer v(&d);

    printf("%s\n", glfwGetVersionString());
    //printf("%p %p\n", &g2, &sidemenu);
    int width, height, pwidth, pheight;

    //g3.update_all();
    while( !glfwWindowShouldClose( window ) )
    {
        glfwGetWindowSize(window, &width, &height);
        if(pwidth != width || pheight != height){
            glViewport(0, 0, width, height);
            v.size.x = width;
            v.size.y = height;
            
            d.size.x = width;
            d.size.y = height;
            d.update_all();
            d.update_all();
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