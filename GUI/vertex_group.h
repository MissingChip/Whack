#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "gl.h"

using namespace std;

class VertexGroup
{
public:
    VertexGroup(uint vertices_s, float* vertices, uint indices_s, uint* indices, uint stride = 3, GLenum draw_type = GL_STATIC_DRAW);
    VertexGroup(vector<float> vertices_vec, vector<uint> indices_vec, uint stride = 3, GLenum draw_type = GL_STATIC_DRAW);

    uint vao, vbo, ebo, stride;

    uint vertices_s, indices_s;
    float* vertices;
    uint* indices;
    
    GLenum draw_type;

    void attribute(uint index, int size, intptr_t offset, int alt_stride = -1, GLenum type = GL_FLOAT, GLboolean normalized = GL_FALSE);

    void use();
    void used();
    void gl_forget();
    //void buffer();
    void update();
    void update_vertices();
    void update_indices();

};

/*
class VertexGroup
{
public:
    VertexGroup(GLenum draw_type);
    VertexGroup(GLenum draw_type, vector<float> vertices, vector<uint> indices);
    VertexGroup(vector<float> vertices, vector<uint> indices);
    VertexGroup() : VertexGroup(GL_STATIC_DRAW){};

    void use();
    void gl_forget();
    //void buffer();
    void update();

    void set_vertices(vector<float> v);
    void set_indices(vector<uint> i);
    void set_vertices(int count, float* v);
    void set_indices(int count, uint* i);
    void copy_vertices(vector<float> v);
    void copy_indices(vector<uint> i);
    void copy_vertices(int count, float* v);
    void copy_indices(int count, uint* i);

    uint vao, vbo, ebo;
    GLenum draw_type;

    int vertex_size;
    int stride;

    int n_vertices;
    float* vertices;
    int n_indices;
    uint* indices;
private:
    void init();
};

void use(VertexGroup v);*/