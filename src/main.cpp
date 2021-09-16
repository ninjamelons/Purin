#include "utils/camera.h"
#include "utils/physics.h"

#include "core/Editor.h"
#include "core/Shader.h"
#include "core/Scene.h"
#include "core/GameObject.h"
#include "core/RigidBody.h"
#include "core/Mesh.h"
#include "core/Model.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>
#include <filesystem>
#include <limits>
#include <fstream>
#include <iterator>

#define STB_IMAGE_IMPLEMENTATION
#include "utils/stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void g_cursor_callback(GLFWwindow* window, double xpos, double ypos);
void g_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

unsigned int getShaderProgram();

float mixValue = 0.2f;

Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
bool firstMouse = true;
float lastX = 400, lastY = 300;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
    glfwInit();
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    int windowWidth = 1250;
    int windowHeight = 900;

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "LearnOpenGL", NULL, NULL);
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

    Editor editor(window, glsl_version);


    glViewport(0, 0, windowWidth, windowHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f,
    };

    Shader shader("./resources/shaders/vertex.vert", "./resources/shaders/fragment.frag");
    shader.use();

    // Set texture wrapping for x and y
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    // Set texture scaling for shrinking and enlarging
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // OR GL_LINEAR for a more blurry effect
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Set texture interpolation between mipmap levels
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // Enable alpha blending (?)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    stbi_set_flip_vertically_on_load(true);

    // Enable depth rendering
    glEnable(GL_DEPTH_TEST);

    // Create Scene
    Scene scene;

    // Load backpack model
    std::shared_ptr<Component> backpackModel = std::make_shared<Model>("./resources/models/backpack/backpack.obj");

    // Create first object
    std::shared_ptr<GameObject> backpack = std::make_shared<GameObject>("First object");
    backpack->addComponent(backpackModel);


    std::shared_ptr<GameObject> backpack2 = std::make_shared<GameObject>("Second backpack");
    backpack2->_transform += Translation(glm::vec3(10.0f, 0.0f, 0.0f));
    backpack2->addComponent(backpackModel);

    scene._root->addChild(backpack);
    scene._root->addChild(backpack2);

    /*
    // Create second object
    std::shared_ptr<GameObject> cube2 = std::make_shared<GameObject>("Second object");
    cube2->setWorldTransform(Transform());
    cube2->_relativeTransform = Transform();

    scene._root.addChild(cube2);

    // Create third object
    std::shared_ptr<GameObject> cube3 = std::make_shared<GameObject>("Third object");
    cube3->setWorldTransform(Transform());
    cube3->_relativeTransform = Transform();

    scene._root.addChild(cube3);

    // Create fourth object
    std::shared_ptr<GameObject> cube4 = std::make_shared<GameObject>("Fourth object");
    cube4->setWorldTransform(Transform());
    cube4->_relativeTransform = Transform();

    cube3->addChild(cube4);
    */

    // Add Bullet object
    Physics physics;

    btScalar cubeMass(1.0f);
    btVector3 cubeInertia(0.0f, 0.0f, 0.0f);
    btVector3 cubeOrigin(btScalar(50.), btScalar(50.), btScalar(50.));
    btCollisionShape* cubeShape = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));

    physics.addRigidBody(cubeMass, cubeInertia, cubeOrigin, cubeShape);
   
    char buf[256] = {};
    float f = 0.0f;

    while(!glfwWindowShouldClose(window))
    {
        physics._dynamicsWorld->stepSimulation(1.0f / 60.0f, 10);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Projection matrix - transform to clip space
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(camera.Fov), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
        shader.setMat4("projection", projection);

        // View matrix / Camera view (Same thing)
        glm::mat4 view = glm::lookAt(camera.Position, camera.Position + camera.Front, camera.Up);
        shader.setMat4("view", view);

        // Render backpack model
        for(auto& child : scene._root->_children)
        {
            shader.setMat4("model", child->_transform.worldTransform());
            child->getComponent<Model>()->Draw(shader);
        }

        /*
        shader.setMat4("model", backpack->getWorldTransform()._worldTransform);
        std::static_pointer_cast<Model>(backpackModel)->Draw(shader);
        */

        editor.DrawEditor([&]() {
            ImGui::SetCurrentContext(editor.getImguiContext());
            
            ImGui::Begin("Scene Hierarchy");

            static ImGuiTreeNodeFlags base_flags =
                ImGuiTreeNodeFlags_OpenOnArrow |
                ImGuiTreeNodeFlags_OpenOnDoubleClick |
                ImGuiTreeNodeFlags_SpanAvailWidth;
            ImGuiTreeNodeFlags node_flags = base_flags;
            if (ImGui::TreeNodeEx("Scene", ImGuiTreeNodeFlags_DefaultOpen))
            {
                for (auto& child : scene._root->_children)
                {                    
                    editor.DrawSceneNode(child, node_flags);
                }
                ImGui::TreePop();
            }
            ImGui::End();
            
            if(editor.getSelectedSceneNode() != nullptr)
            {
                ImGui::SetNextWindowSize(ImVec2(150, 200), ImGuiCond_FirstUseEver);
                ImGui::Begin("Transform");
                ImGui::Text(editor.getSelectedSceneNode()->_name.c_str());
                editor.DrawTransform(editor.getSelectedSceneNode()->_transform);
                ImGui::End();
            }
        });

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete cubeShape;

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    else if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        mixValue += 0.01f;
    else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        mixValue -= 0.01f;

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.MovementSpeed = SPEED * 2;
    else {
        camera.MovementSpeed = SPEED;
    }

    // Interact with scene if button is held down
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glfwSetCursorPosCallback(window, g_cursor_callback);
        glfwSetScrollCallback(window, g_scroll_callback);


        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            camera.ProcessKeyboard(UP, deltaTime);
        else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            camera.ProcessKeyboard(DOWN, deltaTime);
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        glfwSetCursorPosCallback(window, NULL);
        glfwSetScrollCallback(window, NULL);
    }
}

void g_cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void g_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}