
#include <stdio.h>
#include <thread>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "gl.h"

#include <ft2build.h>
#include FT_FREETYPE_H  

#include "vertex_group.h"
#include "shader.h"

#include "visualizer.h"
#include "group.h"
#include "mods.h"
//#include "demo.h"
#include "brickdemo.h"

int main(){
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        printf("ERROR::FREETYPE: Could not init FreeType Library\n");

    FT_Face face;
    if (FT_New_Face(ft, "fonts/dejavu/DejaVuSans.ttf", 0, &face))
        printf("ERROR::FREETYPE: Failed to load font\n");

    FT_Set_Pixel_Sizes(face, 0, 48);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
        printf("ERROR::FREETYTPE: Failed to load Glyph\n");
    /*
    int charw = face->glyph->bitmap.width;
    int charh = face->glyph->bitmap.rows;
    for(int i = 0;i<charh; i++){
        for(int j = 0;j<charw; j++){
            if(face->glyph->bitmap.buffer[i*charw + j] > 126){
                printf("\u2022");
            }else if(face->glyph->bitmap.buffer[i*charw + j] > 0){
                printf(" ");
            }else{
                printf(" ");
            }
        }
        printf("\n");
    }
    */
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
    BrickDemo b;
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
        glfwGetWindowSize(window, &width, &height);
        
        //printf("mouse %f %f\n", xpos, ypos);
        std::this_thread::sleep_for (std::chrono::milliseconds(20));
        state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if (state == GLFW_PRESS && pstate == GLFW_RELEASE)
        {
            printf("clicked %f %f\n", xpos, ypos);
            b.clicked(glm::vec2(xpos, ypos), GLFW_MOUSE_BUTTON_LEFT);
        }
        else if (state == GLFW_RELEASE && pstate == GLFW_PRESS)
        {
            printf("released %f %f\n", xpos, ypos);
            b.released(glm::vec2(xpos, ypos), GLFW_MOUSE_BUTTON_LEFT);
        }
        pstate = state;
        b.mouse(glm::vec2(xpos, ypos));

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