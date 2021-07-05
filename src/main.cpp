#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <filesystem>
#include <limits>
#include <fstream>
#include <iterator>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
unsigned int getShaderProgram();
unsigned int getVAO(unsigned int, unsigned long size, float vertices[], unsigned long size_i, unsigned int indices[]);

std::string read_shader_file (const char *shader_file)
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

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    }; 
    unsigned int shaderProgram = getShaderProgram();
    unsigned int VAO = getVAO(shaderProgram, sizeof(vertices), vertices, sizeof(indices), indices);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        /*
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        */

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

unsigned int getShaderProgram()
{
    // Create and compile vertex shader
    std::string vertex_source = read_shader_file("./shaders/vertex/vertex.vert");
    const char *vertexShaderSource = vertex_source.c_str();

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
    std::string fragment_source = read_shader_file("./shaders/fragment/fragment.frag");
    const char *fragmentShaderSource = fragment_source.c_str();

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
    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int  success_prog;
    char infoLog_prog[512];
    glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success_prog);
    if(!success_prog) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog_prog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog_prog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

unsigned int getVAO(unsigned int shaderProgram, unsigned long size_v, float vertices[], unsigned long size_i, unsigned int indices[])
{
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    unsigned int VBO, EBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size_v, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_i, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    return VAO;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}