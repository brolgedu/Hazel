#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp> // for glm::translate
#include <glm/gtc/type_ptr.hpp> // for glm::value_ptr

#include <Hazel/Platform/OpenGL/OpenGLShader.h>

Sandbox2D::Sandbox2D() :
        Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {
}

void Sandbox2D::OnAttach() {

}

void Sandbox2D::OnDetach() {
}

void Sandbox2D::OnUpdate(Hazel::Timestep ts) {
    // Update
    m_CameraSpeed = ts * 0.15;
    m_CameraController.OnUpdate(m_CameraSpeed);

    // Render
    Hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1}); // Background color
    Hazel::RenderCommand::Clear();

    Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Hazel::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
    Hazel::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f});
    Hazel::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Hazel::Event &e) {
    m_CameraController.OnEvent(e);

}