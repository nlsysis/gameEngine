#include "Sandbox2D.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{

}

void Sandbox2D::OnAttach()
{
	m_CheckboardTexture = Engine::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(float timestep)
{
	EG_PROFILE_FUNCTION();

	//update
	{	
		EG_PROFILE_SCOPE("Sandbox2D::OnUpdate");
		m_CameraController.OnUpdate(timestep);
	}

	//Render
	{
		EG_PROFILE_SCOPE("Sandbox2D::Render");
		Engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Engine::RenderCommand::Clear();
	}

	{
		EG_PROFILE_SCOPE("Sandbox2D::Begin Render");
		Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Engine::Renderer2D::DrawQuad({ 0.0f,-0.5f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Engine::Renderer2D::DrawQuad({ 0.0f,0.8f }, { 0.6f, 1.0f }, { 0.8f, 0.2f, 0.8f, 1.0f });
		Engine::Renderer2D::DrawQuad({ 0.6f,0.3f }, { 0.6f, 0.5f }, m_CheckboardTexture);
		Engine::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Engine::Event& event)
{
	m_CameraController.OnEvent(event);
}
