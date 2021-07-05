#include "utils/shader.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
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

    glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float vertices[] = {
        0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.25f, 0.0, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.25f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,   // first triangle
        2, 1, 4,   // second triangle
        1, 3, 4,   // third
        2, 4, 5
    }; 

    Shader shader("./shaders/vertex/vertex.vert", "./shaders/fragment/fragment.frag");
    shader.use();

    unsigned int VAO = getVAO(shader.getID(), sizeof(vertices), vertices, sizeof(indices), indices);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
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

    // Location 0 - vertice position, 3 values, 0 offset, first float values
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Location 1 - Vertice color value, 3 values, offset by 3 (position values) floats, ending at 6 float memory
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

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