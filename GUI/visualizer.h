#pragma once

#include "group.h"

#include "vertex_group.h"
#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace quadinfo{
    inline float vertices[] = {
        // positions    // texture coords
        1.0f, 1.0f,     1.0f, 1.0f,   // top right
        1.0f, 0.0f,     1.0f, 0.0f,   // bottom right
        0.0f, 0.0f,     0.0f, 0.0f,   // bottom left
        0.0f, 1.0f,     0.0f, 1.0f    // top left 
    };
    inline unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
}

class Visualizer {
public:
    Visualizer(Tile* r);
    Tile* root;
    glm::vec2 size = glm::vec2(1.0, 1.0);
    glm::mat4 transform;
    int trid;
    float color[4] = {1.0, 0.95, 1.0, 0.5};
    int coid;
    VertexGroup quad = VertexGroup(sizeof(quadinfo::vertices), quadinfo::vertices, sizeof(quadinfo::indices), quadinfo::indices, 4);
    Shader shader = Shader::file("/home/ethanf/A/pro/whack/GUI/gui.vs", "/home/ethanf/A/pro/whack/GUI/gui.fs");

    void draw();
private:
    void draw(Tile* t);
};
