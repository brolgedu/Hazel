#include "hzpch.h"
#include "Renderer.h"

#include "Hazel/Platform/OpenGL/OpenGLShader.h"
#include "Renderer2D.h"

namespace Hazel {

    Renderer::SceneData *Renderer::m_SceneData = new SceneData;

    void Renderer::Init() {
        RenderCommand::Init();
        Renderer2D::Init();
    }


    void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
        RenderCommand::SetViewPort(0, 0, width, height);
    }


    void Renderer::BeginScene(OrthographicCamera &camera) {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }


    void Renderer::EndScene() {

    }

    void Renderer::Submit(const Ref <Shader> &shader, const Ref <VertexArray> &vertexArray,
                          const glm::mat4 &transform) {
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection",
                                                                           m_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

}
