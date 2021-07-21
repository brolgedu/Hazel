#include "hzpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include "Hazel/Application.h"
#include "Hazel/KeyCodes.h"

// TEMPORARY
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hazel {

    ImGuiLayer::ImGuiLayer()
            : Layer("ImGuiLayer") {}

    ImGuiLayer::~ImGuiLayer() {}

    void ImGuiLayer::OnAttach() {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;        // Enable Keyboard controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;            // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;          // Enable Multi-viewport / Platform windows

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

//         When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to the style
        ImGuiStyle &style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        Application &app = Application::Get();
        GLFWwindow *window = static_cast<GLFWwindow *>(app.GetWindow().GetNativeWindow());

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true); // Do not use GLFW version 3.4+ due to GLFW_MOUSE_PASSTHROUGH bug.
        ImGui_ImplOpenGL3_Init("#version 410 core");
    }

    void ImGuiLayer::OnDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::Begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End() {
        ImGuiIO &io = ImGui::GetIO();
        Application &app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void ImGuiLayer::OnImGuiRender() {
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }


}