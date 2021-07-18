#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // Create and compile vertex shader
    std::string shader_source = read_shader_file(vertexPath);
    const char *vertexShaderSource = shader_source.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");

    // Create and compile fragment shader
    shader_source = read_shader_file(fragmentPath);
    const char *fragmentShaderSource = shader_source.c_str();

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

    // Create shader program and link shaders
    _ID = glCreateProgram();

    glAttachShader(_ID, vertexShader);
    glAttachShader(_ID, fragmentShader);
    glLinkProgram(_ID);
    checkCompileErrors(_ID, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

unsigned int Shader::getID()
{
    return _ID;
}

void Shader::use()
{
    glUseProgram(_ID);
}

void Shader::setBool(const std::string &name, bool value)
{
    glUniform1i(glGetUniformLocation(_ID, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value)
{
    glUniform1i(glGetUniformLocation(_ID, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value)
{
    glUniform1f(glGetUniformLocation(_ID, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, glm::mat4 value)
{
    int matID = glGetUniformLocation(_ID, name.c_str());
    glUniformMatrix4fv(matID, 1, GL_FALSE, glm::value_ptr(value));
}

std::string Shader::read_shader_file (const char *shader_file)
{
    std::ifstream file (shader_file);
    if (!file) return std::string ();

    file.ignore(std::numeric_limits<std::streamsize>::max());
    auto size = file.gcount();

    if (size > 0x10000) // 64KiB sanity check for shaders:
        return std::string ();

    file.clear();
    file.seekg(0, std::ios_base::beg);

    std::stringstream sstr;
    sstr << file.rdbuf();
    file.close();

    return sstr.str();
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}