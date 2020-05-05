
#include "shader.h"
#include "gl.h"

void check_shader(GLint shader){
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE){
        GLint logSize = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
        char* err = new char[logSize];
        glGetShaderInfoLog(shader, logSize, NULL, err);
        printf("Failed to compile shader\n");
        printf("%s\n", err);
        glDeleteShader(shader);
        delete err;
    }
}

long file_size(FILE* file)
{
    long l = ftell(file);
    fseek(file, 0L, SEEK_END);
    long sz = ftell(file) - l;
    fseek(file, l, SEEK_SET);
    return sz;
}

uint create_shader( GLenum type, const char* shader ){
    uint s = glCreateShader(type);
    glShaderSource(s, 1, &shader, nullptr);
    glCompileShader(s);
    check_shader(s);
    return s;
}
uint create_shader( GLenum type, FILE* shader ){
    long sz = file_size(shader);
    char* str = new char[sz+1];
    str[0] = fgetc(shader);
    int i=0;
    while(str[i] != 0 && i<sz){
        i++;
        str[i] = fgetc(shader);
    }
    if(str[i] == EOF){
        str[i] = '\0';
    }
    //printf("%s\n", str);
    uint s = create_shader(type, str);
    delete str;
    return s;
}

Shader::Shader(FILE* vertexShader, FILE* fragmentShader)
{
    id = glCreateProgram();
    uint vs = create_shader(GL_VERTEX_SHADER, vertexShader );
    uint fs = create_shader(GL_FRAGMENT_SHADER, fragmentShader );

    attach_n_link(vs, fs);
}

Shader::Shader( const char* vertexShader, const char* fragmentShader )
{
    id = glCreateProgram();
    uint vs = create_shader(GL_VERTEX_SHADER, vertexShader );
    uint fs = create_shader(GL_FRAGMENT_SHADER, fragmentShader );

    attach_n_link(vs, fs);
}

Shader Shader::file( const char* vertexPath, const char* fragmentPath )
{
    FILE* vs = fopen(vertexPath, "r");
    if(!vs){fprintf(stderr, "Vertex shader %s not found\n", vertexPath);};
    FILE* fs = fopen(fragmentPath, "r");
    if(!fs){fprintf(stderr, "Fragment shader %s not found\n", fragmentPath);};
    return Shader(vs, fs);
}
Shader Shader::file( string vertexPath, string fragmentPath )
{
    return Shader::file(vertexPath.c_str(), fragmentPath.c_str());
}
uint Shader::uniform_location( const string& name){
    use();
    uint r;
    r = glGetUniformLocation(id, name.c_str());
    used();
    return r;
}
uint Shader::uni( const string& name){
    return uniform_location(name);
}
void Shader::setBool( const string& name, bool val){
    use();
    glUniform1i(uniform_location(name), (int)val);
    used();
}
void Shader::setInt( const string& name, int val){
    use();
    glUniform1i(uniform_location(name), val);
    used();
}
void Shader::setFloat( const string& name, float val){
    use();
    glUniform1f(uniform_location(name), val);
    used();
}
void Shader::set( const string& name, bool val){
    setBool(name, val);
}
void Shader::set( const string& name, int val){
    setInt(name, val);
}
void Shader::set( const string& name, float val){
    setFloat(name, val);
}

void Shader::use()
{
    glUseProgram( id );
}
void Shader::used()
{
    glUseProgram( 0 );
}

void Shader::attach_n_link(uint vs, uint fs)
{
    glAttachShader(id, vs);
    glAttachShader(id, fs);
    glLinkProgram(id);
    glValidateProgram(id);
    //shaders are now attached to the program, can be deleted
    glDeleteShader(vs);
    glDeleteShader(fs);
}

void use(Shader s){
    s.use();
}