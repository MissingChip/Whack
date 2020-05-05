#pragma once

#include <stdio.h>
#include <string>
using namespace std;

class Shader
{
private:
    void attach_n_link(uint vs, uint fs);
public:
    uint id;

    // constructor reads and builds the shader
    Shader(const char* vertexString, const char* fragmentString);
    Shader(FILE* vertexPath, FILE* fragmentPath);
    static Shader file(const char* vertexPath, const char* fragmentPath);
    static Shader file(string vertexPath, string fragmentPath);
    // use/activate the shader
    void use();
    // deactivate shader
    void used();
    // utility uniform functions
    void setBool(const std::string &name, bool value);  
    void setInt(const std::string &name, int value);   
    void setFloat(const std::string &name, float value);
    void set(const std::string &name, bool value);
    void set(const std::string &name, int value);
    void set(const std::string &name, float value);
    uint uniform_location(const std::string &name);
    uint uni(const std::string &name);
};

void use(Shader s);