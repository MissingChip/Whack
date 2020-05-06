#pragma once

#include "group.h"

#include "vertex_group.h"
#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


class Visualizer {
public:
    Visualizer();
    Visualizer(Tile* r);
    Tile* root;
    glm::vec2 size = glm::vec2(1.0, 1.0);
    glm::mat4 transform;
    int trid;
    float color[4] = {1.0, 0.95, 1.0, 0.5};
    int coid;
    VertexGroup quad;
    Shader shader = Shader::file("/home/ethanf/A/pro/whack/GUI/gui.vs", "/home/ethanf/A/pro/whack/GUI/gui.fs");

    void draw();
private:
    void draw(Tile* t);
};
