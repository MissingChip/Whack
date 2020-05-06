
#include "gl.h"

#include "vertex_group.h"


VertexGroup::VertexGroup(uint vertices_s, float* vertices, uint indices_s, uint* indices, uint stride, GLenum draw_type)
    : vertices_s(vertices_s), vertices(vertices), indices_s(indices_s), indices(indices), stride(stride), draw_type(draw_type)
{
    //stride = m_stride;
    glGenVertexArrays(1, &vao);
    glGenBuffers( 1, &vbo );
    glGenBuffers( 1, &ebo );

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices_s, vertices, draw_type);

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices_s, indices, draw_type );
    
    
    // position attribute
    attribute(0, 3, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    glBindVertexArray(0);
}

VertexGroup::VertexGroup(vector<float> vertices_vec, vector<uint> indices_vec, uint stride, GLenum draw_type)
    : VertexGroup(vertices_vec.size()*sizeof(float), &vertices_vec[0], indices_vec.size()*sizeof(uint), &indices_vec[0], stride, draw_type){}

void VertexGroup::attribute(uint index, int size, intptr_t offset, int alt_stride, GLenum type, GLboolean normalized)
{
    /*
     * attribute(uint index, int size, intptr_t offset, GLenum type, GLboolean normalized)
     *      index:
     *          - index of attribute to be modified
     *      size:
     *          - number of components per attribute
     *      offset:
     *          - offset of the first component (number of components before first component)
     *      type: [GL_FLOAT]
     *          - type of data, ex:  GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED
     *      normalized: [GL_FALSE]
     *          - whether data is normalized or not (GL_TRUE | GL_FALSE)
     *      alt_stride: [-1]
     *          - an alternate stride for the data, or the default for the object if alt_stride == -1
     */
    uint s;
    if(alt_stride == -1){
        s = stride;
    }
    else{
        s = alt_stride;
    }
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(index, size, type, normalized, s * sizeof(float), (void*)(offset*sizeof(float)));
    glEnableVertexAttribArray(index);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}

void VertexGroup::use()
{
    glBindVertexArray(vao);
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}
void VertexGroup::used()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    glBindVertexArray(0);
}

void VertexGroup::update()
{
    use();
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices_s, vertices);
    glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, 0, indices_s, indices);
    used();
}
void VertexGroup::update_vertices()
{
    use();
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices_s, vertices);
    used();
}
void VertexGroup::update_indices()
{
    use();
    glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, 0, indices_s, indices);
    used();
}

void VertexGroup::gl_forget()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}