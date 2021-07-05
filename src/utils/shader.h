#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <iostream>
#include <string>
#include <filesystem>
#include <limits>
#include <fstream>
#include <iterator>

class Shader
{
private:
    unsigned int ID;
public:
    unsigned int getID();
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
private:
    std::string read_shader_file (const char *shader_file);
};

#endif