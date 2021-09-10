#if !defined(EDITOR)
#define EDITOR

#include "GameObject.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <memory>

class Editor
{
private:
    ImGuiContext* _imguiContext;
public:
    Editor(GLFWwindow* window, const char* glsl_version);
    ~Editor();

    ImGuiContext* getImguiContext();

    template<typename D>
    void DrawEditor(D&& drawFunc);
    void DrawSceneNode(std::shared_ptr<GameObject> node);
    void DrawTransform(Transform& transform);
};

ImGuiContext* Editor::getImguiContext(){return _imguiContext;}

template<typename D>
void Editor::DrawEditor(D&& drawFunc)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    drawFunc();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::DrawSceneNode(std::shared_ptr<GameObject> node)
{
    if(ImGui::TreeNode(node->_name.c_str()))
    {
        for(auto child : node->_children)
        {
            DrawSceneNode(child);
        }
        ImGui::TreePop();
    }
}

void Editor::DrawTransform(Transform& transform)
{
    
}

Editor::Editor(GLFWwindow* window, const char* glsl_version)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    _imguiContext = ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}
Editor::~Editor()
{
    // ImGui Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(_imguiContext);
}

#endif