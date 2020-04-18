#include "texture.h"
#include "gl.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const void * data, GLsizei width, GLsizei height, GLenum format, GLint internalformat, 
    GLenum target, GLint level, GLenum type){
    if (!data)
    {
        fprintf(stderr, "Cannot load texture from nullptr");
    }
    this->target = target;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    glTexImage2D(target, level, internalformat, width, height, 0, format, type, data);
}

Texture Texture::rgb(const void * data, GLsizei width, GLsizei height, GLint level, GLenum type, GLenum target){
    return Texture(data, width, height, GL_RGB, GL_RGB, target, level, type);
}
Texture Texture::rgba(const void * data, GLsizei width, GLsizei height, GLint level, GLenum type, GLenum target){
    return Texture(data, width, height, GL_RGBA, GL_RGBA, target, level, type);
}
Texture Texture::from_file(const char* filename){
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if(nrChannels == 4){
        Texture t = Texture::rgba(data, width, height);
        stbi_image_free(data);
        return t;
    }
    if(nrChannels == 2){
        Texture t = Texture(data, width, height, GL_RG);
        stbi_image_free(data);
        return t;
    }
    if(nrChannels == 1){
        Texture t = Texture(data, width, height, GL_RED);
        stbi_image_free(data);
        return t;
    }
    Texture t = Texture(data, width, height);
    stbi_image_free(data);
    return t;
}
void Texture::generate_mipmap(GLenum interpolation){
    use();
    glGenerateMipmap(target);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    used();
}
void Texture::wrap(GLint x, GLint y){
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, x);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, y);
}
void Texture::wrap(GLint param){
    wrap(param, param);
}
void Texture::filter(GLint x, GLint y){
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, x);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, y);
}
void Texture::filter(GLint param){
    filter(param, param);
}
void Texture::use(){
    glBindTexture(target, id);
}
void Texture::used(){
    glBindTexture(target, 0);
}
void Texture::active(int texture){
    if(texture>=0){
        glActiveTexture(GL_TEXTURE0+texture);
    }
}