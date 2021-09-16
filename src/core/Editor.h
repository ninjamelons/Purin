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
    ImGuiContext* _imguiContext = nullptr;
    std::shared_ptr<GameObject> _selectedSceneNode = nullptr;
public:
    Editor(GLFWwindow* window, const char* glsl_version);
    ~Editor();

    ImGuiContext* getImguiContext();
    std::shared_ptr<GameObject> getSelectedSceneNode();

    template<typename D>
    void DrawEditor(D&& drawFunc);
    void DrawSceneNode(std::shared_ptr<GameObject> node, ImGuiTreeNodeFlags flags = 0);
    void DrawTransform(Transform& transform);
};

ImGuiContext* Editor::getImguiContext(){return _imguiContext;}
std::shared_ptr<GameObject> Editor::getSelectedSceneNode(){return _selectedSceneNode;}

template<typename D>
void Editor::DrawEditor(D&& drawFunc)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    ImGui::ShowDemoWindow();

    drawFunc();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::DrawSceneNode(std::shared_ptr<GameObject> node, ImGuiTreeNodeFlags flags)
{
    ImGuiTreeNodeFlags node_flags = flags;
    if(_selectedSceneNode == node) {
        node_flags |= ImGuiTreeNodeFlags_Selected;
    }

    if(ImGui::TreeNodeEx(node->_name.c_str(), node_flags))
    {
        if(ImGui::IsItemClicked())
        {
            _selectedSceneNode = node;
        }

        for(auto child : node->_children)
        {
            DrawSceneNode(child, flags);
        }
        ImGui::TreePop();
    }
}

void Editor::DrawTransform(Transform& transform)
{
    if(ImGui::BeginTable("Transform", 3))
    {
        ImGui::TableNextRow();
        ImGui::AlignTextToFramePadding();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("Position");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        if(ImGui::DragFloat("X Pos", &transform._translation.x, 0.1f))
            transform.setDirty();
        ImGui::TableSetColumnIndex(1);
        if(ImGui::DragFloat("Y Pos", &transform._translation.y, 0.1f))
            transform.setDirty();
        ImGui::TableSetColumnIndex(2);
        if(ImGui::DragFloat("Z Pos", &transform._translation.z, 0.1f))
            transform.setDirty();

        ImGui::TableNextRow();
        ImGui::AlignTextToFramePadding();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("Orientation");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        
        // TODO - NEEDS TO BE CONVERTED TO EULER ANGLES SOMEHOW (or dont what do I care)
        if(ImGui::DragFloat("X Rot", &transform._orientation.x, 0.1f))
            transform.setDirty();
        ImGui::TableSetColumnIndex(1);
        if(ImGui::DragFloat("Y Rot", &transform._orientation.y, 0.1f))
            transform.setDirty();
        ImGui::TableSetColumnIndex(2);
        if(ImGui::DragFloat("Z Rot", &transform._orientation.z, 0.1f))
            transform.setDirty();

        ImGui::TableNextRow();
        ImGui::AlignTextToFramePadding();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("Scale");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        if(ImGui::DragFloat("X Scale", &transform._scale.x, 0.1f))
            transform.setDirty();
        ImGui::TableSetColumnIndex(1);
        if(ImGui::DragFloat("Y Scale", &transform._scale.y, 0.1f))
            transform.setDirty();
        ImGui::TableSetColumnIndex(2);
        if(ImGui::DragFloat("Z Scale", &transform._scale.z, 0.1f))
            transform.setDirty();

        ImGui::EndTable();
    }
}

Editor::Editor(GLFWwindow* window, const char* glsl_version)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    _imguiContext = ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    //This wil break scroll for some reason, unclear why
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

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