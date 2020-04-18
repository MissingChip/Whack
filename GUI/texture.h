#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "gl.h"

class Texture
{
public:
    Texture(const void * data, GLsizei width, GLsizei height, GLenum format = GL_RGB, GLint internalformat = GL_RGBA, 
    GLenum target = GL_TEXTURE_2D, GLint level = 0, GLenum type = GL_UNSIGNED_BYTE);
    /*
    Based direcly off of function here (all references to tables on that page):
        [https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml]
        data
            Specifies a pointer to the image data in memory. 
        width
            Specifies the width of the texture image. 
            All implementations support texture images that are at least 1024 texels wide.
        height
            Specifies the height of the texture image, 
            or the number of layers in a texture array, 
            in the case of the GL_TEXTURE_1D_ARRAY and GL_PROXY_TEXTURE_1D_ARRAY targets. 
            All implementations support 2D texture images that are at least 1024 texels high, 
            and texture arrays that are at least 256 layers deep.
        internalformat
            Specifies the number of color components in the texture. 
            Must be one of base internal formats given in Table 1, one of the sized internal formats given in Table 2, 
            or one of the compressed internal formats given in Table 3, below.
        level
            Specifies the level-of-detail number. Level 0 is the base image level. 
            Level n is the nth mipmap reduction image. 
            If target is GL_TEXTURE_RECTANGLE or GL_PROXY_TEXTURE_RECTANGLE, level must be 0.
        target
            Specifies the target texture. Must be GL_TEXTURE_2D, GL_PROXY_TEXTURE_2D, 
            GL_TEXTURE_1D_ARRAY, GL_PROXY_TEXTURE_1D_ARRAY, GL_TEXTURE_RECTANGLE, 
            GL_PROXY_TEXTURE_RECTANGLE, GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 
            GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, or GL_PROXY_TEXTURE_CUBE_MAP.
        border
            This value must be 0.
        format
            Specifies the format of the pixel data. The following symbolic values are accepted: GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA, GL_RED_INTEGER, GL_RG_INTEGER, GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER, GL_BGRA_INTEGER, GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL.
        type
            Specifies the data type of the pixel data. The following symbolic values are accepted: GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV, GL_UNSIGNED_INT_10_10_10_2, and GL_UNSIGNED_INT_2_10_10_10_REV.
     */
    static Texture rgb(const void * data, GLsizei width, GLsizei height, GLint level = 0, GLenum type = GL_UNSIGNED_BYTE, GLenum target = GL_TEXTURE_2D);
    static Texture rgba(const void * data, GLsizei width, GLsizei height, GLint level = 0, GLenum type = GL_UNSIGNED_BYTE, GLenum target = GL_TEXTURE_2D);
    static Texture from_file(const char* filename);

    void generate_mipmap(GLenum interpolation = GL_LINEAR_MIPMAP_LINEAR);
    void wrap(GLint param);
    void wrap(GLint x, GLint y);
    void filter(GLint param);
    void filter(GLint x, GLint y);
    static void active(int texture = 0);

    void use();
    void used();

    uint id;

protected:
    uint target;
};