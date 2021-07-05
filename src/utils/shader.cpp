#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // Create and compile vertex shader
    std::string shader_source = read_shader_file(vertexPath);
    const char *vertexShaderSource = shader_source.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int  success_vert;
    char infoLog_vert[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_vert);
    if(!success_vert) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog_vert);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog_vert << std::endl;
    }

    // Create and compile fragment shader
    shader_source = read_shader_file("./shaders/fragment/fragment.frag");
    const char *fragmentShaderSource = shader_source.c_str();

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    int  success_frag;
    char infoLog_frag[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success_frag);
    if(!success_frag) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog_frag);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog_frag << std::endl;
    }

    // Create shader program and link shaders
    ID = glCreateProgram();

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    int  success_prog;
    char infoLog_prog[512];
    glGetProgramiv(ID, GL_COMPILE_STATUS, &success_prog);
    if(!success_prog) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog_prog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog_prog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

unsigned int Shader::getID()
{
    return ID;
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value)
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
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