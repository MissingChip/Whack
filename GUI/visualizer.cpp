#include "visualizer.h"
#include "whack.h"
#include <glm/gtc/type_ptr.hpp>

using namespace glm;


namespace quadinfo{
    float vertices[16] {
            // positions    // texture coords
            1.0f, 1.0f,     1.0f, 1.0f,   // top right
            1.0f, 0.0f,     1.0f, 0.0f,   // bottom right
            0.0f, 0.0f,     0.0f, 0.0f,   // bottom left
            0.0f, 1.0f,     0.0f, 1.0f    // top left 
    };
    unsigned int indices[6]{
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
}

Visualizer::Visualizer() : quad{VertexGroup(sizeof(float)*16, quadinfo::vertices, sizeof(uint)*6, quadinfo::indices, 4)}{
    quad.attribute(1, 2, 2);
    transform = glm::ortho<double>(0, 1, 0, 1, -1, 1);
    trid = glGetUniformLocation(shader.id, "transform");
    coid = glGetUniformLocation(shader.id, "color");
}
Visualizer::Visualizer(Tile* r) : quad{VertexGroup(sizeof(float)*16, quadinfo::vertices, sizeof(uint)*6, quadinfo::indices, 4)}{
    root = r;
    quad.attribute(1, 2, 2);
    transform = glm::ortho<double>(0, 1, 0, 1, -1, 1);
    trid = glGetUniformLocation(shader.id, "transform");
    coid = glGetUniformLocation(shader.id, "color");
}
void Visualizer::draw(){

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    quad.use();
    shader.use();
    draw(root);
}
void Visualizer::draw(Tile* t){
    Vec2 pos = t->global_pos();
    transform[0][0] = 2*t->size.x/size.x;
    transform[1][1] = -(2*t->size.y/size.y);
    transform[3][0] = 2*pos.x/size.x-1;
    transform[3][1] = -(2*pos.y/size.y-1);
    glUniform4fv(coid, 1, color);
    glUniformMatrix4fv(trid, 1, GL_FALSE, value_ptr(transform));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    if(Group* g = dynamic_cast<Group*>(t)){
        for(Tile* t : g->in){
            draw(t);
        }
    }

}